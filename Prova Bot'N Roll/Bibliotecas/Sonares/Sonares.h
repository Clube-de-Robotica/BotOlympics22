// =============================================================
// = Header File Sonares                        BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =
// =
// =
// =============================================================

// Header guards
#ifndef SONARES_H
#define SONARES_H

//----------------------------------------------------------
// Coment this line to disable the serial print
#define DEBUG

// This provides an easy way to debug and remove the
// Serial Prints Later
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif
//----------------------------------------------------------

#define _SONAR_AMOUNT 3

class Sonares
{
private:
    // LEFT, CENTER, RIGHT
    uint8_t _echoSonares[_SONAR_AMOUNT] = {6, 8, 10};
    uint8_t _triggerSonares[_SONAR_AMOUNT] = {7, 9, 11};
    float _AIRSPEED = 58.30903; // 343 M/s -> 2 times (Go and come back) -> 1 / (0.0343 / 2)

public:
    uint16_t getSonar(uint8_t, uint8_t);
    void getSonares(uint16_t Distance[]);
};
#endif