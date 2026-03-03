import cv2
import numpy as np
import serial
import time

# Arduino port, COM5 is the USB port of arduino (this can be changed based on the COM port of your computer)
arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2) 

cap = cv2.VideoCapture(0)

# HSV RGB range
lower_red1 = np.array([0, 50, 50])
upper_red1 = np.array([10, 255, 255])
lower_red2 = np.array([160, 50, 50])
upper_red2 = np.array([180, 255, 255])

lower_green = np.array([35, 50, 50])
upper_green = np.array([85, 255, 255])

lower_blue = np.array([100, 50, 50])
upper_blue = np.array([140, 255, 255])

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # generate mask for every colour
    mask_r = cv2.inRange(hsv, lower_red1, upper_red1) + cv2.inRange(hsv, lower_red2, upper_red2)
    mask_g = cv2.inRange(hsv, lower_green, upper_green)
    mask_b = cv2.inRange(hsv, lower_blue, upper_blue)

    # find the percentage(pixel) of a colour in the camera
    r_area = np.sum(mask_r > 0)
    g_area = np.sum(mask_g > 0)
    b_area = np.sum(mask_b > 0)

    # find the colour that takes the most area
    areas = {'R': r_area, 'G': g_area, 'B': b_area}
    max_color = max(areas, key=areas.get)

    # if area too small, set to none
    if areas[max_color] < 50:
        max_color = 'N'

    # send to Arduino
    arduino.write(max_color.encode())

    # visualize it
    cv2.putText(frame, f"Max Color: {max_color}", (10,30), cv2.FONT_HERSHEY_SIMPLEX,
                1, (0,255,0), 2)
    cv2.imshow("Camera Frame", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()