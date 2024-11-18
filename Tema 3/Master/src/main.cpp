#include <Arduino.h>
#include <Servo.h>
#include <constants.h>
#include <display.h>
#include <spimaster.h>
#include <spicom.h>

Servo servo;

uint8_t roundCount = 0, correctLed = 0, scoreP1 = 0, scoreP2 = 0;
uint16_t msCounter = 0;
uint32_t lastMillis = 0;
bool isFirstPlayer = false, isWaitingNewRound = false, isWaitingGameEnd = false;


void waitForGameStart() {
    if (roundCount > 0 || isWaitingNewRound || isWaitingGameEnd)
        return;
    
    uint8_t hasPressed = pollSlave() & LED_MASK;

    if (hasPressed == 0)
        return;

    scoreP1 = scoreP2 = 0;

    // Starting a new round will swap the active player
    // So that's why we start with the opposite player
    isFirstPlayer = false;

    displayStartupMessage();
    sendRoundState(false, 0);

    // This will trigger a round start after 3 seconds
    msCounter = 1;
    isWaitingNewRound = true;
}

void startNewRound() {
    isWaitingNewRound = false;
    roundCount++;
    correctLed = random(1, 4);
    sendRoundState(isFirstPlayer = !isFirstPlayer, correctLed);
    displayRoundMessage(isFirstPlayer, isFirstPlayer ? scoreP1 : scoreP2);
    msCounter = 1;
    lastMillis = millis();
}

void handleCounter() {
    if (msCounter == 0) {
        lastMillis = millis();
        return;
    }

    uint32_t ms = millis();
    
    if (ms != lastMillis) {
        msCounter += ms - lastMillis;
        lastMillis = ms;
    }
}

void endRound() {
    msCounter = 1;

    sendRoundState(false, 0);
    // The match has ended
    if (roundCount >= MAX_ROUNDS) {
        isWaitingGameEnd = true;
        bool firstWinner = scoreP1 > scoreP2;
        displayWinner(firstWinner, firstWinner ? scoreP1 : scoreP2);
        return;
    }
    
    isWaitingNewRound = true;
    displayScores(scoreP1, scoreP2);
}

void handleRound() {
    if (roundCount == 0 || isWaitingNewRound || isWaitingGameEnd)
        return;

    if (msCounter > REACTION_CAP) {
        endRound();
        return;
    }

    uint8_t pressed = pollSlave() & LED_MASK;
    if (pressed == 0) 
        return;

    if (pressed == correctLed) {
        if (isFirstPlayer)
            scoreP1 += points(msCounter);
        else scoreP2 += points(msCounter);
    }

    endRound();
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

void handleEndScreen() {
    if (!isWaitingGameEnd)
        return;

    if (msCounter < ROUND_RESTART_DELAY * 1000)
        return;

    msCounter = 0;
    roundCount = 0;
    isWaitingNewRound = isWaitingGameEnd = false;
    sendRoundState(false, 0);
    displayWelcomeMessage();
}

void setup() {
    servo.attach(SERVO_SIG);
    initDisplay();
    initSPI();

    randomSeed(analogRead(0));
    servo.write(0);

    Serial.begin(9600);
    displayWelcomeMessage();
}

void loop() {
    handleCounter();
    waitForGameStart();
    handleRound();
    handleServo();
    waitForNewRound();
    handleEndScreen();
}