import sensor, image, display, time, math, pyb

# 初始化LCD屏幕
lcd = display.SPIDisplay()

# 初始化串口
uart = pyb.UART(3, 19200)  # 使用UART3，波特率为19200

# 颜色阈值（需要根据实际情况进行调整）
thresholds = {
    "red": (0, 28, 5, 127, -2, 19),  # 红色阈值
    "green": (22, 40, -35, -14, 7, 40),  # 绿色阈值
    "blue": (0, 35, -128, 14, -128, -7),  # 蓝色阈值
}
thresholds2 = {
    "black": (0, 11, -19, 45, -22, 62),  # 黑色阈值
}

# 设置中间区域的坐标和尺寸
crop_x, crop_y, crop_w, crop_h = 15, 37, 81, 77  # 裁剪区域参数 (x, y, w, h)

# 获取屏幕宽度和高度
screen_width = lcd.width()
screen_height = lcd.height()

# 计算屏幕中心
center_x = screen_width // 2
center_y = screen_height // 2

# 记录已识别的颜色代码
recognized_color_codes = set()

def init_color_detection_camera():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QQVGA2)  # Special 128x160 framesize for LCD Shield.
    sensor.skip_frames(time=2000)
    sensor.set_auto_gain(False)  # 颜色识别必须关闭自动增益，会影响颜色识别效果
    sensor.set_auto_whitebal(False)

def init_cross_detection_camera():
    sensor.reset()
    sensor.set_pixformat(sensor.GRAYSCALE)
    sensor.set_framesize(sensor.QQVGA2)  # Special 128x160 framesize for LCD Shield.
    sensor.skip_frames(time=2000)

def is_cylinder(circle):
    radius = circle[2]  # circle[2] 是半径
    return 20 < radius < 50

def is_cross_shape(blob, img):
    cx = blob.cx()
    cy = blob.cy()

    horizontal_profile = img.get_statistics(roi=(cx - 5, cy - 1, 10, 2)).mean()
    vertical_profile = img.get_statistics(roi=(cx - 1, cy - 5, 2, 10)).mean()

    return horizontal_profile < 50 and vertical_profile < 50

def color_detection_mode():
    global recognized_color_codes  # 使得函数可以修改全局变量

    img = sensor.snapshot()
    cropped_img = img.copy((crop_x, crop_y, crop_w, crop_h))

    img.draw_rectangle(crop_x, crop_y, crop_w, crop_h, color=(255, 255, 255))

    detected_color = None
    blob_detected = False

    circles = cropped_img.find_circles(threshold=2500, x_margin=10, y_margin=10, r_margin=10, r_min=10, r_max=50, r_step=2)

    for circle in circles:
        if is_cylinder(circle):
            x = circle[0] - circle[2]
            y = circle[1] - circle[2]
            w = circle[2] * 2
            h = circle[2] * 2
            cropped_img.draw_rectangle(x, y, w, h, color=(0, 255, 0))

            for color, threshold in thresholds.items():
                color_blobs = cropped_img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True)
                for color_blob in color_blobs:
                    distance = math.sqrt((circle[0] - color_blob.cx())**2 + (circle[1] - color_blob.cy())**2)
                    if distance <= circle[2]:
                        detected_color = color
                        blob_detected = True
                        color_code = {"red": 2, "green": 3, "blue": 4}.get(detected_color)
                        if color_code is not None and color_code not in recognized_color_codes:
                            recognized_color_codes.add(color_code)
                            print("Detected color:", detected_color)
                            cropped_img.draw_rectangle(color_blob.x(), color_blob.y(), color_blob.w(), color_blob.h(), color=(255, 0, 0))
                            cropped_img.draw_cross(color_blob.cx(), color_blob.cy(), color=(255, 0, 0))
                            cropped_img.draw_string(color_blob.x(), color_blob.y(), detected_color, color=(255, 255, 255))
                            uart.write("{}\n".format(color_code))
            break

    if not blob_detected:
        for circle in circles:
            if is_cylinder(circle):
                x = circle[0] - circle[2]
                y = circle[1] - circle[2]
                w = circle[2] * 2
                h = circle[2] * 2
                cropped_img.draw_rectangle(x, y, w, h, color=(0, 255, 0))

                for color, threshold in thresholds2.items():
                    color_blobs = cropped_img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True)
                    for color_blob in color_blobs:
                        distance = math.sqrt((circle[0] - color_blob.cx())**2 + (circle[1] - color_blob.cy())**2)
                        if distance <= circle[2]:
                            detected_color = color
                            blob_detected = True
                            color_code = {"black": 1, "white": 0}.get(detected_color)
                            if color_code is not None and color_code not in recognized_color_codes:
                                recognized_color_codes.add(color_code)
                                print("Detected color:", detected_color)
                                cropped_img.draw_rectangle(color_blob.x(), color_blob.y(), color_blob.w(), color_blob.h(), color=(255, 0, 0))
                                cropped_img.draw_cross(color_blob.cx(), color_blob.cy(), color=(255, 0, 0))
                                cropped_img.draw_string(color_blob.x(), color_blob.y(), detected_color, color=(255, 255, 255))
                                uart.write("{}\n".format(color_code))

                if not blob_detected:
                    detected_color = "white"
                    color_code = 0  # White color code
                    if color_code not in recognized_color_codes:
                        recognized_color_codes.add(color_code)
                        print("Detected color: white")
                        cropped_img.draw_string(x, y, "white", color=(255, 255, 255))
                        cropped_img.draw_cross(circle[0], circle[1], color=(255, 255, 255))
                        uart.write("{}\n".format(color_code))
                break

    lcd.write(cropped_img)

    # 检查是否识别了所有五种颜色
    if len(recognized_color_codes) >= 5:
        print("All colors detected.")
        recognized_color_codes.clear()  # 清空已识别的颜色
        return 'wait'  # 切换到等待模式

    return 'color'

def cross_detection_mode():
    img = sensor.snapshot()
    threshold = (0, 100)

    img.binary([threshold])
    img.invert()

    blobs = img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True)

    for blob in blobs:
        width = blob.w()
        height = blob.h()
        aspect_ratio = width / height if height > 0 else 0

        if 0.5 < aspect_ratio < 2 and width > 20 and height > 20:
            if is_cross_shape(blob, img):
                cx = blob.cx()
                cy = blob.cy()
                delta_x = cx - center_x
                delta_y = cy - center_y

                img.draw_cross(cx, cy, color=255)
                img.draw_string(cx + 10, cy - 20, "X: {}".format(delta_x), color=(255, 0, 0))
                img.draw_string(cx + 10, cy, "Y: {}".format(delta_y), color=(0, 255, 0))

                # 通过串口发送十字中心的相对位置坐标
                uart.write("{} {}\n".format(delta_x, delta_y))

    lcd.write(img)

current_mode = None

while True:
    if uart.any():
        mode = uart.readchar()
        if mode == ord('1'):
            current_mode = 'color'
            init_color_detection_camera()  # 切换到颜色检测模式时重新初始化摄像头
        elif mode == ord('2'):
            current_mode = 'cross'
            init_cross_detection_camera()  # 切换到十字检测模式时重新初始化摄像头

    if current_mode == 'color':
        next_mode = color_detection_mode()
        if next_mode == 'wait':
            current_mode = None  # 颜色识别完毕，等待串口指令
    elif current_mode == 'cross':
        cross_detection_mode()

    time.sleep(0.1)
