import sensor, image, display, time,pyb
from pyb import UART
# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA2)
sensor.skip_frames(time=2000)
uart = UART(3, 9600)  # 使用 UART3，波特率为9600
# 初始化LCD
lcd = display.SPIDisplay()

# 定义阈值
threshold = (0, 100)  # 适当调整阈值以适应你的环境

# 获取屏幕宽度和高度
screen_width = lcd.width()
screen_height = lcd.height()

# 计算屏幕中心
center_x = screen_width // 2
center_y = screen_height // 2

def is_cross_shape(blob, img):
    # 十字中心位置
    cx = blob.cx()
    cy = blob.cy()

    # 中心点附近像素的检查
    horizontal_profile = img.get_statistics(roi=(cx - 5, cy - 1, 10, 2)).mean()
    vertical_profile = img.get_statistics(roi=(cx - 1, cy - 5, 2, 10)).mean()

    # 如果横竖方向的平均灰度值都接近于0（黑色），则可能是十字形状
    return horizontal_profile < 50 and vertical_profile < 50

while True:
    img = sensor.snapshot()

    # 二值化图像
    img.binary([threshold])

    # 反转图像颜色（如果需要）
    img.invert()

    # 查找所有符合阈值条件的blob
    blobs = img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True)

    for blob in blobs:
        # 计算宽度和高度
        width = blob.w()
        height = blob.h()

        # 计算宽高比
        aspect_ratio = width / height if height > 0 else 0

        # 判断是否为十字形状的条件
        if 0.8 < aspect_ratio < 1.6 and width > 50 and height > 50:
            # 进一步检查十字形状
            if is_cross_shape(blob, img):
                # 十字中心坐标
                cx = blob.cx()
                cy = blob.cy()

                # 计算相对于屏幕中心的坐标差
                delta_x = cx - center_x
                delta_y = cy - center_y

                # 绘制十字中心为白色（在反转的背景上可见）
                img.draw_cross(cx, cy, color=255)
                uart.writechar(0x05)  # 发送十字路口或T字路口检测到的信号
                # 在图像上显示坐标差
                # 红色表示X坐标
                img.draw_string(cx + 10, cy - 20, "X: {}".format(delta_x), color=(255, 0, 0))
                # 绿色表示Y坐标
                img.draw_string(cx + 10, cy, "Y: {}".format(delta_y), color=(0, 255, 0))

    # 在LCD上显示图像
    lcd.write(img)

    # 添加延时，避免LCD刷新频率过高导致卡死
    time.sleep(0.1)
