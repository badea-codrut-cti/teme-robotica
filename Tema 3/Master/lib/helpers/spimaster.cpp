#include <spicom.h>
#include <SPI.h>

void initSPI() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    digitalWrite(SS,HIGH);
}

void stopRound() {
    SPI.transfer(0);
}

void startRound(bool isFirstPlayer, uint8_t ledNumber) {
    ledNumber &= LED_MASK;
    SPI.transfer((isFirstPlayer ? 0 : 1) << PLAYER_PIN | ledNumber);
}

uint8_t pollSlave() {
    return SPI.transfer((1 << POLL_PIN));
}