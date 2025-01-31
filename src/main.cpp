#include <Arduino.h>
#include <WOX.h>
#include <FlexCAN_T4.h>
#include <Reserved.h>

#define RIGHT_WOX_PIN 4
#define LEFT_WOX_PIN 5
// Replace with Front/Rear
#define RIGHT_WHEEL FrontRightId
#define LEFT_WHEEL FrontLeftId
#define SERIAL_BAUD 9600
#define CAN_BAUD_RATE 250000

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> dataCAN;

WOX rightWOX = WOX(RIGHT_WHEEL);
WOX leftWOX = WOX(LEFT_WHEEL);

void handleRightWOX()
{
    rightWOX.seen();
}

void handleLeftWOX()
{
    leftWOX.seen();
}

void setup()
{
    pinMode(RIGHT_WOX_PIN, INPUT_PULLUP); // Check signal direction
    pinMode(LEFT_WOX_PIN, INPUT_PULLUP);

    attachInterrupt(RIGHT_WOX_PIN, handleRightWOX, FALLING); // Check signal direction
    attachInterrupt(LEFT_WOX_PIN, handleLeftWOX, FALLING);

    Serial.begin(SERIAL_BAUD);

    dataCAN.begin();
    dataCAN.setBaudRate(CAN_BAUD_RATE);

    rightWOX.boot(&dataCAN);
    leftWOX.boot(&dataCAN);
}

void loop()
{
    leftWOX.run();
    rightWOX.run();
}
