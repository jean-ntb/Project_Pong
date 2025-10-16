#ifndef JOYSTICK_INPUT_H
#define JOYSTICK_INPUT_H

#include <Arduino.h>


struct Joystick_Data
{
    uint8_t pin_X; // pin joystick X
    uint8_t pin_Y; // pin joystick Y
    uint8_t pin_button;
    int16_t center_X; // postion repox X
    int16_t center_Y; // postion repos Y 
    // zone morte
    int16_t dead_Zone; 
    // Stock les valeurs brutes de l'entrée analogique X 
    int16_t raw_X; 
    int16_t raw_Y;
    int16_t speed_X;
    int16_t speed_Y;
};

void joystick_Init(Joystick_Data* Joystick, uint8_t pin_x, uint8_t pin_y, uint8_t pin_button);
void joystick_Calibrate(Joystick_Data* joystick);
void joystick_Read(Joystick_Data* Joystick);
int16_t joystick_GetSpeedX(Joystick_Data* Joystick);
int16_t joystick_GetSpeedY(Joystick_Data* Joystick);
bool joystick_IsButtonPressed(Joystick_Data* Joystick);
void joystick_PrintDebug(Joystick_Data* Joystick);
#endif