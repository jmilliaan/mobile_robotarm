import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
 
 
class Motor():
    def __init__(self,EnaA,In1A,In2A,EnaB,In1B,In2B):
        self.EnaA= EnaA
        self.In1A = In1A
        self.In2A = In2A
        self.EnaB= EnaB
        self.In1B = In1B
        self.In2B = In2B
        GPIO.setup(self.EnaA,GPIO.OUT);GPIO.setup(self.In1A,GPIO.OUT);GPIO.setup(self.In2A,GPIO.OUT)
        GPIO.setup(self.EnaB,GPIO.OUT);GPIO.setup(self.In1B,GPIO.OUT);GPIO.setup(self.In2B,GPIO.OUT)
        self.pwmA = GPIO.PWM(self.EnaA, 130);
        self.pwmB = GPIO.PWM(self.EnaB, 130);
        self.pwmA.start(0);
        self.pwmB.start(0);
        self.mySpeed=0
 
    def move(self,speed=0.5,turn=0,t=0):
        speed *=100
        turn *=50
        leftSpeed = speed-turn
        #leftSpeed = 0
        rightSpeed = speed+turn
 
        if leftSpeed>100:
            leftSpeed =100
        elif leftSpeed<-100:
            leftSpeed = -100
        if rightSpeed>100:
            rightSpeed =100
        elif rightSpeed<-100:
            rightSpeed = -100
        #print(leftSpeed,rightSpeed)
        self.pwmA.ChangeDutyCycle(abs(leftSpeed*0.75))
        self.pwmB.ChangeDutyCycle(abs(rightSpeed*0.75))
            
        #self.pwmA.ChangeDutyCycle(100)
        #self.pwmB.ChangeDutyCycle(100)
        
        if leftSpeed>0:
            GPIO.output(self.In1A,GPIO.LOW)
            GPIO.output(self.In2A,GPIO.HIGH)
        else:
            GPIO.output(self.In1A,GPIO.HIGH)
            GPIO.output(self.In2A,GPIO.LOW)
        if rightSpeed>0:
            GPIO.output(self.In1B,GPIO.HIGH)
            GPIO.output(self.In2B,GPIO.LOW)
        else:
            GPIO.output(self.In1B,GPIO.LOW)
            GPIO.output(self.In2B,GPIO.HIGH)
        sleep(t)
 
    def stop(self,t=0):
        self.pwmA.ChangeDutyCycle(0);
        self.pwmB.ChangeDutyCycle(0);
        self.mySpeed=0
        sleep(t)
 
def main():
    motor.move(0.5,0,2)
    print("moved forward")
    motor.stop(2)
    motor.move(-0.5,0,2)
    print("moved backward")
    motor.stop(2)
    motor.move(0,0.5,2)
    print("moved right")
    motor.stop(2)
    motor.move(0,-0.5,2)
    print("moved left")
    motor.stop(2)
 
if __name__ == '__main__':
    motor= Motor(17,22,27,13,19,26)
    main()