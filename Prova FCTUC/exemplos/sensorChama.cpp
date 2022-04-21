// =============================================================
// = Exemplo Sensor de Chama                    BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// = Descrição:
// = Este código permite ler os valores devolvidos pelo sensor
// = de chama. As entradas analógicas da placa arduino usada têm
// = um ADC de 8 bits, logo o valor é entre 0 a 1023.
// = Para obteres os valor limiar da deteção de chama observa os
// = valores devolvidos pelo sensor quando o mesmo está apontado
// = a uma vela acessa e quando está apontado apenas a luz
// = ambiente.
// =
// = Para testares o teu valor ajusta o flameTreshold para o
// = valor obtido, e verifica se o sensor está realmente a
// = detetar a chama
// =
// =============================================================
#include <Arduino.h>
#include "botFCTUC.h"

const int flameTreshold = 300; // Altera este valor consoante o teu sensor!

botFCTUC jeff;

void setup()
{
    Serial.begin(9600);
    jeff.begin();

    Serial.println("Teste sensor Chama");
}

void loop()
{
    int sensorValue = jeff.getFlame();

    Serial.print("Valor Sensor: " + String(sensorValue));
    Serial.println("\tChama detetada: " + String((sensorValue <= flameTreshold) ? "Sim!" : "Nao!"));
    delay(250);
}