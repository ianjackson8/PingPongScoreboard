// Arduino Libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Hardware setup
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10
#define DATA_PIN 12
#define CLK_PIN 11

// Define button pins
const int PLAYER_ONE_BTTN = 8;
const int PLAYER_TWO_BTTN = 7;
const int RST_BTTN = 6;

// New instance of MD_Parola class
MD_Parola scoreboard = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Score variables
int playerOneScore;
int playerTwoScore;

// Ball variables
int playerOneBall = 0;
int playerTwoBall = 0;

// Button state variables
int lastStateP1 = LOW;
int currentStateP1;
int lastStateP2 = LOW;
int currentStateP2;
int lastStateRst = LOW;
int currentStateRst;

int switched = 0;

void setup() {
  // set up scoreboard
  scoreboard.begin();
  scoreboard.setIntensity(8);
  scoreboard.displayClear();
  
  // setup buttons
  pinMode(PLAYER_ONE_BTTN, INPUT_PULLUP);
  pinMode(PLAYER_TWO_BTTN, INPUT_PULLUP);
  pinMode(RST_BTTN, INPUT_PULLUP);

  // reset scores
  int playerOneScore = 0;
  int playerTwoScore = 0;
}

void loop() {
  // get button states
  currentStateP1 = digitalRead(PLAYER_ONE_BTTN);
  currentStateP2 = digitalRead(PLAYER_TWO_BTTN);
  currentStateRst = digitalRead(RST_BTTN);
  scoreboard.setTextAlignment(PA_CENTER);

  firstBall();

  switchBall();

  if (playerOneBall == 1) {
    scoreboard.print(String(playerOneScore) + "<-" + String(playerTwoScore));
  } else if (playerTwoBall == 1) {
    scoreboard.print(String(playerOneScore) + "->" + String(playerTwoScore));
  }

  // gameplay
  checkWinner();
  incP1();
  incP2();
  rst();

  // update button states
  lastStateP1 = currentStateP1;
  lastStateP2 = currentStateP2;
  lastStateRst = currentStateRst;
}

void incP1() {
  // check if player one score increases
  if (lastStateP1 == HIGH && currentStateP1 == LOW) {
    playerOneScore++;
    switched = 0;
  }
}

void incP2() {
  // check if player two score increases
  if (lastStateP2 == HIGH && currentStateP2 == LOW) {
    playerTwoScore++;
    switched = 0;
  }
}

void rst() {
   // check if scores reset
  if (lastStateRst == HIGH && currentStateRst == LOW) {
    playerOneScore = 0;
    playerTwoScore = 0;
    playerOneBall = 0;
    playerTwoBall = 0;
    switched = 0;
  }
}

void checkWinner() {

  if (winByTwo()) {
    if (playerOneScore >= 21 || playerTwoScore >= 21) {
      scoreboard.displayClear();
      // P1 wins
      if (playerOneScore > playerTwoScore) {
        scoreboard.print("P1 Wins!");
        delay(5000);
        playerOneScore = 0;
        playerTwoScore = 0;
        playerOneBall = 0;
        playerTwoBall = 0;
      } else { // P2 wins
        scoreboard.print("P2 Wins!");
        delay(5000);
        playerOneScore = 0;
        playerTwoScore = 0;
        playerOneBall = 0;
        playerTwoBall = 0;
      }
    }
  }
  
  // check if winner
  
}

void firstBall() {
  // who gets balls first
  while (playerOneBall == 0 && playerTwoBall == 0) {
    currentStateP1 = digitalRead(PLAYER_ONE_BTTN);
    currentStateP2 = digitalRead(PLAYER_TWO_BTTN);
    
    scoreboard.setTextAlignment(PA_CENTER);
    scoreboard.print("volley?");
    
    if (lastStateP1 == HIGH && currentStateP1 == LOW) {
      playerOneScore = -1;
      playerOneBall = 1;
      scoreboard.displayClear();
      break;
    }
    if (lastStateP2 == HIGH && currentStateP2 == LOW) {
      playerTwoScore = -1;
      playerTwoBall = 1;
      scoreboard.displayClear();
      break;
    }

    lastStateP1 = currentStateP1;
    lastStateP2 = currentStateP2;
  }
}

void switchBall() {
  if (((playerOneScore + playerTwoScore) % 5) == 0 && (playerOneScore + playerTwoScore) > 3 && switched == 0) {
    if (playerOneBall == 1 && playerTwoBall == 0) {
      playerOneBall = 0;
      playerTwoBall = 1;
      switched = 1;
    } else if (playerTwoBall == 1 && playerOneBall == 0){
      playerOneBall = 1;
      playerTwoBall = 0;
      switched = 1;
    }
  }
}

bool winByTwo() {
  if (abs(playerOneScore - playerTwoScore) > 1) {
    return true;
  } else {
    return false;
  }
}
