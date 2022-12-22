#include <Servo.h>

Servo base;
Servo elbow;
Servo wrist;
Servo arm;
Servo claw;

int angle = 0;

int ds = 15;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  base.attach(7);
  base.write(angle);
  
//  elbow.attach(9);
//  elbow.write(angle);
//  
//  wrist.attach(10);
//  wrist.write(90);
//  
//  arm.attach(11);
//  arm.write(0);
//  
//  claw.attach(12);
//  claw.write(180);
}

void loop() {
  for(angle = 90; angle < 180; angle++)  
  {
    base.write(angle);
//    elbow.write(angle);
//    wrist.write(angle); 
//    arm.write(angle);
//    claw.write(angle);
    Serial.println(angle);
    delay(ds);                   
  } 
  for(angle = 180; angle > 0; angle--)    
  { 
    base.write(angle);
//    elbow.write(angle);
//    wrist.write(angle); 
//    arm.write(angle); 
//    claw.write(angle);
    Serial.println(angle);         
    delay(ds);       
  } 
  for(angle = 0; angle < 90; angle++)    
  { 
    base.write(angle);
//    elbow.write(angle);
//    wrist.write(angle);
//    arm.write(angle);
//    claw.write(angle);
    Serial.println(angle);         
    delay(ds);       
  } 
}
