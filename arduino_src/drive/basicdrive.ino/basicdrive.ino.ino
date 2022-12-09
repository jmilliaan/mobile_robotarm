#include "Arduino.h"
#include "Stepper.h"

const int dir_1 = 4;
const int step_1 = 5;
const int dir_2 = 6;
const int step_2 = 7;
const int dir_3 = 8;
const int step_3 = 9;
const int dir_4 = 10;
const int step_4 = 11;
Stepper motor_1(200, dir_1, step_1);
Stepper motor_2(200, dir_2, step_2);
Stepper motor_3(200, dir_3, step_3);
Stepper motor_4(200, dir_4, step_4);

void setup() {
  Serial.begin(115200);
  
  motor_1.setSpeed(500);
  motor_2.setSpeed(500);
  motor_3.setSpeed(500);
  motor_4.setSpeed(500);

}

void loop() {
  motor_1.step(300);
  motor_2.step(300);
  motor_3.step(300);
  motor_4.step(300);
  delay(200);
}
