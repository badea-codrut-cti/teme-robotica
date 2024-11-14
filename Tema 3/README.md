## Protocol over SPI

### Master Protocol:

```
00000000

7 POLL - When it is on, it means that this is a request asking for status from the slave. The other pins should be off.
6 PLAYER - Dictates which player is the active player.
0-1 CORRECT_LED - 01 for red, 10 for green, 11 for blue. Can technically support up to 32 colors.
```

### Slave Protocol:

```
00000000

0-1 PRESSED_BTN - same as above, 00 meaning no button was pressed yet.

Expected Behaviour:
 - The slave only keeps track of the last pressed button, active player and correct LED.
 - The slave will ignore button presses from the inactive player.
 - If the correct LED is set to 00, the round has ended and the LED is shut down.
 - The last pressed button resets to zero whenever a non-polling request is sent.
 - The slave only loops back non-polling data.
 - We will only register button presses if the last button pressed is zero.
```
 
### Example Communication:

```
Master: 00000011 // The master tells the slave that a new round started, player 1 is playing and the correct LED is blue.
Slave : 00000011 // Looping back, signaling that we understood.
Master: 10000000 // Asking what's up.
Slave : 00000000 // Nothing yet, the player hasn't reacted.
Master: 10000000 // Asking what's up again every ms.
Slave : 00000000
// Repeating this until the player reacted...
Master: 10000000
Slave : 00000011 // The player has pressed the button corresponding to the blue LED. 
Master: 00000000 // We shut down the LEDs. The round is over.
Slave : 00000000
// We wait out the round restart delay on the master...
Master: 01000010 // Now it's player 2's turn and the correct LED is green.
```

**Disclaimer: Do not check if the master message is equal to 0 to determine if the round is over. `0b01000000` is also valid.**

### Starting the game

The master will keep polling the slave until any of the buttons are pressed.

```
Master: 00000000 // The game ended, we shut off the LEDs
Slave: 00000000 // Looping back.
Master: 10000000 // Polling
Slave : 00000000
// Repeating until button is pressed...
Master: 10000000
Slave: 00000010 // One of the players has pressed the green LED button. We should start the game.
// We wait out the start countdown...
Master: 00000001 // A new round has started
```