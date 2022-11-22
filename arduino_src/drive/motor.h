#include "Arduino.h"

namespace motor{
  void intialize_motors();
  void set_speed(int motor_id, int speed);
  void step(int motor_id, int step_count);
  void forward(int dur);
  void reverse(int dur);
  void right(int dur);
  void left(int dur);
  
  }
