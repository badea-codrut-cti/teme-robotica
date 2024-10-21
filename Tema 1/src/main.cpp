#include <Arduino.h>

#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7
#define RED_RGB 6
#define GREEN_RGB 4
#define RESET_BUTTON 3
#define START_BUTTON 2
#define CHARGE_LEVEL_DELAY 3000
#define RESET_HOLD_TIME 1000
#define BLINK_INTERVAL 500
#define BLINK_ANIMATION_TIMES 3
#define DEBOUNCE_OFFSET 20

bool isCharging = false, blinkOn = true;
uint16_t levelTimer = 0, resetHoldTimer = 0, blinkTimer = 0;
uint8_t chargeLevel = 0, chargeDebounceTimer = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(RED_RGB, OUTPUT);
  pinMode(GREEN_RGB, OUTPUT);
  pinMode(RESET_BUTTON, INPUT_PULLUP);
  pinMode(START_BUTTON, INPUT_PULLUP);
  digitalWrite(GREEN_RGB, HIGH);
  digitalWrite(RED_RGB, LOW);
}

void handleCharge() {
  if (digitalRead(START_BUTTON) == LOW && !isCharging) {
    chargeDebounceTimer++;
    if (chargeDebounceTimer > DEBOUNCE_OFFSET) {
      digitalWrite(RED_RGB, HIGH);
      digitalWrite(GREEN_RGB, LOW);
      isCharging = true;
      chargeDebounceTimer = 0;
    }
  }
  if (!isCharging)
    return;
  if (chargeLevel < 4) 
    levelTimer++;
  if (levelTimer > CHARGE_LEVEL_DELAY) {
    chargeLevel++;
    levelTimer = 0;
    blinkTimer = BLINK_INTERVAL + 1;
    blinkOn = true;
    switch (chargeLevel) {
        case 1: digitalWrite(LED1, HIGH); break;
        case 2: digitalWrite(LED2, HIGH); break;
        case 3: digitalWrite(LED3, HIGH); break;
    }
  }
}

void setAllLEDState(bool state) {
  digitalWrite(LED1, state ? HIGH : LOW);
  digitalWrite(LED2, state ? HIGH : LOW);
  digitalWrite(LED3, state ? HIGH : LOW);
  digitalWrite(LED4, state ? HIGH : LOW);
}

void handleLEDBlink() {
  if (!isCharging)
    return;

  blinkTimer++;
  if (blinkTimer >= BLINK_INTERVAL) {
    if (chargeLevel < 4) {
      switch (chargeLevel) {
        case 0: digitalWrite(LED1, blinkOn ? HIGH : LOW); break;
        case 1: digitalWrite(LED2, blinkOn ? HIGH : LOW); break;
        case 2: digitalWrite(LED3, blinkOn ? HIGH : LOW); break;
        case 3: digitalWrite(LED4, blinkOn ? HIGH : LOW); break;
      }
    } else setAllLEDState(blinkOn);
    blinkTimer = 0;
    blinkOn = !blinkOn;
  }
}

void handleReset() {
  if (digitalRead(RESET_BUTTON) == LOW) {
    resetHoldTimer++;
    if (resetHoldTimer > RESET_HOLD_TIME) {
      setAllLEDState(false);
      isCharging = false;
      chargeLevel = levelTimer = blinkTimer = 0;
      uint8_t blinkCounter = 0;
      while (blinkCounter++ <= BLINK_ANIMATION_TIMES) {
        setAllLEDState(blinkCounter % 2);
        delay(BLINK_INTERVAL);
      }
      digitalWrite(RED_RGB, LOW);
      digitalWrite(GREEN_RGB, HIGH);
    }
  } else resetHoldTimer = 0;
}

void loop() {
  handleCharge();
  handleLEDBlink();
  handleReset();
  delay(1);
}