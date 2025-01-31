#ifndef WOX_H
#define WOX_H
#include <FlexCAN_T4.h>

class WOX
{
public:
    WOX();
    explicit WOX(uint8_t wheelId);
    void boot(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can);
    void seen();
    void sendCAN();
    void calculateRPM();
    void reset();
    void run();

private:
    uint16_t rpm = 0;
    uint8_t wheelId = 0xFF;
    // TODO: Replace with interval that can be used to calculate RPM
    uint interval = 20;
    volatile uint64_t seenHoles = 0;
    uint32_t lastCheck = 0;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can = nullptr;
    CAN_message_t msg;
};
#endif
