import cv2

cap = cv2.VideoCapture(0)
_, img = cap.read()
cv2.imwrite('tes2.jpg', img)