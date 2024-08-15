import sensor, image, display, time, math, pyb
from pyb import UART

# 摄像头模块初始化
sensor.reset()
sensor.set_pixformat(sensor.RGB565) # 使用 grayscale 灰度图像处理速度会更快
sensor.set_framesize(sensor.QQVGA2)
sensor.skip_frames(time = 2000)

# LCD初始化
lcd = display.SPIDisplay()

# UART3初始化
uart = pyb.UART(3, 9600)  # 使用UART3，波特率为9600

while(True):
    # lens_corr 为了去除畸变，1.8 是默认参数，可以根据自己实际情况调整
    img = sensor.snapshot().lens_corr(1.8)

    # 圆形类有4个参数值：圆心(x, y), r (半径)和 magnitude（量级）；
    # 量级越大说明识别到的圆可信度越高。
    # `threshold` 参数控制找到圆的数量，数值的提升会降低识别圆形的总数。
    # `x_margin`, `y_margin`, and `r_margin`控制检测到接近圆的合并调节。
    # r_min, r_max, and r_step 用于指定测试圆的半径范围。
    for c in img.find_circles(threshold = 3000, x_margin = 10, y_margin = 10, r_margin = 10, r_min = 20, r_max = 45, r_step = 2):
        # 画红色圆做指示
        img.draw_circle(c.x(), c.y(), c.r(), color = (255, 0, 0))
        print(c)  # 打印圆形的信息

        # 通过 UART3 发送数字 5
        uart.writechar(5)

    # 显示图像
    lcd.write(img)
