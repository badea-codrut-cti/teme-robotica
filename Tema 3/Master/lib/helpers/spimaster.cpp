#include <spicom.h>
#include <SPI.h>

uint8_t spiTransfer(uint8_t data) {
    digitalWrite(SS, LOW);
    uint8_t ret = SPI.transfer(data);
    digitalWrite(SS, HIGH);
    return ret;
}

void initSPI() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    digitalWrite(SS, HIGH);
}

void stopRound() {
    spiTransfer(0);
}

void sendRoundState(bool isFirstPlayer, uint8_t ledNumber) {
    ledNumber &= LED_MASK;
    spiTransfer((isFirstPlayer ? 0 : 1) << PLAYER_PIN | ledNumber);
}

uint8_t pollSlave() {
    return spiTransfer((1 << POLL_PIN));
}