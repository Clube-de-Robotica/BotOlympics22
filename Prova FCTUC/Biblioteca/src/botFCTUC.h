
#ifndef __botFCTUC__
#define __botFCTUC__

#define motor1Dir 4    // Motor 1 - Dir
#define motor1PWM 5    // Motor 1 - PWM
#define motor2PWM 6    // Motor 2 - PWM
#define neopixel 7     // LED NeoPixel
#define motor2Dir 8    // Motor 2 - Dir
#define buzzer 9       // Buzzer
#define xshutRight 10  // XSHUT LiDAR Direita
#define xshutFront 11  // XSHUT LiDAR Frente
#define xhsutLeft 12   // XSHUT LiDAR Esquerda
#define flameSensor A0 // Sensor infravermelhos
#define button A1      // Botão
#define fan A2         // Ventoinha

class botFCTUC
{
private:
public:
    botFCTUC();
    ~botFCTUC();

    void setupMotores();
    void setupLidar();
};
#endif