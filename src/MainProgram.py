import cv2

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
    return True


if __name__ == "__main__":
    
    needDetectToy = True
    needDetectBox = False
    needPickedUp = False
    needDropOff = False
    
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
            
        
        else:
            print("Merry Christmas your Program is Broken")
            
    