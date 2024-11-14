#include "constants.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void initDisplay() {
    lcd.begin(LCD_COLS, LCD_LINES);
}

void displayScores(uint8_t p1, uint8_t p2) {
    lcd.clear();
    lcd.print(P1_NAME);

    lcd.setCursor(LCD_COLS - sizeof(P2_NAME), 0);
    lcd.print(P2_NAME);

    lcd.setCursor(0, 1);
    lcd.print(p1);

    lcd.setCursor(LCD_COLS - (p2 >= 100 ? 3 : p2 >= 10 ? 2 : 1), 1);
    lcd.print(p2);
}

void displayWinner(bool isFirstPlayer, uint8_t score) {
    lcd.clear();
    lcd.print(isFirstPlayer ? P1_NAME : P2_NAME);
    lcd.print(" ");
    lcd.print(WINNER_MSG);
    lcd.setCursor(0, 1);
    lcd.print(score);
}

void displayWelcomeMessage() {
    lcd.clear();
    lcd.print(WELCOME_MSG);
    lcd.setCursor(0, 1);
    lcd.print(IDLE_MSG);
}

void displayRoundMessage(bool isFirstPlayer, uint8_t score) {
    lcd.clear();
    lcd.print(isFirstPlayer ? P1_NAME : P2_NAME);
    lcd.setCursor(0, 1);
    lcd.print(score);
}

void displayStartupMessage() {
    lcd.clear();
    lcd.print(STARTUP_MSG);
}