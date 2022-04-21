// =============================================================
// = Exemplo Botão e Ventoinha                  BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// = Descrição:
// = Este código permite testar o botão e ventoinha do robô
// =
// =============================================================
#include <Arduino.h>
#include "botFCTUC.h"

botFCTUC jeff;

void setup()
{
    Serial.begin(9600);
    Serial.println("Teste Ventoinha e botao");

    jeff.begin();
}

void loop()
{
    if (jeff.readButton())
    {
        Serial.println("Ventoinha ON");
        jeff.fanOn(); // Liga a ventoinha
    }
    else
    {
        Serial.println("Ventoinha OFF");
        jeff.fanOff(); // Desliga a ventoinha
    }
    delay(250);
}
