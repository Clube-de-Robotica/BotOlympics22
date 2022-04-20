/*
  Sonar.cpp - Library for interfacing Ultrasonics sensors with Bot'n Roll ONE Arduino Compatible from www.botnroll.com
  Created by Dylan Denizon, April 18, 2022.
*/

#include "Sonar.h"
Sonar sonar;

/**
 * @brief Function to get Ultrasonics distances values
 *
 * @param pos LEFT_SONAR or MIDDLE_SONAR or RIGH_SONAR
 * @returns Distance in cm (float)
 */
float Sonar::getSonarDistance(byte pos)
{
    return echo_duration[pos] / VEL_CONST;
}

/**
 * @brief Function to start Ultrasonics sensors measurements
 */
void Sonar::begin()
{
    for (byte i = 0; i < SonarN; i++)
    {
        pinMode(TrigPins[i], OUTPUT); // Sets the trigPins as an OUTPUT
        digitalWrite(TrigPins[i], LOW);
        pinMode(EchoPins[i], INPUT); // Sets the EchoPins as an INPUT

        pciSetup(EchoPins[i]);
    }

    // Setup Timer 1 Registers
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0; // set counter = 0;

    OCR1A = 100; // compare match register 100/ (16MHz/8) -> 50us

    TCCR1B |= (1 << WGM12);  // CTC mode
    TCCR1B |= (1 << CS11);   // 8 prescaler
    TIMSK1 |= (1 << OCIE1A); // enable compare interrupt
    interrupts();
}

void Sonar::pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin)); // enable pin
    PCIFR |= bit(digitalPinToPCICRbit(pin));                   // clear any outstanding interrupt
    PCICR |= bit(digitalPinToPCICRbit(pin));                   // enable interrupt for the group
}

// --------------------------
// trigger_pulse() called every 50 uS to schedule trigger pulses.
// Generates a pulse one timer tick long.
// Minimum trigger pulse width for the HC-SR04 is 10 us. This system
// delivers a 50 uS pulse.
// --------------------------
void Sonar::trigger_pulse()
{
    static volatile int state = 1; // State machine variable

    if (!(--trigger_time_count))          // Count to 200mS
    {                                     // Time out - Initiate trigger pulse
        trigger_time_count = TICK_COUNTS; // Reload
        state = 1;                        // Changing to state 1 initiates a pulse
        sonar_pos++;
        if (sonar_pos >= 3)
        {
            sonar_pos = 0;
        }
    }

    switch (state) // State machine handles delivery of trigger pulse
    {
    case 0: // Normal state does nothing
        break;

    case 1: // Initiate pulse
        digitalWrite(TrigPins[sonar_pos], HIGH);
        state = 2; // and set state to 2
        break;

    case 2: // Complete the pulse
    default:
        digitalWrite(TrigPins[sonar_pos], LOW);
        state = 0; // and return state to normal 0
        break;
    }
}

// --------------------------
// echo_interrupt() External interrupt from HC-SR04 echo signal.
// Called every time the echo signal changes state.
//
// Note: this routine does not handle the case where the timer
//       counter overflows which will result in the occassional error.
// --------------------------
void Sonar::echo_interrupt(byte n)
{
    if (sonar_pos == n)
    {
        switch (digitalRead(EchoPins[n])) // Test to see if the signal is high or low
        {
        case HIGH:                    // High so must be the start of the echo pulse
            echo_end[n] = 0;          // Clear the end time
            echo_start[n] = micros(); // Save the start time
            break;

        case LOW:                                           // Low so must be the end of hte echo pulse
            echo_end[n] = micros();                         // Save the end time
            echo_duration[n] = echo_end[n] - echo_start[n]; // Calculate the pulse duration
            break;
        }
    }
}

// --------------------------
// timerIsr() 50uS second interrupt ISR()
// Called every time the hardware timer 1 times out.
// --------------------------
ISR(TIMER1_COMPA_vect)
{
    sonar.trigger_pulse(); // Schedule the trigger pulses
}

ISR(PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{
    volatile static bool lastMSonarEchoPinState = LOW;
    bool actualMSonarEchoPinState = digitalRead(MSonarEchoPin);
    if (actualMSonarEchoPinState != lastMSonarEchoPinState)
    {
        lastMSonarEchoPinState = actualMSonarEchoPinState;
        sonar.echo_interrupt(MIDDLE_SONAR);
    }
}

ISR(PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
    //
}

ISR(PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
    volatile static bool lastLSonarEchoPinState = LOW;
    volatile static bool lastRSonarEchoPinState = LOW;

    bool actualLSonarEchoPinState = digitalRead(LSonarEchoPin);
    bool actualRSonarEchoPinState = digitalRead(RSonarEchoPin);
    if (actualLSonarEchoPinState != lastLSonarEchoPinState)
    {
        lastLSonarEchoPinState = actualLSonarEchoPinState;
        sonar.echo_interrupt(LEFT_SONAR);
    }

    if (actualRSonarEchoPinState != lastRSonarEchoPinState)
    {
        lastRSonarEchoPinState = actualRSonarEchoPinState;
        sonar.echo_interrupt(RIGH_SONAR);
    }
}