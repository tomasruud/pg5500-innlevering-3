#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "Arduino.h"

#define JS_THRESHOLD 32

typedef enum JoystickDirection {
  JS_None,
  JS_Left,
  JS_Up,
  JS_Down,
  JS_Right
};

JoystickDirection get_joystick_vertical_direction(uint16_t y);

#endif
