#include <Arduino.h>
#include <WOX.h>
#include <FlexCAN_T4.h>
#include <Reserved.h>

#define RIGHT_WOX_PIN 2
#define LEFT_WOX_PIN 3
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
    pinMode(RIGHT_WOX_PIN, INPUT_PULLDOWN);
    pinMode(LEFT_WOX_PIN, INPUT_PULLDOWN);

    attachInterrupt(RIGHT_WOX_PIN, handleRightWOX, RISING);
    attachInterrupt(LEFT_WOX_PIN, handleLeftWOX, RISING);

    Serial.begin(SERIAL_BAUD);

    dataCAN.begin();
    dataCAN.setBaudRate(CAN_BAUD_RATE);

    rightWOX.boot(&dataCAN);
    leftWOX.boot(&dataCAN);
}

void loop()
{
    rightWOX.run();
    leftWOX.run();
}
