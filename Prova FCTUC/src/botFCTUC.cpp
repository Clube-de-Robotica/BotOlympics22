#include "botFCTUC.h"

//
botFCTUC::botFCTUC()
{
    pinMode(motor1Dir, OUTPUT);
    pinMode(motor1PWM, OUTPUT);
    pinMode(motor2PWM, OUTPUT);
    pinMode(neopixel, OUTPUT);
    pinMode(motor2Dir, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(xshutRight, OUTPUT);
    pinMode(xshutFront, OUTPUT);
    pinMode(xhsutLeft, OUTPUT);
    pinMode(flameSensor, INPUT);
    pinMode(button, INPUT);
    pinMode(fan, OUTPUT);
}

botFCTUC::~botFCTUC()
{
}
