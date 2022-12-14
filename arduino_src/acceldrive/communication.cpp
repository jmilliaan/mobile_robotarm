#include <Arduino.h>
#include "communication.h"
#include "constants.h"

using namespace communication;

namespace communication{
    String read_message(){
        String data;
        if (Serial.available() > 0){
            String data = Serial.readStringUntil('\n');
        }
        return data;
    }

    void write_message(String message){
        Serial.println(message);
    }
}
