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
const int dir_4 = 12;
const int step_4 = 13;
const int motor_interface_type = 1;

const int n_motors = 4;

int pos_array_forward[n_motors] = {100, 100, 100, 100};
int pos_array_reverse[n_motors] = {-100, -100, -100, -100};
int pos_array_left[n_motors] = {-100, -100, -100, -100};
int pos_array_right[n_motors] = {100, 100, 100, 100};
int rotate_cw[n_motors] = {400, -400, 400, -400};
int rotate_ccw[n_motors] = {-100, 100, -100, 100};

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
  motor_2.setPinsInverted(true);
  motor_4.setPinsInverted(true);
  
  Serial.begin(115200);
  Wire.begin(slave_address);
  Wire.onReceive(receiveData);
  
  for(int stepper_n=0; stepper_n < n_motors; stepper_n++){
    steppers[stepper_n]->setMaxSpeed(400);
    steppers[stepper_n]->setAcceleration(100);}
}

void forward(){
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->move(pos_array_forward[stepper_n]);}
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->run();}
  Serial.println(" -> forward");}
  
void reverse(){
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->move(pos_array_reverse[stepper_n]);}
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->run();}
  Serial.println(" -> reverse");}

void stop_robot(){
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->stop();}
}

void turn_around(){
  int start = millis();
  int elapsed;
  
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    
    steppers[stepper_n]->moveTo(rotate_cw[stepper_n]);
    }
  for(int stepper_n=0; stepper_n <  n_motors; stepper_n++){
    steppers[stepper_n]->runToPosition();
    elapsed = millis() - start;
    }
  Serial.print("-->"); Serial.println(elapsed);
  Serial.println("---> turn_around");
//  if (elapsed > 1000){stop_robot();}
}

void receiveData(int bytecount){
  for (int i = 0; i < bytecount; i++) {
    data_to_echo = Wire.read();
  }
}

void loop() {
  Serial.println(data_to_echo);
//  forward();
  turn_around();
//  delay(1000);
//  if (data_to_echo==1){forward();}
//  else if (data_to_echo==5){turn_around();}
}
