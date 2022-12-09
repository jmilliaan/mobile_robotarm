#include <Stepper.h> 

#define STEPS 200


// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver

Stepper stepper(STEPS, 8, 9); // Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver

#define motorInterfaceType 1

int Pval = 0;

int potVal = 0;


void setup() {

  // Set the maximum speed in steps per second:

  stepper.setSpeed(1000);

}

void loop() {
  stepper.step(10);
}
