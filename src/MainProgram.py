import cv2
<<<<<<< Updated upstream

from DataCollection import WebcamModule as WM
from smbus import SMBus
from time import sleep

def MoveForward():
    return

def TurnAround():
    return True

def PickUpToy():
    return True

def DropOffToy():
=======
import imutils
import os
i2c_address = 0x08

COMMAND = {
    "stop":0,
    "forward": 1, 
    "reverse": 2,
    "right":3, 
    "left":4, 
    "turn_around": 5, 
    "pick_up_toy": 6, 
    "drop_off_toy": 7}

def MoveForward(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, COMMAND["forward"])
    print("MoveForward")
    return 

def TurnAround(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, COMMAND["turn_around"])
    print("TurnAround")
    return True

def PickUpToy(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, COMMAND["pick_up_toy"])
    print("PickUpToy")
    return True

def DropOffToy(i2c_obj, i2c_addr):
    i2c_obj.write_byte(i2c_addr, COMMAND["drop_off_toy"])
    print("DropOffToy")
>>>>>>> Stashed changes
    return True


if __name__ == "__main__":
<<<<<<< Updated upstream
=======
    communication = SMBus(1)

    sleep(1)
>>>>>>> Stashed changes
    
    needDetectToy = True
    needDetectBox = False
    needPickedUp = False
    needDropOff = False
<<<<<<< Updated upstream
    
    while True:
        if needDetectToy:
            ## detect image here
            ## model here, predict
            toyDetected = True
            if toyDetected:
                MoveForward()
                ## predict distance
            distance_toy = 0
            threshold_toy = 5
            if distance < threshold_toy:
                needDetectToy = False
                needPickedUp = True
                
                
        else if needPickedUp:
            isPickedUp = PickUpToy()
            if isPickedUp:
                isTurned = TurnAround()
                needDetectBox = True
                needPickedUp = False
        
        else if needDetectBox:
            ## detect image here
            ## model here, predict
            boxDetected = True
            if boyxDetected:
                MoveForward()
                ## predict distance
            distance_box = 0
            threshold_box = 5
            if distance < threshold_box:
                needDetectBox = False
                needDropOff = True
        
        else if needDropOff:
            isDroppedOff = DropOffToy()
            if isDroppedOff:
                isTurned = TurnAround()
                needDetectToy = True
                needDroppedOff = False
=======
    threshold_toy_w = 15
    threshold_box_w = 115
    
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
        _, orig = cap.read()
        if needDetectToy:
            label, orig, w_toy = PredictImage("TOY", orig)
            
                        
            if label == "Toy":
                print("w_toy: {}".format(w_toy))
                if w_toy > threshold_toy_w:
                    needDetectToy = False
                    needPickedUp = True
                else:
                    MoveForward(communication, i2c_address)
                
                
        elif needPickedUp:
            isPickedUp = PickUpToy(communication, i2c_address)
            if isPickedUp:
                isTurned = TurnAround(communication, i2c_address)
                sleep(1)
                print("turnaround sleep")
                needDetectBox = True
                needPickedUp = False
                communication.write_byte(i2c_address, 0)
        
        elif needDetectBox:
            label, orig, w_box = PredictImage("BOX", orig)
            
            
            if label == "Box":
                print("w_box: {}".format(w_box))
                if w_box > threshold_box_w:
                    needDetectBox = False
                    needDropOff = True
                else:
                    MoveForward(communication, i2c_address)
            

        elif needDropOff:
            isDroppedOff = DropOffToy(communication, i2c_address)
            if isDroppedOff:
                isTurned = TurnAround(communication, i2c_address)
                sleep(1)
                print("turnaround sleep")
                needDetectToy = True
                needDroppedOff = False
                communication.write_byte(i2c_address, 0)
>>>>>>> Stashed changes
            
        
        else:
            print("Merry Christmas your Program is Broken")
            
<<<<<<< Updated upstream
    
=======
    cv2.destroyAllWindows()
>>>>>>> Stashed changes
