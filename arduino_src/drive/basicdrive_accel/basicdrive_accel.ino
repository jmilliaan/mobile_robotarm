#include <AccelStepper.h>
#include <Wire.h>

#define slave_address 0x08
byte data_to_echo = 0;

const int dir_1 = 4;
const int step_1 = 5;
const int dir_2 = 6;
const int step_2 = 7;
const int dir_3 = 8;
const int step_3 = 9;
const int dir_4 = 10;
const int step_4 = 11;
const int motor_interface_type = 1;

int motion_increment = 200;
const int n_motors = 4;
int pos_array[n_motors] = {
  200, 
  -200, 
  -200, 
  200
};

AccelStepper motor_1(motor_interface_type, step_1, dir_1);
AccelStepper motor_2(motor_interface_type, step_2, dir_2);
AccelStepper motor_3(motor_interface_type, step_3, dir_3);
AccelStepper motor_4(motor_interface_type, step_4, dir_4);

AccelStepper* steppers[n_motors] = {
  &motor_1, 
  &motor_2, 
  &motor_3, 
  &motor_4, 
};
void setup() {
  Serial.begin(115200);
  Wire.begin(slave_address);
  Wire.onReceive(receiveData);
  for(int stepper_n=0; stepper_n < n_motors; stepper_n++){
    steppers[stepper_n]->setMaxSpeed(2000);
    steppers[stepper_n]->setAcceleration(400);
    }
}

void receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++) {
    data_to_echo = Wire.read();
    Serial.println(data_to_echo);
  }
}

void loop() {
  

  // int current_pos1 = motor_1.currentPosition();
  // int current_pos2 = motor_2.currentPosition();
  // int current_pos3 = motor_3.currentPosition();
  // int current_pos4 = motor_4.currentPosition();
  
  // for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
  //   steppers[stepper_n]->move(pos_array[stepper_n]);
  //   }
  // for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
  //   steppers[stepper_n]->run();
  //   }
  // Serial.print(current_pos1); Serial.print(" ");
  // Serial.print(current_pos2); Serial.print(" ");
  // Serial.print(current_pos3); Serial.print(" ");
  // Serial.print(current_pos4); Serial.println(" ");
  
 delay(100);
}
