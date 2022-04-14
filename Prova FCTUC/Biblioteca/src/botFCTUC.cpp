// =============================================================
// = Function File botFTCUC                     BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =============================================================
#include "botFCTUC.h"
#include <Arduino.h>

/*!
  @brief
  @param
  @return
*/

// =============================================================
// = Class Constructor and Destructor ==========================
// =============================================================

// Constructor
botFCTUC::botFCTUC()
{
  // Setup Fan
  fanSetup();
  // Setup Button
  buttonSetup();
  // Setup Buzzer
  buzzerSetup();

} // End Constructor

// Destructor
botFCTUC::~botFCTUC()
{
} // End Destructor

// =============================================================
// = Fan Control Funtions ======================================
// =============================================================

/*!
  @brief   Set up the Fan
*/
void botFCTUC::fanSetup()
{
  pinMode(_fanPin, OUTPUT);
  fanOff();
} // End fanSetup

/*!
  @brief Turn the fan on
  @note Control Logic is Inverted (1 = Off, 0 = On)
*/
void botFCTUC::fanOn()
{
  digitalWrite(_fanPin, LOW);
} // End fanOn

/*!
  @brief Turn the fan off
  @note Control Logic is Inverted (1 = Off, 0 = On)
*/
void botFCTUC::fanOff()
{
  digitalWrite(_fanPin, HIGH);
} // End fanOff

// =============================================================
// = Button Control Funtions ===================================
// =============================================================

/*!
  @brief   Set up the Button
*/
void botFCTUC::buttonSetup()
{
  pinMode(_buttonPin, INPUT);
}

/*!
  @brief   Waits in a infinite loop until the button is pressed to exit
*/
void botFCTUC::waitStart()
{
  DEBUG_PRINTLN("[INFO] - BotFCTUC Waiting to start!");

  while (!digitalRead(_buttonPin))
  {
    if (millis() - _previousMillis >= 500)
    {
      _previousMillis = millis();
      this->pixelSetColor(0, !(greenOrBlue)*255, (greenOrBlue)*255);
      greenOrBlue = !greenOrBlue;
    }
  }

  DEBUG_PRINTLN("[INFO] - BotFCTUC Is starting!");
}

/*!
  @brief   Read the button status
  @return  The button Status
*/
bool botFCTUC::readButton()
{
  return digitalRead(_buttonPin);
}

// =============================================================
// = Buzzer Control Funtions ===================================
// =============================================================
/*!
  @brief   Set up the Buzzer
*/
void botFCTUC::buzzerSetup()
{
  pinMode(_buzzerPin, OUTPUT);
  buzzerPlay(0);
}
/*!
  @brief   Play a sound on the buzzer
  @param   Val Tone to be played
*/
void botFCTUC::buzzerPlay(uint8_t val)
{
  analogWrite(_buzzerPin, val);
}

// =============================================================
// = NeoPixel Control Funtions =================================
// =============================================================
/*!
  @brief   Set up the neopixel
*/
void botFCTUC::neopixelSetup()
{
  pinMode(_neopixelPin, OUTPUT);

  // Create Neopixel and start it
  this->_pixel = new Adafruit_NeoPixel(1, _neopixelPin,
                                       NEO_GRB + NEO_KHZ800);
  this->_pixel->begin();
  pixelSetBrightness(255);
  pixelSetColor(255, 255, 255);
  // DEBUG_PRINTLN("[INFO] - NeoPixel Started");
}

/*!
  @brief   Set the color to a given R G & B Values
  @param   Red Red Amount 0 -> 255
  @param   Green Red Amount 0 -> 255
  @param   Blue Red Amount 0 -> 255
*/
void botFCTUC::pixelSetColor(uint8_t Red, uint8_t Green, uint8_t Blue)
{
  // Prevent the user from being funny and messing with me
  constrain(Red, 0, 255);
  constrain(Green, 0, 255);
  constrain(Blue, 0, 255);

  this->_pixel->setPixelColor(0, this->_pixel->Color(Red, Green, Blue)); // (pixelID, cor)
  this->_pixel->show();
}
/*!
  @brief   Set the color to a given R G & B Values
  @param   Brightness Brightness Amount 0 -> 255
*/
void botFCTUC::pixelSetBrightness(uint8_t Brightness)
{
  // Prevent the user from being funny and messing with me
  constrain(Brightness, 0, 255);
  this->_pixel->setBrightness(Brightness);
}
// =============================================================
// = Flame Sensor Control Funtions =============================
// =============================================================
/*!
  @brief   Set up the flame sensor
*/
void botFCTUC::flameSetup()
{
  pinMode(_flameSensor, INPUT);
}

/*!
  @brief   Get the sensor value from the flame sensor
  @return  The flame sensor value 0 -> 1023
*/
uint16_t botFCTUC::getFlame()
{
  return analogRead(_flameSensor);
}

/*!
  @brief   Print the current value of the flame sensor
*/
void botFCTUC::printFlame()
{
  DEBUG_PRINTLN("Flame Sensor: " + String(getFlame()));
}

// =============================================================
// = Color Sensor Control Funtions =============================
// =============================================================
/*!
  @brief   Set up the color sensor
  @return  True if sucessful, false if not setup
*/
bool botFCTUC::setupColorSensor()
{
  _colorSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
  return _colorSensor.begin();
}

/*!
 *  @brief  Return the Red, Green, Blue, Clear values
 *  @param  RGBC[0]
 *          Red value
 *  @param  RGBC[1]
 *          Green value
 *  @param  RGBC[2]
 *          Blue value
 *  @param  RGBC[3]
 *          Clear channel value
 */
void botFCTUC::getColor(uint16_t RGBC[])
{
  _colorSensor.getRawData(&RGBC[0], &RGBC[1], &RGBC[2], &RGBC[3]);
}
/*!
 *  @brief Enable the color Sensor
 */
void botFCTUC::enableColorSensor()
{
  _colorSensor.enable();
}
/*!
 *  @brief Disable the color Sensor
 */
void botFCTUC::disableColorSensor()
{
  _colorSensor.disable();
}