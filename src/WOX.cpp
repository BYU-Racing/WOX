#include <WOX.h>
#include <Arduino.h>
#include <FlexCAN_T4.h>


WOX::WOX() {
    wheel = 1;
}

WOX::WOX(int inWheel) {
    wheel = inWheel;
}

void WOX::boot() {
    can.begin();
    can.setBaudRate(250000);
}


void WOX::addHole() {
    seenHoles++;
}

void WOX::reset() {
    seenHoles = 0;
}

void WOX::calculateRPM() {
    rpm = seenHoles / 12; // THIS IS PLACEHOLDER CODE
}