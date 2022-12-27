//#include "constants.h"
#include "MultiStepper.h"
#include "AccelStepper.h"
#include <Wire.h>
#include <Servo.h>

#define dir_1 5
#define step_1 4
#define dir_2 6
#define step_2 7
#define dir_3 8
#define step_3 9
#define dir_4 12
#define step_4 13
#define motor_interface_type 1

#define claw_pin 46
#define arm_pin 45
#define wrist_pin 44
#define elbow_pin 11
#define base_pin 10

#define n_motors 4

#define slave_address 0x08

long pos_array_forward[n_motors] = {100, 100, 100, 100};
long pos_array_reverse[n_motors] = {-100, -100, -100, -100};
long pos_array_left[n_motors] = {100, -100, -100, 100};
long pos_array_right[n_motors] = {-100, 100, 100, -100};
long rotate_cw[n_motors] = {550, -550, 550, -550};
long rotate_ccw[n_motors] = {-600, 600, -600, 600};

byte d = 0;

Servo claw; Servo arm; Servo wrist; Servo elbow; Servo base;

int ds = 15;

AccelStepper motor_1(motor_interface_type, step_1, dir_1);
AccelStepper motor_2(motor_interface_type, step_2, dir_2);
AccelStepper motor_3(motor_interface_type, step_3, dir_3);
AccelStepper motor_4(motor_interface_type, step_4, dir_4);

MultiStepper mobile_robot;
AccelStepper* steppers[n_motors] = {&motor_1, &motor_2, &motor_3, &motor_4};


void move_joint(int joint, int pos){
  if(joint == 1){base.write(pos);};
  if(joint == 2){elbow.write(pos);};
  if(joint == 3){wrist.write(pos);};
  if(joint == 4){arm.write(pos);};
  if(joint == 5){claw.write(pos);};  
};

void move_joint_timed(int joint, int pos, long duration){
  if(joint == 1){
    int start_angle = base.read();
    unsigned long move_start_time = millis();
    unsigned long progress = millis() - move_start_time;
    while(progress <= duration){
      long angle = map(progress, 0, duration, start_angle, pos);
      base.write(angle);
      progress = millis()-move_start_time;
    };
  };
  if(joint == 2){
    int start_angle = elbow.read();
    unsigned long move_start_time = millis();
    unsigned long progress = millis() - move_start_time;
    while(progress <= duration){
      long angle = map(progress, 0, duration, start_angle, pos);
      elbow.write(angle);
      progress = millis()-move_start_time;
    };
  };
  if(joint == 3){
    int start_angle = wrist.read();
    unsigned long move_start_time = millis();
    unsigned long progress = millis() - move_start_time;
    while(progress <= duration){
      long angle = map(progress, 0, duration, start_angle, pos);
      wrist.write(angle);
      progress = millis()-move_start_time;
    };
  };
  if(joint == 5){
    int start_angle = arm.read();
    unsigned long move_start_time = millis();
    unsigned long progress = millis() - move_start_time;
    while(progress <= duration){
      long angle = map(progress, 0, duration, start_angle, pos);
      arm.write(angle);
      progress = millis()-move_start_time;
    };
  };
  if(joint == 4){
    int start_angle = claw.read();
    unsigned long move_start_time = millis();
    unsigned long progress = millis() - move_start_time;
    while(progress <= duration){
      long angle = map(progress, 0, duration, start_angle, pos);
      claw.write(angle);
      progress = millis()-move_start_time;
    };
  };
};

void claw_open(){move_joint_timed(5, 150, 1000);};
void claw_close(){move_joint_timed(5, 60, 1000);};

void lower_robot(){
  move_joint_timed(2, 180, 1000);
  move_joint_timed(4, 60, 600);
};

void raise_robot(){
  move_joint_timed(2, 90, 1000);
  move_joint_timed(4, 70, 1000);
};

void forward(){
  long new_pos[n_motors];
  for(int i=0; i<n_motors; i++){
    new_pos[i] = steppers[i]->currentPosition() + pos_array_forward[i];
  };
  mobile_robot.moveTo(new_pos);
  mobile_robot.runSpeedToPosition();
  };
  
void stop_robot(){
  long new_pos[n_motors];
  for(int i=0; i<n_motors; i++){
    new_pos[i] = steppers[i]->currentPosition();};
  mobile_robot.moveTo(new_pos);
  mobile_robot.runSpeedToPosition();
};

void turn_around(){
  long new_position[n_motors];
  for(int i=0; i<n_motors; i++){
    new_position[i]=steppers[i]->currentPosition() + rotate_cw[i];};
  mobile_robot.moveTo(new_position);
  mobile_robot.runSpeedToPosition();  
}

void receiveData(int bytecount){
  for (int i = 0; i < bytecount; i++) {
    d = Wire.read();
  }};

void setup(){
    Serial.begin(115200);
    Wire.begin(slave_address);
    Wire.onReceive(receiveData);

    claw.attach(claw_pin); 
    arm.attach(arm_pin); 
    wrist.attach(wrist_pin); 
    elbow.attach(elbow_pin); 
    base.attach(base_pin);
    motor_2.setPinsInverted(true);
    motor_4.setPinsInverted(true);

    for(int i=0; i<n_motors; i++){
      steppers[i]->setMaxSpeed(50);};
  
    mobile_robot.addStepper(motor_1); mobile_robot.addStepper(motor_2); mobile_robot.addStepper(motor_3); mobile_robot.addStepper(motor_4);
}

void loop(){
    //Serial.println(d);
    Serial.print(claw.read()); Serial.print(" "); 
    Serial.print(arm.read()); Serial.print(" "); 
    Serial.print(wrist.read()); Serial.print(" "); 
    Serial.print(elbow.read()); Serial.print(" "); 
    Serial.print(base.read());Serial.println(" "); 
    Serial.println("Raise Robot"); raise_robot();
    Serial.println("Claw Open"); claw_open();
    Serial.println("Lower Robot"); lower_robot();
    Serial.println("Claw Close"); claw_close();

//    if(d==0){forward();};
//    if(d==1){forward();Serial.println("FORWARD");}
//    else if(d==5){Serial.println("Turn Around Delay");delay(500);turn_around();Serial.println("TURN AROUND");delay(500);};
};
