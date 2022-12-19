from imutils import paths
import numpy as np
import imutils
import cv2

def find_marker(image):
    # convert the image to grayscale, blur it, and detect edges
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (5, 5), 0)
    edged = cv2.Canny(gray, 35, 125)
    # find the contours in the edged image and keep the largest one;
    # we'll assume that this is our piece of paper in the image
    cnts = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)
    c = max(cnts, key = cv2.contourArea)
    # compute the bounding box of the of the paper region and return it
    return cv2.minAreaRect(c)

def distance_to_camera(knownWidth, focalLength, perWidth):
    # compute and return the distance from the maker to the camera
    return (knownWidth * focalLength) / perWidth


#KNOWN_DISTANCE = 225
#KNOWN_WIDTH = 21.5
cap = cv2.VideoCapture(0)
while True:
    _, image = cap.read()
    #image = cv2.imread('Image-Test.jpg')
    original = image.copy()
    image = cv2.resize(image,(128, 128))
    #image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    lower = np.array([0, 100, 120], dtype="uint8")
    upper = np.array([45, 215, 255], dtype="uint8")
    mask = cv2.inRange(image, lower, upper)

    cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cnts = cnts[0] if len(cnts) == 2 else cnts[1]

    c = max(cnts, key = cv2.contourArea)
    x,y,w,h = cv2.boundingRect(c)
    print(w)
    cv2.rectangle(image, (x, y), (x + w, y + h), (36,255,12), 2)

    cv2.imshow('mask', mask)
    cv2.imshow('original', image)
    
    key = cv2.waitKey(1)
    if key==27:
        break

cv2.destroyAllWindows()