// =============================================================
// = Exemplo Sensor de Cor                      BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// = Descrição:
// = Este código permite testar o Sensor de Cor
// =
// =============================================================

#include <Arduino.h>
#include "botFCTUC.h"

botFCTUC jeff;

uint16_t RGBC[4];

void setup()
{
    Serial.begin(9600);
    Serial.println("Teste Sensor de Cor");

    jeff.begin();
}

void loop()
{
    jeff.getColor(RGBC);

    Serial.println("R: " + String(RGBC[0]) + "    G: " + String(RGBC[1]) + "    B: " + String(RGBC[2]) + "    C: " + String(RGBC[3]));

    delay(250);
}
