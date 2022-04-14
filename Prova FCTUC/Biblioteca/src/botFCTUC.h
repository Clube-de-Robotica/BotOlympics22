// =============================================================
// = Header File botFTCUC                       BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =============================================================

// Guard Clauses
#ifndef __botFCTUC
#define __botFCTUC

#define motor1Dir 4    // Motor 1 - Dir
#define motor1PWM 5    // Motor 1 - PWM
#define motor2PWM 6    // Motor 2 - PWM
#define neopixel 7     // LED NeoPixel
#define motor2Dir 8    // Motor 2 - Dir
#define buzzerPin 9    // Buzzer
#define xshutRight 10  // XSHUT LiDAR Direita
#define xshutFront 11  // XSHUT LiDAR Frente
#define xhsutLeft 12   // XSHUT LiDAR Esquerda
#define flameSensor A0 // Sensor infravermelhos
#define buttonPin A1   // Botão
#define fanPin A2      // Ventoinha

class botFCTUC
{
private:
public:
    botFCTUC();
    ~botFCTUC();

    void setupMotores();
    void setupLidar();

    // Fan Control Routines
    void fanSetup();
    void fanOn();
    void fanOff();

    // Button Routines
    void buttonSetup();
    void waitStart();
    bool readButton();

    // Buzzer Routines
    void setupBuzzer();
    void buzzer_tone(int valor);
};
#endif