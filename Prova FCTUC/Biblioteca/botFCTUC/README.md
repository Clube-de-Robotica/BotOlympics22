# Bibloteca FCTUC

```cpp
/*!
  @brief   Set up the robot
  @param   M1 If the motor 1 spins the correct way or not
  @param   M2 If the motor 2 spins the correct way or not
*/
void botFCTUC::begin(bool M1, bool M2)

/*!
  @brief Turn the fan on
  @note Control Logic is Inverted (1 = Off, 0 = On)
*/
void botFCTUC::fanOn()

/*!
  @brief Turn the fan off
  @note Control Logic is Inverted (1 = Off, 0 = On)
*/
void botFCTUC::fanOff()

/*!
  @brief   Waits in a infinite loop until the button is pressed to exit
*/
void botFCTUC::waitStart()

/*!
  @brief   Read the button status
  @return  The button Status
*/
bool botFCTUC::readButton()

/*!
  @brief   Play a sound on the buzzer
  @param   Val Tone to be played
*/
void botFCTUC::buzzerPlay(uint8_t val)

/*!
  @brief   Set the color to a given R G & B Values
  @param   Red Red Amount 0 -> 255
  @param   Green Red Amount 0 -> 255
  @param   Blue Red Amount 0 -> 255
*/
void botFCTUC::pixelSetColor(uint8_t Red, uint8_t Green, uint8_t Blue)

/*!
  @brief   Set the color to a given R G & B Values
  @param   Brightness Brightness Amount 0 -> 255
*/
void botFCTUC::pixelSetBrightness(uint8_t Brightness)

/*!
  @brief   Get the sensor value from the flame sensor
  @return  The flame sensor value 0 -> 1023
*/
uint16_t botFCTUC::getFlame()

/*!
  @brief   Print the current value of the flame sensor
*/
void botFCTUC::printFlame()


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

/*!
 *  @brief Enable the color Sensor
 */
void botFCTUC::enableColorSensor()

/*!
 *  @brief Disable the color Sensor
 */
void botFCTUC::disableColorSensor()


/*!
  @brief   Control Motor 1
  @param   pwm The desired PWM for the motor, accepts value between
               and only between -255 to 255
*/
void botFCTUC::moveMotor1(int16_t pwm) // aceita valores entre -255 e 255

/*!
  @brief   Control Motor 2
  @param   pwm The desired PWM for the motor, accepts value between
               and only between -255 to 255
*/
void botFCTUC::moveMotor2(int16_t pwm) // aceita valores entre -255 e 255

/*!
  @brief   Control the motors speed
  @param   pwmM1 The desired PWM for motor 1, accepts value between
               and only between -255 to 255
  @param   pwmM2 The desired PWM for motor 2, accepts value between
               and only between -255 to 255
*/
void botFCTUC::move(int16_t pwmM1, int16_t pwmM2)

/*!
  @brief   Bring Motors to a stop, this blocks the code for 50 milliseconds
*/
void botFCTUC::stopMotors()

/*!
  @brief   Get the LiDAR distance value
  @param   lidarLocation The lidar to return the distance |
           ESQUERDA ou 1 Lidar esquerdo |
           CENTRO ou 2 Lidar centro |
           DIREITA ou 3 Lidar direito |
  @return  the distance value
*/
uint16_t botFCTUC::lidarGetDistance(uint8_t lidarLocation)

/*!
  @brief   Print all the lidar distances
*/
void botFCTUC::lidarPrint()

/*!
  @brief   Print all the detected I2C devices
*/
void botFCTUC::printI2C()
```