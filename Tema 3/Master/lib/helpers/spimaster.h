#include <Arduino.h>

void initSPI();

void stopRound();

void sendRoundState(bool, uint8_t);

uint8_t pollSlave();