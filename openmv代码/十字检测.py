import sensor, image, time, pyb, display
from pyb import UART

# 摄像头模块初始化
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 使用 RGB565 图像格式
sensor.set_framesize(sensor.QQVGA2)   # 设置分辨率
sensor.skip_frames(time=2000)        # 跳过初始化的前几帧
lcd = display.SPIDisplay()

# UART 初始化
uart = UART(3, 9600)  # 使用 UART3，波特率为9600

# 定义颜色阈值 (这个阈值需要根据实际环境调整)
thresholds = [(1, 20, -16, 30, -13, 10)]  #  黑色

# 设置色块宽度阈值
width_threshold = 50  # 当色块宽度大于此值时，判断为十字路口或T字路口

while(True):
    img = sensor.snapshot()  # 拍摄一帧图像

    # 寻找图像中的色块
    blobs = img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200, merge=True)

    # 遍历所有找到的色块
    junction_detected = False
    for blob in blobs:
        # 判断色块宽度是否大于阈值
        if blob.w() > width_threshold:
            junction_detected = True
            break

    if junction_detected:
        uart.writechar(0x05)  # 发送十字路口或T字路口检测到的信号

    # 显示图像
    lcd.write(img)
    time.sleep(0.1)  # 延时调整
