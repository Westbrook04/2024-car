import sensor, image, display, time, math

# 初始化摄像头和LCD屏幕
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA2)  # Special 128x160 framesize for LCD Shield.
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)  # 颜色识别必须关闭自动增益，会影响颜色识别效果
sensor.set_auto_whitebal(False)
lcd = display.SPIDisplay()

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

def is_cylinder(circle):
    # 定义圆的半径在一定范围内，并且面积在一定范围内
    radius = circle[2]  # circle[2] 是半径
    if 20 < radius < 50:
        return True
    return False

# 主循环
while(True):
    img = sensor.snapshot()  # 获取一次快照
    # 裁剪图像中间部分
    cropped_img = img.copy((crop_x, crop_y, crop_w, crop_h))

    # 在原始图像上画出裁剪区域的边框（白色）
    img.draw_rectangle(crop_x, crop_y, crop_w, crop_h, color=(255, 255, 255))

    detected_color = None
    blob_detected = False

    # 使用Hough Circle变换来检测圆形
    circles = cropped_img.find_circles(threshold=2500, x_margin=10, y_margin=10, r_margin=10, r_min=10, r_max=50, r_step=2)

    for circle in circles:
        if is_cylinder(circle):
            # 绘制圆形的外接矩形框
            x = circle[0] - circle[2]
            y = circle[1] - circle[2]
            w = circle[2] * 2
            h = circle[2] * 2
            cropped_img.draw_rectangle(x, y, w, h, color=(0, 255, 0))  # 使用绿色绘制矩形框

            # 对符合标准的物块区域进行颜色判断
            for color, threshold in thresholds.items():
                color_blobs = cropped_img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True)
                for color_blob in color_blobs:
                    # 计算颜色斑点和圆形中心之间的距离
                    distance = math.sqrt((circle[0] - color_blob.cx())**2 + (circle[1] - color_blob.cy())**2)
                    if distance <= circle[2]:  # 如果距离小于或等于半径，则该颜色斑点在圆形内
                        detected_color = color
                        blob_detected = True
                        x, y, w, h = color_blob.rect()
                        cx, cy = color_blob.cx(), color_blob.cy()
                        cropped_img.draw_rectangle(x, y, w, h, color=(255, 0, 0))  # 使用红色绘制框框
                        cropped_img.draw_cross(cx, cy, color=(255, 0, 0))  # 使用红色绘制十字架
                        # 在终端中打印颜色
                        print("Detected color:", color)
                        # 在图像上显示颜色名称
                        cropped_img.draw_string(x, y, color, color=(255, 255, 255))
            break  # 只处理一个颜色，跳出循环

    # 如果没有检测到颜色，将其标记为白色物块
    if not blob_detected:
        for circle in circles:
            if is_cylinder(circle):
                # 绘制圆形的外接矩形框
                x = circle[0] - circle[2]
                y = circle[1] - circle[2]
                w = circle[2] * 2
                h = circle[2] * 2
                cropped_img.draw_rectangle(x, y, w, h, color=(0, 255, 0))  # 使用绿色绘制矩形框

                # 检测是否为黑色物块
                for color, threshold in thresholds2.items():
                    color_blobs = cropped_img.find_blobs([threshold], pixels_threshold=100, area_threshold=100, merge=True)
                    for color_blob in color_blobs:
                        distance = math.sqrt((circle[0] - color_blob.cx())**2 + (circle[1] - color_blob.cy())**2)
                        if distance <= circle[2]:
                            detected_color = color
                            blob_detected = True
                            x, y, w, h = color_blob.rect()
                            cx, cy = color_blob.cx(), color_blob.cy()
                            cropped_img.draw_rectangle(x, y, w, h, color=(255, 0, 0))  # 使用红色绘制框框
                            cropped_img.draw_cross(cx, cy, color=(255, 0, 0))  # 使用红色绘制十字架
                            print("Detected color:", color)
                            cropped_img.draw_string(x, y, color, color=(255, 255, 255))

                # 如果没有检测到黑色物块，将其标记为白色物块
                if not blob_detected:
                    print("Detected color: white")
                    cropped_img.draw_string(x, y, "white", color=(255, 255, 255))
                    cropped_img.draw_cross(circle[0], circle[1], color=(255, 255, 255))  # 使用白色绘制十字架

    lcd.write(cropped_img)
    time.sleep(0.1)  # 休眠100毫秒
