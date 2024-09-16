#include <Arduino.h>
#include <WOX.h>

// put function declarations here:
volatile bool flagR = false;
volatile bool flagL = false;

const int rWOXpin = 4;
const int lWOXpin = 5;

WOX leftWOX = WOX(1);
WOX rightWOX = WOX(2);

void handleRightWOX() {
  rightWOX.addHole();
}

void handleLeftWOX() {
  leftWOX.addHole();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(rWOXpin, INPUT_PULLUP);
  pinMode(lWOXpin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(rWOXpin), handleRightWOX, FALLING);
  attachInterrupt(digitalPinToInterrupt(lWOXpin), handleLeftWOX, FALLING);

  Serial.begin(9600);
  rightWOX.boot();
  leftWOX.boot();
}

void loop() {
  // put your main code here, to run repeatedly:
  leftWOX.run();
  rightWOX.run();
}
