#include <Arduino.h>

unsigned long currentMillis = 0;

const long intervalPlim = 1000;
unsigned long previousMillisPlim = 0;

const long intervalPing = 500;
unsigned long previousMillisPing = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    currentMillis = millis();

    // Plim de 1 segundo em 1 segundo
    if (currentMillis - previousMillisPlim >= intervalPlim)
    {
        Serial.println("Plim! Plim!");

        previousMillisPlim = currentMillis;
    }

    // Ping de 500 milisegundos em 500 milisegundos
    if (currentMillis - previousMillisPing >= intervalPing)
    {
        Serial.println("Ping!");

        previousMillisPing = currentMillis;
    }
}