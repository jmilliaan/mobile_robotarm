#include <Stepper.h> 

#define STEPS 200


// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver

Stepper stepper_lr(STEPS, 2, 3); // Stepper kanan depan (right front), Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver
Stepper stepper_lf(STEPS, 4, 5); // Stepper kanan belakang (right rear), Pin 4 connected to DIRECTION & Pin 4 connected to STEP Pin of Driver
Stepper stepper_rr(STEPS, 6, 7); // Stepper kiri depan (left front), Pin 6 connected to DIRECTION & Pin 7 connected to STEP Pin of Driver
Stepper stepper_rf(STEPS, 22, 23); // Stepper kiri belakang (left rear), Pin 22 connected to DIRECTION & Pin 23 connected to STEP Pin of Driver


#define motorInterfaceType 1


void setup() {
  // Set the maximum speed in steps per second:
  stepperSetSpeed(1000, 1000, 1000, 1000);
  
}

void loop() {
  stepperStep(10, 10, 10, 10);
}

void stepperSetSpeed(int rf, int rr, int lf, int lr){
  stepper_rf.setSpeed(rf);
  stepper_rr.setSpeed(rr);
  stepper_lf.setSpeed(lf);
  stepper_lr.setSpeed(lr);
}

void stepperStep(int rf, int rr, int lf, int lr){
  stepper_rf.step(rf);
  stepper_rr.step(rr);
  stepper_lf.step(lf);
  stepper_lr.step(lr);
}
