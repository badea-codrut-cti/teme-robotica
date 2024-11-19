#include <Arduino.h>
#include <SPI.h>
#include <spicom.h>

#define BTN0_P0_RED A5
#define BTN0_P0_GREEN A4
#define BTN0_P0_BLUE A3
#define BTN1_P1_BLUE A2
#define BTN1_P1_GREEN A1
#define BTN1_P1_RED A0
#define LED0_RED 9
#define LED0_GREEN 8
#define LED0_BLUE 7
#define LED1_RED 6
#define LED1_GREEN 5
#define LED1_BLUE 4
#define DEBOUNCE_DELAY 50

enum Color {
  RED=0b01,
  GREEN=0b10,
  BLUE=0b11,
  SHUT=0b00
};

bool buttonPressed = false;
uint32_t debounceTimer = 0;
volatile uint8_t activePlayer = 0;
volatile Color activeLed = SHUT, lastButtonPressed = SHUT, buttonColor = SHUT;

void setup() {
  // Set analog pins A0 to A5 as digital inputs with pull-up resistors
  pinMode(BTN0_P0_RED, INPUT_PULLUP);
  pinMode(BTN0_P0_GREEN, INPUT_PULLUP);
  pinMode(BTN0_P0_BLUE, INPUT_PULLUP);
  pinMode(BTN1_P1_BLUE, INPUT_PULLUP);
  pinMode(BTN1_P1_GREEN, INPUT_PULLUP);
  pinMode(BTN1_P1_RED, INPUT_PULLUP);

  // Set LED pins as outputs
  pinMode(LED0_RED, OUTPUT);
  pinMode(LED0_GREEN, OUTPUT);
  pinMode(LED0_BLUE, OUTPUT);
  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);
  // Set up SPI
  SPCR |= _BV(SPE);
  pinMode(MISO,OUTPUT);
  SPI.attachInterrupt();
  interrupts();
}

void setPlayerLedColor(bool isFirstPlayer, Color col) {
  // Shut down all LEDs first
  if (isFirstPlayer) {
    digitalWrite(LED0_RED, LOW);
    digitalWrite(LED0_GREEN, LOW);
    digitalWrite(LED0_BLUE, LOW);
  } else {
    digitalWrite(LED1_RED, LOW);
    digitalWrite(LED1_GREEN, LOW);
    digitalWrite(LED1_BLUE, LOW);
  }
  // Turn on the LED with the specified color
  if (col == RED) {
    digitalWrite(isFirstPlayer ? LED0_RED : LED1_RED, HIGH);
  } else if (col == GREEN) {
    digitalWrite(isFirstPlayer ? LED0_GREEN : LED1_GREEN, HIGH);
  } else if (col == BLUE) {
    digitalWrite(isFirstPlayer ? LED0_BLUE : LED1_BLUE, HIGH);
  }
}

void handleLED() {
  // If no player is active, shut down all LEDs
  if (activePlayer == 0) {
    setPlayerLedColor(false, SHUT);
    setPlayerLedColor(true, SHUT);
    return;
  }
 // Set the LED color for the active player
  setPlayerLedColor(activePlayer == 1, activeLed);
}

void updateLastPressedButton() {
  //If no button was pressed, return
  if (lastButtonPressed != SHUT)
    return;
  // Check which button was pressed for player 1
  if (activePlayer == 0 || activePlayer == 1) {
    if (digitalRead(BTN0_P0_RED) == LOW) {
      buttonPressed = true;
      buttonColor = RED;
    } else if (digitalRead(BTN0_P0_GREEN) == LOW) {
      buttonPressed = true;
      buttonColor = GREEN;
    } else if (digitalRead(BTN0_P0_BLUE) == LOW) {
      buttonPressed = true;
      buttonColor = BLUE;
    }
  }
   // Check which button was pressed for player 2
  if (activePlayer == 0 || activePlayer == 2) {
    if (digitalRead(BTN1_P1_RED) == LOW) {
      buttonPressed = true;
      buttonColor = RED;
    } else if (digitalRead(BTN1_P1_GREEN) == LOW) {
      buttonPressed = true;
      buttonColor = GREEN;
    } else if (digitalRead(BTN1_P1_BLUE) == LOW) {
      buttonPressed = true;
      buttonColor = BLUE;
    }
  }
  //Update which button was pressed
  if (buttonPressed) {
    if (millis() - debounceTimer >= DEBOUNCE_DELAY) {
      debounceTimer = millis();
      lastButtonPressed = buttonColor;
      buttonPressed = false;
    }
  } else {
    debounceTimer = millis();
  }
}
// SPI interrupt service routine
ISR (SPI_STC_vect){
  // If the master is polling, send the last button pressed
  if ((SPDR & (1 << POLL_PIN))) {
    SPDR = lastButtonPressed;
    return;
  }
  // If the master is not polling, update the active player and LED color
  lastButtonPressed = SHUT;
  activeLed = (Color)(SPDR & LED_MASK);
  activePlayer = activeLed == SHUT ? 0 : ((SPDR & (1 << PLAYER_PIN)) == 0 ? 1 : 2);
  SPDR=0;
}

void loop() {
  handleLED();
  updateLastPressedButton();
}