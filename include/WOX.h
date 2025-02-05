#ifndef WOX_H
#define WOX_H
#include <FlexCAN_T4.h>

class WOX
{
public:
    WOX() {}
    explicit WOX(const uint8_t wheelId): wheelId(wheelId) {}
    void boot(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can);
    void seen();
    void sendCAN();
    void calculateRPM();
    void run();

private:
    volatile bool pulseFlag = false;
    volatile uint32_t currentPulse_ms = 0;
    volatile uint32_t lastPulse_ms = 0;
    volatile uint32_t pulseInterval_ms = 0;
    float lastRpmRaw = 0;
    float rpm = 0;
    uint32_t lastDecay_ms = 0;
    uint32_t lastSent_ms = 0;
    uint32_t sendInterval_ms = 20;
    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can = nullptr;
    CAN_message_t msg;
    uint8_t wheelId = 0xFF;
};
#endif
