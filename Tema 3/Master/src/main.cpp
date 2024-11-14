#include <Arduino.h>
#include <Servo.h>
#include <constants.h>
#include <display.h>
#include <spimaster.h>

Servo servo;

uint8_t roundCount = 0, correctLed = 0, scoreP1 = 0, scoreP2 = 0;
uint16_t msCounter = 0;
uint32_t lastMillis = 0;
bool isFirstPlayer = false, isWaitingNewRound = false;


void handleMainMenu() {
    servo.write(0);
    displayWelcomeMessage();
}

void waitForGameStart() {
    if (roundCount > 0)
        return;
    
    uint8_t hasPressed = pollSlave();
    if (hasPressed == 0)
        return;

    scoreP1 = scoreP2 = 0;
    isFirstPlayer = false;

    roundCount = 0;
    msCounter = 1;
    isWaitingNewRound = true;
    displayStartupMessage();
}

void startNewRound() {
    isWaitingNewRound = false;
    roundCount++;
    startRound(isFirstPlayer = !isFirstPlayer, correctLed = random(1, 4));
    msCounter = 1;
    lastMillis = millis();
}

void handleCounter() {
    if (msCounter == 0)
        return;

    uint32_t ms = millis();
    
    if (ms != lastMillis) {
        msCounter += ms - lastMillis;
        lastMillis = ms;
    }
}

void handleRound() {
    if (isWaitingNewRound)
        return;

    if (msCounter > REACTION_CAP) {
        endRound();
        return;
    }

    uint8_t pressed = pollSlave();
    if (pressed == 0) 
        return;
    
    if (pressed == correctLed) {
        if (isFirstPlayer)
            scoreP1 += points(msCounter);
        else scoreP2 += points(msCounter);
    }

    endRound();
}

void endRound() {
    msCounter = 1;
    isWaitingNewRound = true;

    displayScores(scoreP1, scoreP2);
}

void handleServo() {
    servo.write(servo_pos(roundCount));
}

void waitForNewRound() {
    if (!isWaitingNewRound)
        return;

    if (msCounter < ROUND_RESTART_DELAY * 1000)
        return;
    
    startNewRound();
}

void setup() {
    servo.attach(SERVO_SIG);
    initDisplay();
    initSPI();

    randomSeed(analogRead(0));

    handleMainMenu();
}

void loop() {
    waitForGameStart();
    handleCounter();
    handleRound();
    handleServo();
    waitForNewRound();
}