#include "Arduino.h"
#include "motor.h"
#include "Stepper.h"
#include "constants.h"

// Motor 1 -> Front Left. Numbering follows a clockwise pattern. 

Stepper motor_1(motor_steps, dir_1, step_1);
Stepper motor_2(motor_steps, dir_2, step_2);
Stepper motor_3(motor_steps, dir_3, step_3);
Stepper motor_4(motor_steps, dir_4, step_4);

namespace motor{

    void initialize_motors(){
        set_speed(1, default_speed);
        set_speed(2, default_speed);
        set_speed(3, default_speed);
        set_speed(4, default_speed);
    }

    void set_speed(int motor_id, int speed){
        if (motor_id == 1){motor_1.setSpeed(speed);}
        if (motor_id == 2){motor_2.setSpeed(speed);}
        if (motor_id == 3){motor_3.setSpeed(speed);}
        if (motor_id == 4){motor_4.setSpeed(speed);}
    }

    void step(int motor_id, int step_count){
        if (motor_id == 1){motor_1.step(step_count);}
        if (motor_id == 2){motor_2.step(step_count);}
        if (motor_id == 3){motor_3.step(step_count);}
        if (motor_id == 4){motor_4.step(step_count);}
    }

    void forward(int dur){
        // step(1, 0); step(2, 0); step(3, 0); step(4, 0);
    }

    void reverse(int dur){
        // step(1, 0); step(2, 0); step(3, 0); step(4, 0);
    }

    void right(int dur){
        // step(1, 0); step(2, 0); step(3, 0); step(4, 0);
    }

    void left(int dur){
        // step(1, 0); step(2, 0); step(3, 0); step(4, 0);
    }

}
