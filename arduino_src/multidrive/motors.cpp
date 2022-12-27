#include "constants.h"
#include "MultiStepper.h"
#include "AccelStepper.h"

AccelStepper motor_1(motor_interface_type, step_1, dir_1);
AccelStepper motor_2(motor_interface_type, step_2, dir_2);
AccelStepper motor_3(motor_interface_type, step_3, dir_3);
AccelStepper motor_4(motor_interface_type, step_4, dir_4);

MultiStepper mobile_robot;
AccelStepper* steppers[n_motors] = {&motor_1, &motor_2, &motor_3, &motor_4};

void set_speed(){};

void forward(int distance){};

void reverse(int distance){};

void turn_cw(int angle){};

void turn_ccw(int angle){};

void turn_around(int direction){
    if(direction == 0){turn_cw(180);}
    else if(direction == 1){turn_ccw(180);}
};

void stop(){};
