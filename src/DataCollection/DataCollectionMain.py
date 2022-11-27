import WebcamModule as wM
import DataCollectionModule as dcM
import JoystickModule as jsM
import MotorModule as mM
import cv2
from time import sleep


# maxThrottle need to be adjusted to motor speed
maxThrottle = 0.25

# need to be adjusted to motor module pinout
motor = mM.Motor(17,22,27,13,19,26)

record = 0
while True:

    # need to check which button is which
    # this config is for 2 analog Joystick (Nintendo Switch Pro Controller)
    joyVal = jsM.getJS()
    steering = joyVal['axis1']
    throttle = joyVal['axis2']*maxThrottle

    # if record button pressed, start recording
    if joyVal['share'] == 1:
        if record ==0: print('Recording Started ...')
        record +=1
        sleep(0.200)
    if record == 1:
        img = wM.getImg(True,size=[240,120])
        dcM.saveData(img,steering)
    
    # when record button is pressed the second time, finish recording
    # save images and data as csv for training
    elif record == 2:
        dcM.saveLog()
        record = 0

    # negative is for direction, need to test
    motor.move(-throttle,-steering)
    cv2.waitKey(1)