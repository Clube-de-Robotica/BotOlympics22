/*
  Sonar.cpp - Library for interfacing Ultrasonics sensors with Bot'n Roll ONE Arduino Compatible from www.botnroll.com
  Created by Dylan Denizon, April 18, 2022.
*/
#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"

#define LSonarTrigPin 7
#define LSonarEchoPin 6

#define MSonarTrigPin 9
#define MSonarEchoPin 8

#define RSonarTrigPin 10
#define RSonarEchoPin 5

#define SonarN 3

#define TICK_COUNTS 1000

#define LEFT_SONAR 0
#define MIDDLE_SONAR 1
#define RIGH_SONAR 2

#define SPEED_SOUND 340 // m/s in air at 20ºC
#define MAX_DIST 3.5    // meters

#define MAX_DURATION ((2.0 * MAX_DIST) / SPEED_SOUND) * 1e6
#define VEL_CONST 58.7755

class Sonar
{
private:
  const byte EchoPins[3] = {LSonarEchoPin, MSonarEchoPin, RSonarEchoPin};
  const byte TrigPins[3] = {LSonarTrigPin, MSonarTrigPin, RSonarTrigPin};

  volatile int trigger_time_count = TICK_COUNTS; // Count down counter to trigger pulse time

  volatile long echo_start[3] = {0};    // Records start of echo pulses
  volatile long echo_end[3] = {0};      // Records end of echo pulses
  volatile long echo_duration[3] = {0}; // Duration - difference between end and start

  volatile byte sonar_pos = 0;

  void pciSetup(byte pin);

public:
  void begin();
  float getSonarDistance(byte n);
  void trigger_pulse();
  void echo_interrupt(byte n);
};

extern Sonar sonar;
#endif
