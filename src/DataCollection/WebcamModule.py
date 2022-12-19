import cv2

cap = cv2.VideoCapture(0)
def getImg(display= False,size=[128,128]):
    try:
        _, img = cap.read()
        orig = img.copy()
        img = cv2.resize(img,(size[0],size[1]))
        if display:
            cv2.imshow('Car Camera POV',img)
        return img, orig
    except Exception as e:
        print(str(e))
        raise


if __name__ == '__main__':
    while True:
        img = getImg(True)
        if cv2.waitKey(1) == 27: 
            break  # esc to quit
    cv2.destroyAllWindows()