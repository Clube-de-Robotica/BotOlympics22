// =============================================================
// = Functions File botFTCUC                    BotOlympics 2022
// = JNDVasco - Rev 1.0
// =
// =============================================================
#include "botFCTUC.h"

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
  setupFan();
  // Setup Button
  setupButton();
  // Setup Buzzer
  setupBuzzer();

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
void botFCTUC::setupFan()
{
  pinMode(_fanPin, OUTPUT);
  this->fanOff();
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
void botFCTUC::setupButton()
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
void botFCTUC::setupBuzzer()
{
  pinMode(_buzzerPin, OUTPUT);
  this->buzzerPlay(0);
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
void botFCTUC::setupNeopixel()
{
  pinMode(_neopixelPin, OUTPUT);

  // Create Neopixel and start it
  this->_pixel = new Adafruit_NeoPixel(1, _neopixelPin,
                                       NEO_GRB + NEO_KHZ800);
  this->_pixel->begin();
  this->pixelSetBrightness(255);
  this->pixelSetColor(255, 255, 255);
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
void botFCTUC::setupFlame()
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
  DEBUG_PRINTLN("Flame Sensor: " + String(this->getFlame()));
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

// =============================================================
// = Motors Control Funtions ===================================
// =============================================================
/*
| Dir |   PWM   |        Função        |
|:---:|:-------:|:--------------------:|
|  0  |    0    |    Abrandar Lento    |
|  0  |   PWM   |    Sentido Horário   |
|  1  | 1 - PWM | Sentido Anti-Horário |
|  1  |    1    |        Travar        |
*/

/*!
  @brief   Set up the motors
*/
void botFCTUC::setupMotores(bool isMotor1Correct, bool isMotor2Correct)
{
  this->_isMotor1Correct = isMotor1Correct;
  this->_isMotor2Correct = isMotor2Correct;

  pinMode(_motor1Dir, OUTPUT);
  pinMode(_motor1PWM, OUTPUT);
  pinMode(_motor2Dir, OUTPUT);
  pinMode(_motor2PWM, OUTPUT);

  this->stopMotors();
}
/*!
  @brief   Control Motor 1
  @param   pwm The desired PWM for the motor, accepts value between
               and only between -255 to 255
*/
void botFCTUC::moveMotor1(int16_t pwm) // aceita valores entre -255 e 255
{

  constrain(pwm, -1 * _maxPwm, _maxPwm);

  /*
   * 1st case is for the correct polarity
   */
  if (_isMotor1Correct)
  {
    if (pwm > 0)
    {
      digitalWrite(_motor1Dir, LOW);
      analogWrite(_motor1PWM, pwm);
    }
    else
    {
      pwm = _maxPwm + pwm;
      digitalWrite(_motor1Dir, HIGH);
      analogWrite(_motor1PWM, pwm);
    }
  }
  else
  /*
   * 2nd case is for the incorrect polarity
   */
  {
    if (pwm > 0)
    {
      pwm = _maxPwm - pwm;
      digitalWrite(_motor1Dir, LOW);
      analogWrite(_motor1PWM, pwm);
    }
    else
    {
      digitalWrite(_motor1Dir, HIGH);
      analogWrite(_motor1PWM, abs(pwm));
    }
  }
}
/*!
  @brief   Control Motor 2
  @param   pwm The desired PWM for the motor, accepts value between
               and only between -255 to 255
*/
void botFCTUC::moveMotor2(int16_t pwm) // aceita valores entre -255 e 255
{
  constrain(pwm, -1 * _maxPwm, _maxPwm);

  /*
   * 1st case is for the correct polarity
   */
  if (_isMotor2Correct)
  {
    if (pwm > 0)
    {
      digitalWrite(_motor2Dir, LOW);
      analogWrite(_motor2PWM, pwm);
    }
    else
    {
      pwm = _maxPwm + pwm;
      digitalWrite(_motor2Dir, HIGH);
      analogWrite(_motor2PWM, pwm);
    }
  }
  else
  /*
   * 2nd case is for the incorrect polarity
   */
  {
    if (pwm > 0)
    {
      pwm = _maxPwm - pwm;
      digitalWrite(_motor2Dir, LOW);
      analogWrite(_motor2PWM, pwm);
    }
    else
    {
      digitalWrite(_motor2Dir, HIGH);
      analogWrite(_motor2PWM, abs(pwm));
    }
  }
}

/*!
  @brief   Control the motors speed
  @param   pwmM1 The desired PWM for motor 1, accepts value between
               and only between -255 to 255
  @param   pwmM2 The desired PWM for motor 2, accepts value between
               and only between -255 to 255
*/
void botFCTUC::move(int16_t pwmM1, int16_t pwmM2)
{
  this->moveMotor1(pwmM1);
  this->moveMotor2(pwmM2);
}

/*!
  @brief   Bring Motors to a stop, this blocks the code for 50 milliseconds
*/
void botFCTUC::stopMotors()
{
  this->move(0, 0);
  delay(50);
}