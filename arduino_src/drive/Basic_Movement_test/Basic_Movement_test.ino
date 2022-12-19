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

const int n_motors = 4;

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

int pos_array[n_motors] = {
  200, 
  200, 
  200, 
  200
};

int spd_1 = 1000;
int spd_2 = 1000;
int spd_3 = 1000;
int spd_4 = 1000;

int spd_array[n_motors] = {
  spd_1, 
  spd_2, 
  spd_3, 
  spd_4
};

int y = 1000;
int x;
bool up = false;

void setup() {
  Serial.begin(115200);
  motor_2.setPinsInverted(true);
  motor_4.setPinsInverted(true);
  for(int stepper_n=0; stepper_n < n_motors; stepper_n++){
    steppers[stepper_n]->setMaxSpeed(2000);
    steppers[stepper_n]->setSpeed(2000);
    steppers[stepper_n]->setAcceleration(200);
    }
}

void loop() {
    int current_pos1 = motor_1.currentPosition();
    int current_pos2 = motor_2.currentPosition();
    int current_pos3 = motor_3.currentPosition();
    int current_pos4 = motor_4.currentPosition();

    if(up==false){
      x = 2000 -abs(y);
    } else {
      x = -2000 + abs(y);
    }

    spd_1 = x+y;
    spd_2 = -x+y;
    spd_3 = -x+y;
    spd_4 = x+y; 
    int kopling = 0;
//    for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
//      Serial.println(kopling);
//      steppers[stepper_n]->setSpeed(spd_array[stepper_n]);
//      if(spd_1%200==0){
//        motor_1.setSpeed(spd_1);
//      }
//      if(spd_2%200==0){
//        motor_2.setSpeed(spd_2);
//      }
//      if(spd_3%200==0){
//        motor_3.setSpeed(spd_3);
//      }
//      if(spd_4%200==0){
//        motor_4.setSpeed(spd_4);
//      }
      
//      motor_2.setSpeed(spd_2);
//      motor_3.setSpeed(spd_3);
//      motor_4.setSpeed(spd_4);
      
//      steppers[stepper_n]->move(pos_array[stepper_n]);
//      steppers[stepper_n]->run();
//      kopling++;
//    }
    for (int stepper_n=0; stepper_n<n_motors;stepper_n++){
      steppers[stepper_n]->move(pos_array[stepper_n]);
    }

    for (int stepper_n=0; stepper_n<n_motors;stepper_n++){
      steppers[stepper_n]->run();
    }

    
    Serial.print("Pos 1:"); Serial.print(current_pos1); Serial.print(" ");
    Serial.print("Pos 2:"); Serial.print(current_pos2); Serial.print(" ");
    Serial.print("Pos 3:"); Serial.print(current_pos3); Serial.print(" ");
    Serial.print("Pos 4:"); Serial.print(current_pos4); Serial.print(" ");
    Serial.print("x   :"); Serial.print(x); Serial.print(" ");
    Serial.print("y   :"); Serial.print(y); Serial.print(" ");
    Serial.print("spd 1:"); Serial.print(spd_1); Serial.print(" ");
    Serial.print("spd 2:"); Serial.print(spd_2); Serial.print(" ");
    Serial.print("spd 3:"); Serial.print(spd_3); Serial.print(" ");
    Serial.print("spd 4:"); Serial.print(spd_4); Serial.println(" ");

    if(up==false){
      y = y - 1;
      if(y == -2000){
        up = true;
      }
    } else {
      y = y + 1;
      if(y == 2000){
        up = false;
      }
    }
}
