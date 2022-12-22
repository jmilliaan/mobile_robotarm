  #include "constants.h"
#include "motor.h"
#include "communication.h"

using namespace motor;
using namespace communication;

void setup() {
    Serial.begin(baud_rate);
    initialize_motors();
    read_message();
}

void loop() {
//    step(1, 100);
//    step(2, 100);
//    step(3, 100);
//    step(4, 100);
//    delay(500);
}
