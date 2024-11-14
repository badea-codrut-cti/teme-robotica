## Protocol over SPI

### Master Protocol:

```
00000000

7 POLL - When it is on, it means that this is a request asking for status from the slave. The other pins should be off.
6 RGB_STATE - If this is off, either the game ended or we are between rounds. When it is off we shut down both RGB LEDs.
5 PLAYER - Dictates which player is the active player.
0-1 CORRECT_LED - 01 for red, 10 for green, 11 for blue. Can technically support up to 32 colors.
```

### Slave Protocol:

```
00000000

0-1 PRESSED_BTN - same as above, 00 meaning no button was pressed yet.

Expected Behaviour:
 - The slave only keeps track of the last pressed button and active player.
 - The slave will ignore button presses from the inactive player.
 - The last pressed button resets to zero whenever a non-polling request is sent.
 - The slave only loops back non-polling data.
```
 
### Example Communication:

```
Master: 01000011 // The master tells the slave that a new round started, player 1 is playing and the correct LED is blue.
Slave : 01000011 // Looping back, signaling that we understood.
Master: 10000000 // Asking what's up.
Slave : 00000000 // Nothing yet, the player hasn't reacted.
Master: 10000000 // Asking what's up again every ms.
// Repeating this until the player reacted...
Master: 10000000
Slave : 00000011 // The player has pressed the button corresponding to the blue LED. 
Master: 00000000 // We shut down the LEDs. The round is over.
Slave : 00000000
// We wait out the round restart delay on the master...
Master: 01000010 // Now it's player 2's turn and the correct LED is green.
```
