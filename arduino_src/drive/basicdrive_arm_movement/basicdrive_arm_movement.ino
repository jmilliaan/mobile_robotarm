#include <Servo.h>

Servo base;
Servo elbow;
Servo wrist;
Servo arm;
Servo claw;

int ds = 15;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  base.attach(8);
  base.write(180);
  
  elbow.attach(9);
  elbow.write(180);
  
  wrist.attach(10);
  wrist.write(90);
  
  arm.attach(11);
  arm.write(0);
  
  claw.attach(12);
  claw.write(90);

  delay(2000);

  base.write(180);

  delay(1000);
  
  claw.write(180);
  elbow.write(90);
  arm.write(90);

  delay(2000);

  // Claw max 110, 120 for safe.
  claw.write(120);
}

void loop() {
}
