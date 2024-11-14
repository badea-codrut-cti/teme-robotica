#include <Arduino.h>

void initSPI();

void stopRound();

void startRound(bool, uint8_t);

uint8_t pollSlave();