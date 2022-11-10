#include <Stepper.h> 
#define STEPS 200

Stepper stepper(STEPS, 8, 9); // Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver

#define motorInterfaceType 1

int Pval = 0;

int potVal = 0;

void motor_motion(int motor_id; int steps;){}

void mobile_robot_motion(int motor_1_val; int motor_2_val; int motor_3_val; int motor_4_val; ){}

void forward(){
  mobile_robot_motion(...);
}

void reverse(){
  mobile_robot_motion(...);
}


void setup() {
  stepper.setSpeed(1000);
}

void loop() {
  stepper.step(10);
}
