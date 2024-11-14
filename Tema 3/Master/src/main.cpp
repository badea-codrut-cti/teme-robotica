#include <Arduino.h>
#include <Servo.h>
#include <constants.h>
#include <display.h>
#include <spicom.h>

Servo servo;

uint8_t servoCoord = 0;

void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  servo.attach(SERVO_SIG);

  // Print a message to the LCD.
  initDisplay();
  displayWelcomeMessage();
}

void loop()
{
  //servo.write(servoCoord);
  //if (servoCoord < 179)
  //  servoCoord++;
  delay(100);
}