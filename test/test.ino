#include <MultiStepper.h>
#include <AccelStepper.h>
const int dir_1 = 5;
const int step_1 = 4;
const int dir_2 = 6;
const int step_2 = 7;
const int dir_3 = 8;
const int step_3 = 9;
const int dir_4 = 12;
const int step_4 = 13;
const int motor_interface_type = 1;

const int n_motors = 4;

long pos_array_forward[n_motors] = {100, 100, 100, 100};
long pos_array_reverse[n_motors] = {-100, -100, -100, -100};
long pos_array_left[n_motors] = {100, -100, -100, 100};
long pos_array_right[n_motors] = {-100, 100, 100, -100};
long rotate_cw[n_motors] = {600, -600, 600, -600};
long rotate_ccw[n_motors] = {-600, 600, -600, 600};

AccelStepper motor_1(motor_interface_type, step_1, dir_1);
AccelStepper motor_2(motor_interface_type, step_2, dir_2);
AccelStepper motor_3(motor_interface_type, step_3, dir_3);
AccelStepper motor_4(motor_interface_type, step_4, dir_4);

MultiStepper mobile_robot;

AccelStepper* steppers[n_motors] = {
  &motor_1, 
  &motor_2, 
  &motor_3, 
  &motor_4, 
};

void traverse_right(){
  long target_position[n_motors];
  for(int i=0; i<n_motors; i++){
    long target_pos = steppers[i]->currentPosition() + pos_array_right[i];
    target_position[i] = target_pos;
    Serial.print(target_pos); Serial.print(" ");
  };
  mobile_robot.moveTo(target_position);
  mobile_robot.runSpeedToPosition();
  };

void traverse_left(){
  long target_position[n_motors];
  for(int i=0; i<n_motors; i++){
    long target_pos = steppers[i]->currentPosition() + pos_array_left[i];
    target_position[i] = target_pos;
    Serial.print(target_pos); Serial.print(" ");
  };
  mobile_robot.moveTo(target_position);
  mobile_robot.runSpeedToPosition();
  };

void turn_around(){
  long current_position[n_motors] = {
    motor_1.currentPosition(), 
    motor_2.currentPosition(), 
    motor_3.currentPosition(), 
    motor_4.currentPosition()
    };
  long target_position[n_motors];
  for(int i=0; i<n_motors; i++){
    long target_pos = current_position[i] + rotate_cw[i];
    target_position[i] = target_pos;
    Serial.print(target_pos); Serial.print(" ");
    };
  mobile_robot.moveTo(target_position);
  mobile_robot.runSpeedToPosition();
  Serial.println(" Turn Around");
  }

void setup() {
  motor_2.setPinsInverted(true);
  motor_4.setPinsInverted(true);
  Serial.begin(9600);
  mobile_robot.addStepper(motor_1);
  mobile_robot.addStepper(motor_2);
  mobile_robot.addStepper(motor_3);
  mobile_robot.addStepper(motor_4);
  
  for(int stepper_n=0; stepper_n < n_motors; stepper_n++){
    steppers[stepper_n]->setMaxSpeed(150);
    steppers[stepper_n]->setAcceleration(80);}
  Serial.println("begin, 3s delay");
  delay(3000);
//  mobile_robot.moveTo(pos_array_reverse);
//  mobile_robot.runSpeedToPosition();
//  Serial.println("reverse all wheels to 200");
}

void loop(){
  traverse_right();
  delay(1000);
  traverse_left();
  delay(1000);
  };
