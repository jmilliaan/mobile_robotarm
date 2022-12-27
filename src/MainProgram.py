from tensorflow.keras.models import load_model
from smbus import SMBus
from time import sleep
import numpy as np
import cv2
import imutils
import os



def MoveForward(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, 1)
    print("MoveForward")
    return 

def TurnAround(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, 5)
    print("TurnAround")
    return True

def PickUpToy():
    #i2c_obj.write_byte(i2c_addr, 7)
    print("PickUpToy")
    return True

def DropOffToy():
    #i2c_obj.write_byte(i2c_addr, 8)
    print("DropOffToy")
    return True

def PredictImage(flag, img):
    img = cv2.resize(img,(128, 128))
    orig = img.copy()
    imgPredict = img.astype("float") / 255.0
    label = ""
    w = 0
    
    if flag == "TOY":
        mask = cv2.inRange(img, lowerBlue, upperBlue)
        imgPredict = np.expand_dims(imgPredict, axis=0)
        (NoToy, Toy) = modelToy.predict(imgPredict)[0]
        label = "Toy" if Toy > NoToy else "No Toy"
        probability = max(Toy, NoToy)
        
    else:
        mask = cv2.inRange(img, lowerYellow, upperYellow)
        imgPredict = np.expand_dims(imgPredict, axis=0)
        (NoBox, Box) = modelBox.predict(imgPredict)[0]
        label = "Box" if Box > NoBox else "No Box"
        probability = max(Box, NoBox)
        
    try:
        cnts = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if len(cnts) == 2 else cnts[1]
        c = max(cnts, key = cv2.contourArea)
        x,y,w,h = cv2.boundingRect(c)
        cv2.rectangle(orig, (x, y), (x + w, y + h), (36,255,12), 2)
    except:
        pass
    
    #orig = imutils.resize(orig, width = 400)
    labelInImg = "{}: {:.2f}%".format(label, probability * 100)
    cv2.putText(orig, labelInImg, (10,10), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (200, 255, 40), 2)
    return label, orig, w



if __name__ == "__main__":
    addr = 0x08
    bus = SMBus(1)
    #addr = ""
    #bus = ""
    sleep(3)
    
    needDetectToy = True
    needDetectBox = False
    needPickedUp = False
    needDropOff = False
    threshold_toy_w = 16
    threshold_box_w = 120
    
    lowerBlue = np.array([100, 30, 0], dtype="uint8")
    upperBlue = np.array([255, 100, 50], dtype="uint8")
    
    lowerYellow = np.array([0, 100, 120], dtype="uint8")
    upperYellow = np.array([100, 255, 255], dtype="uint8")

    
    print("[INFO] loading network toy")
    modelToy = load_model("ToyNoToy.model")
    print("[INFO] loading network box")
    modelBox = load_model("ToyBoxNoToyBox.model")
    
    cap = cv2.VideoCapture(0)
        
    while True:       
        #try:
        _, orig = cap.read()
        # bus.write_byte(addr, 0)
        if needDetectToy:
            label, orig, w_toy = PredictImage("TOY", orig)
            
                        
            if label == "Toy":
                print("w_toy: {}".format(w_toy))
                if w_toy > threshold_toy_w:
                    needDetectToy = False
                    needPickedUp = True
                else:
                    MoveForward(bus, addr)
                
                
        elif needPickedUp:
            isPickedUp = PickUpToy()
            if isPickedUp:
                isTurned = TurnAround(bus, addr)
                sleep(1)
                print("turnaround sleep")
                needDetectBox = True
                needPickedUp = False
                bus.write_byte(addr, 0)
        
        elif needDetectBox:
            label, orig, w_box = PredictImage("BOX", orig)
            
            
            if label == "Box":
                print("w_box: {}".format(w_box))
                if w_box > threshold_box_w:
                    needDetectBox = False
                    needDropOff = True
                else:
                    MoveForward(bus, addr)
            

        elif needDropOff:
            isDroppedOff = DropOffToy()
            if isDroppedOff:
                isTurned = TurnAround(bus, addr)
                sleep(1)
                print("turnaround sleep")
                needDetectToy = True
                needDroppedOff = False
                bus.write_byte(addr, 0)
            
        
        else:
            print("Merry Christmas your Program is Broken")
        
        cv2.imshow('Car Vision', orig)
        key = cv2.waitKey(1)
        if key==27:
            break
            
            
    cv2.destroyAllWindows()