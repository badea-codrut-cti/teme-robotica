#include <Arduino.h>
#include <Dictionary.h>

volatile uint8_t difficultyLevel = 0;
uint8_t lastDifficultyLevel = 0, wordIndex = 0, letterIndex = 0, lastCorrectIndex = 0, correctCount = 0;
volatile uint16_t gameStartMs = 0;
uint16_t lastBlinkMs = 0, lastCountMs = 0, lastWordMs = 0;
volatile uint32_t debounceDifficultyButton = millis(), debounceStartButton = millis();
volatile bool hasGameStarted = false;
bool isLEDOn = false, lastWordCorrect = true, forceNewWord = false;

// Made this a separate function as the same logic
// will be used when the timer runs out or inside the interrupt.
void resetCountersAfterGame() {
  gameStartMs = lastWordMs = lastCountMs = correctCount = 0;
  hasGameStarted = false;
}

// Should only be called in the interrupt. It will change the difficulty setting.
void handleDifficultyButton() {
  // We should not change difficulty mid-game
  if (hasGameStarted)
    return;

  if (millis() - debounceDifficultyButton < DEBOUNCE_TIME)
    return;

  difficultyLevel = (difficultyLevel + 1) % 3;
  debounceDifficultyButton = millis();
}

void handleStartButton() {
  if (millis() - debounceStartButton < DEBOUNCE_TIME)
    return;

  if (hasGameStarted)
    resetCountersAfterGame();
  else
    hasGameStarted = true;
  debounceStartButton = millis();
}

ISR(TIMER2_COMPA_vect) {
  TCNT1 = TIMER_COMPARE_VAL;

  if (!hasGameStarted)
    return;

  gameStartMs++;

  if (gameStartMs < GAME_LENGTH + START_LENGTH)
    return;

  gameStartMs = 0;
  hasGameStarted = false;
}

void setup() {
  pinMode(RED_RGB, OUTPUT);
  pinMode(GREEN_RGB, OUTPUT);
  pinMode(BLUE_RGB, OUTPUT);
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(DIFFICULTY_BTN, INPUT_PULLUP);

  randomSeed(analogRead(0));

  // In repaus LED-ul RGB este alb.
  digitalWrite(RED_RGB, HIGH);
  digitalWrite(GREEN_RGB, HIGH);
  digitalWrite(BLUE_RGB, HIGH);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(DIFFICULTY_BTN), handleDifficultyButton, FALLING);
  attachInterrupt(digitalPinToInterrupt(START_BTN), handleStartButton, FALLING);

  // Preventing timer from triggering during setup
  noInterrupts();
  
  // Source: https://dronebotworkshop.com/interrupts
  TCCR2A = 0;
  TCCR2B = 0;

  TCNT2 = TIMER_COMPARE_VAL;
  TCCR2B |= (1 << CS22);
  //TCCR1B &= ~((1 << CS12) | (1 << CS10));
  TIMSK2 |= (1 << OCIE2A);

  interrupts();
}

// Keeps track of difficulty level changes and shows their corresponding message.
void showDifficultyMessage() {
  if (lastDifficultyLevel == difficultyLevel) 
    return;
  
  Serial.println(difficultyMessages[difficultyLevel]);
  lastDifficultyLevel = difficultyLevel;
}

void handleStartAnimation() {
  if (!hasGameStarted) {
    digitalWrite(RED_RGB, HIGH);
    digitalWrite(GREEN_RGB, HIGH);
    digitalWrite(BLUE_RGB, HIGH);
    return;
  }

  // Only play the blinking animation before the game starts
  if (gameStartMs > START_LENGTH)
    return;
  
  if (gameStartMs - lastBlinkMs >= BLINK_LENGTH) {
    lastBlinkMs = gameStartMs;
    isLEDOn = !isLEDOn;
    digitalWrite(RED_RGB, isLEDOn ? HIGH : LOW);
    digitalWrite(GREEN_RGB, isLEDOn ? HIGH : LOW);
    digitalWrite(BLUE_RGB, isLEDOn ? HIGH : LOW);
  }

  if (gameStartMs - lastCountMs >= 1000) {
    Serial.println(4 - gameStartMs / 1000, DEC);
    lastCountMs = gameStartMs;
  }
}

void handleGameWordPrint() {
  if (gameStartMs < START_LENGTH)
    return;

  if ((lastWordMs != 0 && gameStartMs - lastWordMs < difficultyDelay[difficultyLevel]) && !forceNewWord)
    return;

  if (lastWordMs != 0 && !forceNewWord)
    lastWordCorrect = false;

  forceNewWord = false;
  wordIndex = random(dictionaryCount);
  Serial.print("\n");
  Serial.println(dictionary[wordIndex]);
  lastWordMs = gameStartMs;
  lastCorrectIndex = letterIndex = 0;
}

void handleGameEnd() {
  if (gameStartMs < GAME_LENGTH) 
    return;
  
  Serial.print(correctCount, DEC);
  Serial.print(" cuvinte corecte\n");

  resetCountersAfterGame();
}

void handleWordValidationLED() {
  if (gameStartMs <= START_LENGTH) 
    return;

  digitalWrite(RED_RGB, lastWordCorrect ? LOW : HIGH);
  digitalWrite(GREEN_RGB, lastWordCorrect ? HIGH : LOW);
  digitalWrite(BLUE_RGB, LOW);
}

void handleInput() {
  if (!Serial.available()) 
    return;

  int incomingByte = Serial.read();

  if (incomingByte == -1)
    return;

   if (incomingByte == '\b') {
    letterIndex = letterIndex ? letterIndex - 1 : 0;
    return;
   }

  // We can't just backspace one character and keep typing.
  if (letterIndex && letterIndex - 1 > lastCorrectIndex) {
    letterIndex++;
    return;
  }
  
  if (dictionary[wordIndex][letterIndex++] != incomingByte) {
    lastWordCorrect = false;
    return;
  }

  lastCorrectIndex = letterIndex - 1;

  if (dictionary[wordIndex][letterIndex] == '\0') {
    lastWordCorrect = true;
    forceNewWord = true;
    correctCount++;
  }
}

void loop() {
  showDifficultyMessage();
  handleStartAnimation();
  handleGameWordPrint();
  handleWordValidationLED();
  handleInput();
  handleGameEnd();
}
