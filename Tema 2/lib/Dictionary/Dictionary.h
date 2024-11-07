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

#define MAX_DICT_SIZE 30

const char dictionary[][MAX_DICT_SIZE] PROGMEM = {
    "copilu cine esti ma", 
    "zero munca", 
    "alta gasca in alta traista", 
    "switch switch router",  
    "dom student",
    "ai mari lacune",
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
    "cand vreodata",
    "time is money",
    "nu exista help",
    "ursuletul din erasmus",
    "crestem in valoare",
    "nu sariti peste fire",
    "de la ce vine rsa",
    "eu nu sunt aici",
    "nu vreau sa vad elefanti",
    "am zis castraveti",
    "nu salvati nimic",
    "ai restanta puisor",
    "te joci acasa",
    "de la simplu la compus",
    "resetati aplicatia",
    "nu inchideti unitatea",
    "default gateway",
    "ce o fi aia partitie",
    "nu va faceti programatori",
    "folositi doar packet tracer",
    "cum ar zice rusu",
    "ati folosit gpt",
    "sub nivelul marii",
    "reguli simple",
    "foloseste crossover",
    "nu ai vlanul null",
    "noi gandim in modele",
    "echipament virtual 5 lei",
    "echipament real 3000 lei",
    "eu vorbesc cu frigiderul",
    "scrie bine colegul tau",
    "ai pierdut trenul",
    "intri cu absenta",
    "asa e in tenis",
    "scopul si durata",
    "nu ne intelegem",
    "cablarea ta e zero",
    "ai stricat axele",
    "nu lucra in izometric",
    "ai permis de conducere",
    "perpetuezi greseala",
    "iti lipsesc elemente",
    "pierdeti din vedere",
    "va spun doamnei de poo",
    "stii de la ce vine uso",
    "lucrezi ca sa lucrezi",
    "cat casa scanteii",
    "ce a vrut sa zica colegul",
    "doi ursuleti care soptesc",
    "criptat nu e securizat",
    "lucram pe etape",
    "te joci acasa",
    "ai potential dar degeaba", // asta mi-a zis mie la colocviu sem 1
    "va pistonam din spate", // asta mi-a zis sem 2 la colocviu, "noi" fiind profesorii
    "mai trebuie un doctorat",
    "in momentul de fata",
    "din acest moment",
    "aplicatia te ajuta",
    "dlluri de la windows",
    "switchport edging time",
    "ai configurat serviciul tfc", // tai frunza la caini
    "unitate plus monitor",
    "nu iti merge stickul",
    "accesati resursele pe site",
    "ai trimis tu mailuri"
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