import cv2
import mediapipe as mp

from mediapipe.python.solutions import hands as mp_hands
from mediapipe.python.solutions import drawing_utils as mp_draw
hands = mp_hands.Hands()

cap = cv2.VideoCapture(0)

while True:
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)

    finger_count = 0

    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            lm_list = []

            for id, lm in enumerate(handLms.landmark):
                h, w, c = img.shape
                lm_list.append((int(lm.x * w), int(lm.y * h)))

            # Thumb (special case)
            if lm_list[4][0] > lm_list[3][0]:
                finger_count += 1

            # Fingers
            tips = [8, 12, 16, 20]

            for tip in tips:
                if lm_list[tip][1] < lm_list[tip - 2][1]:
                    finger_count += 1

            mp_draw.draw_landmarks(img, handLms, mp_hands.HAND_CONNECTIONS)

    cv2.putText(img, str(finger_count), (50, 100),
                cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 255, 0), 5)

    print("Fingers:", finger_count)

    cv2.imshow("Finger Counter", img)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()