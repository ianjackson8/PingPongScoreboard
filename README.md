# PingPongScoreboard
Code for a ping pong scoreboard using an Arduino Uno R3, LED Matrix, and 3 push buttons

## Features
* Scoreboard for ping pong, first to score 21 wins. 
* Features three pushbuttons: player one, player two, and a reset button.
* The player who wins has to score by two.
* Prompts players to volley for the first serve.
* Serve possession switches between players every 5 points scored.

## Materials Required
* Arudino Uno R3
* 8x32 MAX7219 LED Matrix
* 3 push buttons with jumper wire connections
* Small breadboard power rail
* Jumper wires

## Instructions
* Connect the 5V and GND pin on the Arduino to the power rail of the breadboard.
* Connect VCC and GND of the LED Matrix to the breadboard power rail.
* Connect the following pins of the LED Matrix to the followuing Arduino pins (these can be changed, this is what I jave them as),
  * DIN to Pin 12
  * CS to Pin 10
  * CLK to Pin 11
* Connect one pin of the push buttons to pins 8 (player one), 7 (player two), and pin 6 (reset).
* Connect the other pins of the push buttons to ground on the power rail.
* Supply power to the Arduino via a 9V battery.

Seen below is a schematic of the scoreboard.
![Scoreboard Schematic](https://user-images.githubusercontent.com/77818029/171063943-401f8b90-fbf3-436a-b70e-a79a461fdec5.png)

## Notes
* Any of the pin locations can be changed, make sure the updated locations are changed in the code.
* For a more compact design, I removed the power rail from the small breadboard so the Scoreboard didn't have all of the unused breadboard space carried around.
* If there are any features I am missing, let me know!
