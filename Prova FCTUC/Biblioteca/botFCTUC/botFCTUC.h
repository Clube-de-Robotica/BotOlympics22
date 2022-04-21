// =============================================================
// = Header File botFTCUC                       BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =
// = Hardware Mapping
// = |---------------------|--------|
// = |     Descrição       |  Pino  |
// = |---------------------|--------|
// = |Motor 1 - Dir        |    4   |
// = |---------------------|--------|
// = |Motor 1 - PWM        |    5   |
// = |---------------------|--------|
// = |Motor 2 - PWM        |    6   |
// = |---------------------|--------|
// = |LED NeoPixel         |    7   |
// = |---------------------|--------|
// = |Motor 2 - Dir        |    8   |
// = |---------------------|--------|
// = |Buzzer               |    9   |
// = |---------------------|--------|
// = |XSHUT LiDAR Direita  |   10   |
// = |---------------------|--------|
// = |XSHUT LiDAR Frente   |   11   |
// = |---------------------|--------|
// = |XSHUT LiDAR Esquerda |   12   |
// = |---------------------|--------|
// = |Sensor infravermelhos|   A0   |
// = |---------------------|--------|
// = |Botão                |   A1   |
// = |---------------------|--------|
// = |Ventoinha            |   A2   |
// = |---------------------|--------|
// =
// =
// =============================================================

// Header guards
#ifndef BOT_FCTUC_H
#define BOT_FCTUC_H

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
// Auxiliry Define
#define ESQUERDA 1
#define CENTRO 2
#define DIREITA 3

//----------------------------------------------------------
// Auxiliry Libraries
#include <Wire.h>
//----------------------------------------------------------
// External Auxiliry Libraries
#include <./external/Adafruit_NeoPixel.h>
#include <./external/Adafruit_TCS34725.h>
#include <./external/VL53L0X.h>
//----------------------------------------------------------

class botFCTUC
{
private:
    // Pin Declarations
    const uint8_t _motor1Dir = 4;    // Motor 1 - Dir
    const uint8_t _motor1PWM = 5;    // Motor 1 - PWM
    const uint8_t _motor2PWM = 6;    // Motor 2 - PWM
    const uint8_t _neopixelPin = 7;  // LED NeoPixel
    const uint8_t _motor2Dir = 8;    // Motor 2 - Dir
    const uint8_t _buzzerPin = 9;    // Buzzer
    const uint8_t _xshutRight = 10;  // XSHUT LiDAR Direita
    const uint8_t _xshutFront = 11;  // XSHUT LiDAR Frente
    const uint8_t _xshutLeft = 12;   // XSHUT LiDAR Esquerda
    const uint8_t _flameSensor = A0; // Sensor infravermelho
    const uint8_t _buttonPin = A1;   // Botão
    const uint8_t _fanPin = A2;      // Ventoinha
    //----------------------------------------------------------
    // Neopixel Led
    Adafruit_NeoPixel *_pixel;
    //----------------------------------------------------------
    // Some Vars
    uint32_t _previousMillis = 0;
    bool isGreen = false;
    //----------------------------------------------------------
    // Color Sensor
    Adafruit_TCS34725 _colorSensor;
    //----------------------------------------------------------
    // Motors Polarity
    const uint8_t _maxPwm = 255;
    bool _isMotor1Correct = true;
    bool _isMotor2Correct = true;
    //----------------------------------------------------------
    // LiDAR's
    const uint8_t _lidarLeftAddr = 0x70;
    const uint8_t _lidarFrontAddr = 0x71;
    const uint8_t _lidarRightAddr = 0x72;

    const uint16_t _lidarDistMin = 0;
    const uint16_t _lidarDistMax = 2600;

    VL53L0X _lidarLeft;
    VL53L0X _lidarFront;
    VL53L0X _lidarRight;
    //----------------------------------------------------------
    // Setup Functions
    void setupFan();
    void setupButton();
    void setupBuzzer();
    void setupNeopixel();
    void setupFlame();
    bool setupColorSensor();
    void setupMotores(bool isMotor1Correct, bool isMotor2Correct);
    void setupLidar();
    void setAddressLidar(VL53L0X &LIDAR, uint8_t new_addr);
    //----------------------------------------------------------

public:
    botFCTUC();
    ~botFCTUC();

    void begin(bool M1 = true, bool M2 = true);

    // Fan Control Routines
    void fanOn();
    void fanOff();

    // Button Routines
    void waitStart();
    bool readButton();

    // Buzzer Routines
    void buzzerPlay(uint8_t val);

    // NeoPixel Routines
    void pixelSetColor(uint8_t Red, uint8_t Green, uint8_t Blue);
    void pixelSetBrightness(uint8_t Brightness);

    // Flame Sensor
    uint16_t getFlame();
    void printFlame();

    // Color Sensor
    void getColor(uint16_t RGBC[]);
    void enableColorSensor();
    void disableColorSensor();

    // Motors
    void moveMotor1(int16_t pwm);
    void moveMotor2(int16_t pwm);
    void move(int16_t pwmM1, int16_t pwmM2);
    void stopMotors();

    // Lidars
    uint16_t lidarGetDistance(uint8_t lidarLocation);
    void printI2C();
    void lidarPrint();
};
#endif
