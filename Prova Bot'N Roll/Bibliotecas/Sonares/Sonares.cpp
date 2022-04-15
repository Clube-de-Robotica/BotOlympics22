// =============================================================
// = Functions File Sonares                     BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =============================================================
#include "Sonares.h"
#include <Arduino.h>

/*!
  @brief Return the distance of all sonares
  @param Distance Returns the distances of the left, center and right sonar
*/
void Sonares::getSonares(uint16_t Distance[])
{
    for (int i = 0; i < _SONAR_AMOUNT; i++)
    {
        Distance[i] = getSonar(_triggerSonares[i], _echoSonares[i]);
    }
}

uint16_t Sonares::getSonar(uint8_t trigger, uint8_t echo)
{
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    uint16_t _sonarOut = pulseIn(echo, HIGH);
    delay(50);

    return (_sonarOut / 58.2);
}