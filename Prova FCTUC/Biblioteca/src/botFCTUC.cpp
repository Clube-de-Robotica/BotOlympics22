// =============================================================
// = Function File botFTCUC                     BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =============================================================
#include "botFCTUC.h"

// =============================================================
// = Class Constructor and Destructor ==========================
// =============================================================

// Constructor
botFCTUC::botFCTUC()
{
    pinMode(motor1Dir, OUTPUT);
    pinMode(motor1PWM, OUTPUT);
    pinMode(motor2PWM, OUTPUT);
    pinMode(neopixel, OUTPUT);
    pinMode(motor2Dir, OUTPUT);
    pinMode(xshutRight, OUTPUT);
    pinMode(xshutFront, OUTPUT);
    pinMode(xhsutLeft, OUTPUT);
    pinMode(flameSensor, INPUT);
    pinMode(buttonPin, INPUT);

    // Setup Fan
    fanSetup();

} // End Constructor

// Destructor
botFCTUC::~botFCTUC()
{
} // End Destructor

// =============================================================
// = Fan Control Funtions ======================================
// =============================================================

void botFCTUC::fanSetup()
{
    pinMode(fanPin, OUTPUT);
    fanOff();
} // End fanSetup

// Turns fan on (Logic is Inverted!!)
void botFCTUC::fanOn()
{
    digitalWrite(fanPin, LOW);
} // End fanOn

// Turns fan off (Logic is Inverted!!)
void botFCTUC::fanOff()
{
    digitalWrite(fanPin, HIGH);
} // End fanOff

void botFCTUC::buttonSetup()
{
    pinMode(buttonPin, INPUT);
}

void botFCTUC::waitStart()
{
    while (!digitalRead(buttonPin))
    {
    }

    Serial.println("Starting Program!");
}

bool botFCTUC::readButton()
{
    return digitalRead(buttonPin);
}

void setupBuzzer()
{
    pinMode(buzzerPin, OUTPUT);
    buzzer_tone(0);
}

void buzzerPlay(int8_t val)
{
    analogWrite(buzzerPin, val);
}