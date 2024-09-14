#include <Arduino.h>
#include <WOX.h>

// put function declarations here:
int myFunction(int, int);

WOX leftWOX = WOX(1);
WOX rightWOX = WOX(2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rightWOX.boot();
  leftWOX.boot();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}