// =============================================================
// = Functions File botFTCUC                    BotOlympics 2022
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

} // End Constructor

// Destructor
botFCTUC::~botFCTUC()
{
} // End Destructor

void botFCTUC::begin(bool M1, bool M2)
{
  // Setup Fan
  setupFan();
  // Setup Button
  setupButton();
  // Setup Buzzer
  setupBuzzer();
  // Setup Flame Sensor
  setupFlame();
  // Setup Neopixel
  setupNeopixel();
  // Setup
  setupColorSensor();
  // Setup
  setupMotores(M1, M2);
  // Setup Lidars
  setupLidar();
}

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
  this->pixelSetColor(0, 255, 0);
  DEBUG_PRINTLN("[INFO] - NeoPixel Started");
}

/*!
  @brief   Set the color to a given R G & B Values
  @param   Red Red Amount 0 -> 255
  @param   Green Red Amount 0 -> 255
  @param   Blue Red Amount 0 -> 255
*/
void botFCTUC::pixelSetColor(uint8_t Red, uint8_t Green, uint8_t Blue)
{
  this->_pixel->setPixelColor(0, this->_pixel->Color(Red, Green, Blue)); // (pixelID, cor)
  this->_pixel->show();
}
/*!
  @brief   Set the color to a given R G & B Values
  @param   Brightness Brightness Amount 0 -> 255
*/
void botFCTUC::pixelSetBrightness(uint8_t Brightness)
{
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
void botFCTUC::setupMotores(bool isMotor1Correct = true, bool isMotor2Correct = true)
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

  pwm = constrain(pwm, (-1 * _maxPwm), _maxPwm);

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
    if (pwm < 0)
    {

      digitalWrite(_motor1Dir, LOW);
      analogWrite(_motor1PWM, abs(pwm));
    }
    else
    {
      pwm = _maxPwm - pwm;
      digitalWrite(_motor1Dir, HIGH);
      analogWrite(_motor1PWM, pwm);
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
  pwm = constrain(pwm, -1 * _maxPwm, _maxPwm);

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
    if (pwm < 0)
    {
      digitalWrite(_motor2Dir, LOW);
      analogWrite(_motor2PWM, abs(pwm));
    }
    else
    {
      pwm = _maxPwm - pwm;
      digitalWrite(_motor2Dir, HIGH);
      analogWrite(_motor2PWM, pwm);
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
// =============================================================
// = LiDARs ====================================================
// =============================================================
/*!
  @brief   Setup the lidar
*/
void botFCTUC::setupLidar()
{
  pinMode(_xshutLeft, OUTPUT);
  pinMode(_xshutFront, OUTPUT);
  pinMode(_xshutRight, OUTPUT);

  digitalWrite(_xshutLeft, LOW);
  digitalWrite(_xshutFront, LOW);
  digitalWrite(_xshutRight, LOW);

  delay(150);
  digitalWrite(_xshutLeft, HIGH);
  delay(100);
  setAddressLidar(_lidarLeft, (uint8_t)_lidarLeftAddr);

  delay(150);

  digitalWrite(_xshutFront, HIGH);
  delay(100);
  setAddressLidar(_lidarFront, (uint8_t)_lidarFrontAddr);
  delay(150);

  digitalWrite(_xshutRight, HIGH);
  delay(100);
  setAddressLidar(_lidarRight, (uint8_t)_lidarRightAddr);
  delay(150);

  _lidarLeft.init(true);
  _lidarFront.init(true);
  _lidarRight.init(true);

  _lidarLeft.setTimeout(10);
  _lidarFront.setTimeout(10);
  _lidarRight.setTimeout(10);

  delay(150);
  _lidarLeft.startContinuous(0);
  _lidarFront.startContinuous(0);
  _lidarRight.startContinuous(0);
}
/*!
  @brief   Set the LiDAR adress
*/
void botFCTUC::setAddressLidar(VL53L0X &LIDAR, uint8_t new_addr)
{
  LIDAR.setAddress(new_addr);
}
/*!
  @brief   Get the LiDAR distance value
  @param   lidarLocation The lidar to return the distance |
           ESQUERDA ou 1 Lidar esquerdo |
           CENTRO ou 2 Lidar centro |
           DIREITA ou 3 Lidar direito |
  @return  the distance value
*/
uint16_t botFCTUC::lidarGetDistance(uint8_t lidarLocation)
{
  uint16_t returnDist;

  switch (lidarLocation)
  {
  case 1:
    returnDist = _lidarLeft.readRangeContinuousMillimeters();
    if (returnDist > _lidarDistMax)
    {
      returnDist = _lidarDistMax;
    }

    return returnDist;
    break;
  case 2:
    returnDist = _lidarFront.readRangeContinuousMillimeters();

    if (returnDist > _lidarDistMax)
    {
      returnDist = _lidarDistMax;
    }

    return returnDist;
    break;
  case 3:
    returnDist = _lidarRight.readRangeContinuousMillimeters();

    if (returnDist > _lidarDistMax)
    {
      returnDist = _lidarDistMax;
    }

    return returnDist;
    break;
  default:
    return 0;
    break;
  }
}

void botFCTUC::lidarPrint()
{
  DEBUG_PRINT("Esquerda: ");
  DEBUG_PRINT(this->lidarGetDistance(ESQUERDA));
  DEBUG_PRINT("mm      Frente: ");
  DEBUG_PRINT(this->lidarGetDistance(CENTRO));
  DEBUG_PRINT("mm      Direita: ");
  DEBUG_PRINT(this->lidarGetDistance(DIREITA));
  DEBUG_PRINTLN("mm");
}

void botFCTUC::printI2C()
{
  Serial.println("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1); // maybe unneeded?
    }           // end of good response
  }             // end of for loop
  Serial.println("Done.");
  Serial.print("Found ");
  Serial.print(count, DEC);
  Serial.println(" device(s).");
}