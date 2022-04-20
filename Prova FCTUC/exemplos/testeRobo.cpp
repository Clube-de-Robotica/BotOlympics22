#include <Arduino.h>
#include "botFCTUC.h"

botFCTUC jeff;

void setup()
{
    jeff.begin(false, false);
    Serial.begin(9600);
    Serial.println("BOT FCTUC");
    jeff.waitStart();
}

void loop()
{
    //----------------------------------------------------------
    Serial.println("VENTOINHA");
    jeff.fanOn();
    delay(250);
    jeff.fanOff();
    //----------------------------------------------------------
    Serial.println("FLAME");
    for (int i = 0; i < 64; i++)
    {
        jeff.printFlame();
        delay(100);
    }
    //----------------------------------------------------------
    Serial.println("LIDARES");
    jeff.printI2C();
    for (int i = 0; i < 64; i++)
    {
        jeff.lidarPrint();
        delay(100);
    }
    delay(250);

    //----------------------------------------------------------
    Serial.println("Buzzer");
    jeff.buzzerPlay(255);
    delay(1000);
    jeff.buzzerPlay(0);

    //----------------------------------------------------------
    Serial.println("SENSOR COR");

    uint16_t RGB[4];

    for (int i = 0; i < 64; i++)
    {
        jeff.getColor(RGB);
        Serial.println("R: " + String(RGB[0]) + "    G: " + String(RGB[1]) + "    B: " + String(RGB[2]) + "    G: " + String(RGB[3]));
        delay(50);
    }
    //----------------------------------------------------------
    Serial.println("BOTAO");

    for (int i = 0; i < 255; i++)
    {
        Serial.println("Botão: " + String(jeff.readButton() ? "Pressionado!" : "OFF"));
        delay(50);
    }
    //----------------------------------------------------------
    Serial.println("MOTORES");

    for (int i = 0; i < 512; i++)
    {
        jeff.move(i - 255, i - 255);
        delay(50);
    }
    //----------------------------------------------------------
}