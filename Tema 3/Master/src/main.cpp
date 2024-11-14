#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Constants.h>

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Servo servo;

uint8_t servoCoord = 0;

void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
  servo.attach(SERVO_SIG);

  // Print a message to the LCD.

  lcd.print("hello, world!");
  
}

void loop()
{
  servo.write(servoCoord);
  if (servoCoord < 179)
    servoCoord++;
  delay(100);
}