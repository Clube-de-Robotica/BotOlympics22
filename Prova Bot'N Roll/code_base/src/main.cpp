/***
 This example was created by Dylan Denizon (dylandfd@gmail.com)
 on the 18th April 2022

 This code was made for the Bot'n Roll part of the Bot Olympics competition.
 https://botolympics.pt/

Description:
This file contains the code that serves as a base to start programming with the Bot'n Roll robots,
dealing with the initiation of sensors and libraries in order to facilitate integration with the robots.
Participants are advised to only write code inside the beacons:

** USER CODE BEGIN code **

// place here your code

** CODE END code **

in order to help in the organization of code beings and not to harm the initialization of sensors and libraries.
Good luck and have fun
*/

/* PRIVATE CODE BEGIN Includes */
#include <Arduino.h>
#include <BnrOneA.h>
#include <Sonar.h>
#include <SPI.h>
/* USER CODE BEGIN Includes -------------------------- */

// place your includes here

/* CODE END Includes */

/* PRIVATE CODE BEGIN DEFINE -------------------------- */
#define SSPIN 2
/* USER CODE BEGIN DEFINE */

// place your defines here

/* CODE END DEFINE */

/* PRIVATE CODE BEGIN VARIABLES -------------------------- */
/* USER CODE BEGIN VARIABLES */

// place your variables here

/* USER CODE END VARIABLES */

/* PRIVATE CODE BEGIN CLASSES -------------------------- */
BnrOneA one;
/* USER CODE BEGIN CLASSES */

// place your classes here

/* USER CODE END CLASSES */

/* PRIVATE CODE BEGIN FUNCTION PROTOTYPES -------------------------- */
/* USER CODE BEGIN FUNCTION PROTOTYPES */

// place your functions here

/* USER CODE END FUNCTION PROTOTYPES */

//  The setup function runs once when you press reset or power the board
void setup()
{
  /* PRIVATE CODE BEGIN Initializations -------------------------- */
  Serial.begin(9600);        // set baud rate to 9600bps for printing values at serial monitor.
  one.spiConnect(SSPIN);     // start SPI communication module
  one.stop();                // stop motors
  one.obstacleEmitters(OFF); // desactivate IR emitters
  one.minBat(10.5);          // set batery treshold
  sonar.begin();             // start Ultrasonic Sensors measurements
  /* USER CODE BEGIN Initializations */

  // place your initializations here

  /* USER CODE END Initializations */

  while (one.readButton() != 1)
  {
    // stuff to do while waiting for button PB1 to be pressed

    // example to get sonars values and display to Serial monitor
    Serial.print("LEFT SONAR: ");                       // Send msg to Serial monitor
    Serial.println(sonar.getSonarDistance(LEFT_SONAR)); // get Left Ultrasonic sensor distance value
    Serial.print("MIDDLE SONAR: ");
    Serial.println(sonar.getSonarDistance(MIDDLE_SONAR)); // get Middle Ultrasonic sensor distance value
    Serial.print("RIGHT SONAR: ");
    Serial.println(sonar.getSonarDistance(RIGH_SONAR)); // get Righ Ultrasonic sensor distance value

    Serial.println("LINE SENSOR VALUES: ");
    int sensor0 = one.readAdc(0);
    int sensor1 = one.readAdc(1);
    int sensor2 = one.readAdc(2);
    int sensor3 = one.readAdc(3);
    int sensor4 = one.readAdc(4);
    int sensor5 = one.readAdc(5);
    int sensor6 = one.readAdc(6);
    int sensor7 = one.readAdc(7);

    // Print values on Serial Monitor
    // Imprimir valores no Serial Monitor
    Serial.print(sensor0);
    Serial.print(" ");
    Serial.print(sensor1);
    Serial.print(" ");
    Serial.print(sensor2);
    Serial.print(" ");
    Serial.print(sensor3);
    Serial.print(" ");
    Serial.print(sensor4);
    Serial.print(" ");
    Serial.print(sensor5);
    Serial.print(" ");
    Serial.print(sensor6);
    Serial.print(" ");
    Serial.print(sensor7);
    Serial.print(" ");
    Serial.println();
    delay(1000); // wait 2sec
  }
}

//  The loop function runs over and over again forever
void loop()
{
  // place your code here
  if (sonar.getSonarDistance(LEFT_SONAR) >= 20 && sonar.getSonarDistance(MIDDLE_SONAR) >= 20 && sonar.getSonarDistance(RIGH_SONAR) >= 20)
  {
    one.move(50, 50);
  }
  else
  {
    one.brake(100, 100);
  }
}
