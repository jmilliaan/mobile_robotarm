#include <AccelStepper.h>

const int dir_1 = 4;
const int step_1 = 5;
const int dir_2 = 6;
const int step_2 = 7;
const int dir_3 = 8;
const int step_3 = 9;
const int dir_4 = 22;
const int step_4 = 24;
const int motor_interface_type = 1;

int motion_increment = 200;
const int n_motors = 4;
int pos_array[n_motors] = {
  200, 
  200, 
  200, 
  200
};
int spd_array[n_motors] = {
  1000,
  1000,
  1000,
  1000
};
int spd_array_rt[n_motors] = {
  1000, 
  -1000, 
  1000, 
  -1000
};
int spd_array_lt[n_motors] = {
  -1000, 
  1000, 
  -1000, 
  1000
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
  motor_2.setPinsInverted(true);
  motor_4.setPinsInverted(true);
  for(int stepper_n=0; stepper_n < n_motors; stepper_n++){
    steppers[stepper_n]->setMaxSpeed(1000);
    steppers[stepper_n]->setAcceleration(200);
    }
}

void loop() {
  int current_pos1 = motor_1.currentPosition();
  int current_pos2 = motor_2.currentPosition();
  int current_pos3 = motor_3.currentPosition();
  int current_pos4 = motor_4.currentPosition();

//  if(current_pos1 <= 5000){
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->setMaxSpeed(spd_array[stepper_n]);
//      steppers[stepper_n]->setSpeed(spd_array[stepper_n]);
//    }
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->move(pos_array[stepper_n]);
//    }
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->run();
//    }
//    Serial.print(current_pos1); Serial.print(" ");
//    Serial.print(current_pos2); Serial.print(" ");
//    Serial.print(current_pos3); Serial.print(" ");
//    Serial.print(current_pos4); Serial.println(" ");
//  }

  if(current_pos1 <= 5000000){
    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
      steppers[stepper_n]->setMaxSpeed(spd_array_rt[stepper_n]);
      steppers[stepper_n]->setSpeed(spd_array_rt[stepper_n]);
    }
    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
      steppers[stepper_n]->move(pos_array[stepper_n]);
    }
    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
      steppers[stepper_n]->run();
    }
    Serial.print(current_pos1); Serial.print(" ");
    Serial.print(current_pos2); Serial.print(" ");
    Serial.print(current_pos3); Serial.print(" ");
    Serial.print(current_pos4); Serial.println(" ");
  }
  
//  if(current_pos1 <= 10000){
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->setMaxSpeed(-spd_array[stepper_n]);
//      steppers[stepper_n]->setSpeed(-spd_array[stepper_n]);
//    }
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->move(pos_array[stepper_n]);
//    }
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      steppers[stepper_n]->run();
//    }
//    Serial.print(current_pos1); Serial.print(" ");
//    Serial.print(current_pos2); Serial.print(" ");
//    Serial.print(current_pos3); Serial.print(" ");
//    Serial.print(current_pos4); Serial.println(" ");
//  }
}
