#define DIFFICULTY_BTN 2
#define START_BTN 3
#define BLUE_RGB 4
#define GREEN_RGB 5
#define RED_RGB 6

#define TIMER_COMPARE_VAL 250

#define GAME_LENGTH 30000U
#define BLINK_LENGTH 500U
#define START_LENGTH 3000U

#define DEBOUNCE_TIME 200U

const char* dictionary[] = {
    "copilu cine esti ma", 
    "zero munca", 
    "alta gasca in alta traista", 
    "switch switch router",  
    "dom student",
    "ai mari lagune",
    "sterge tot",
    "pasul doi incomplet",
    "pentru ca da",
    "colegul meu",
    "nu ai fost la curs",
    "nu merge asa",
    "din aproape in aproape",
    "de la stanga la dreapta",
    "de la mic la mare",
    "cine nu are parola",
    "nu urmariti informatia",
    "se intoarce in zero",
    "armin van buuren",
    "layer zero nota zero",
    "inchideti monitoarele",
    "cand vreodata"
};

const uint8_t dictionaryCount = sizeof(dictionary) / sizeof(dictionary[0]);

const char* difficultyMessages[] = {
    "Easy",
    "Medium",
    "Hard mode on!"
};

const uint16_t difficultyDelay[] = {
    7000,
    4500,
    2700
};
