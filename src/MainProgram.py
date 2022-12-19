from tensorflow.keras.models import load_model
from smbus import SMBus
from time import sleep
import numpy as np
import cv2
import imutils
import os



def MoveForward(i2c_obj, i2c_addr):
    #i2c_obj.write_byte(i2c_addr, 1)
    print("MoveForward")
    return 

def TurnAround(i2c_obj, i2c_addr):
    #i2c_obj.write_byte(i2c_addr, 5)
    print("TurnAround")
    return True

def PickUpToy():
    print("PickUpToy")
    return True

def DropOffToy():
    print("DropOffToy")
    return True

def PredictImage(flag, img):
    orig = img.copy()
    img = cv2.resize(img,(128, 128))
    img = img.astype("float") / 255.0
    label = ""
    x = 0
    
    if flag == "TOY":
        mask = cv2.inRange(img, lowerBlue, upperBlue)
        img = np.expand_dims(img, axis=0)
        (NoToy, Toy) = modelToy.predict(img)[0]
        label = "Toy" if Toy > NoToy else "No Toy"
        probability = max(Toy, NoToy)
        #label = "{}: {:.2f}%".format(label, probability * 100)
        
    else:
        mask = cv2.inRange(img, lowerYellow, upperYellow)
        img = np.expand_dims(img, axis=0)
        (NoBox, Box) = modelBox.predict(img)[0]
        label = "Box" if Box > NoBox else "No Box"
        probability = max(Box, NoBox)
        #label = "{}: {:.2f}%".format(label, probability * 100)
    try:
        cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if len(cnts) == 2 else cnts[1]
        c = max(cnts, key = cv2.contourArea)
        x,y,w,h = cv2.boundingRect(c)
        
    except ValueError:
        continue
    
    #orig = imutils.resize(orig, width = 400)
    #cv2.putText(orig, label, (200,25), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (200, 2255, 40), 2)
    return label, probability, img, orig, x



if __name__ == "__main__":
    addr = 0x08
    #bus = SMBus(1)
    bus = "dummy"
    #sleep(3)
    
    needDetectToy = True
    needDetectBox = False
    needPickedUp = False
    needDropOff = False
    threshold_toy_w = 60
    threshold_box_w = 120
    
    lowerBlue = np.array([100, 30, 0], dtype="uint8")
    upperBlue = np.array([150, 100, 50], dtype="uint8")
    
    lowerYellow = np.array([0, 100, 120], dtype="uint8")
    upperYellow = np.array([45, 215, 255], dtype="uint8")

    
    print("[INFO] loading network toy")
    modelToy = load_model("ToyNoToy.model")
    print("[INFO] loading network box")
    modelBox = load_model("ToyBoxNoToyBox.model")
    
    cap = cv2.VideoCapture(0)
        
    while True:
        _, img = cap.read()
        
        if needDetectToy:
            print("Now finding toy")
            label, probability, img, orig, w_toy = PredictImage("TOY", img)
            print("Toy prob. Label: {}, Probs: {}".format(label, probability))
            
                        
            if label == "Toy":
                if w_toy > threshold_toy_w:
                    needDetectToy = False
                    needPickedUp = True
                else:
                    MoveForward(bus, addr)
                
                
        elif needPickedUp:
            isPickedUp = PickUpToy()
            if isPickedUp:
                isTurned = TurnAround(bus, addr)
                needDetectBox = True
                needPickedUp = False
        
        elif needDetectBox:
            print("Now finding box")
            label, probability, img, orig, w_box = PredictImage("BOX", img)
            print("Box prob. Label: {}, Probs: {}".format(label, probability))
            
            
            if label == "Box":
                if w_box > threshold_box_w:
                    needDetectBox = False
                    needDropOff = True
                else:
                    MoveForward(bus, addr)
            

        elif needDropOff:
            isDroppedOff = DropOffToy()
            if isDroppedOff:
                isTurned = TurnAround(bus, addr)
                needDetectToy = True
                needDroppedOff = False
            
        
        else:
            print("Merry Christmas your Program is Broken")
            
        key = cv2.waitKey(1)
        if key==27:
            break
            
    cv2.destroyAllWindows()