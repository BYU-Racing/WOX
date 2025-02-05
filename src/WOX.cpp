#include <WOX.h>
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <Reserved.h>
#include <BufferPacker.h>

#define MAGNET_COUNT 4
#define MIN_PULSE_INTERVAL 5
#define MS_PER_MIN 60000.0f
#define MS_PER_MAGNET MS_PER_MIN / MAGNET_COUNT
// RPM takes (DECAY_INTERVAL_FACTOR x last pulse interval) milliseconds to decay to 0
#define DECAY_INTERVAL_FACTOR 2.0f

void WOX::boot(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can)
{
    this->can = can;
}


void WOX::seen()
{
    if (const uint32_t now = millis(); now - lastPulse_ms > MIN_PULSE_INTERVAL)
    {
        // Prevent the sensor from registering more than 3000 RPM
        lastPulse_ms = currentPulse_ms;
        currentPulse_ms = now;
        pulseInterval_ms = currentPulse_ms - lastPulse_ms;
        pulseFlag = true;
    }
}

void WOX::calculateRPM()
{
    const uint32_t now = millis();
    if (pulseFlag)
    {
        // Process most recent detection
        if (pulseInterval_ms > 0)
        {
            rpm = MS_PER_MAGNET / pulseInterval_ms;
        }
        pulseFlag = false;
        lastDecay_ms = now;
        return;
    }

    if (rpm == 0 || pulseInterval_ms == 0) return;

    // Decay RPM
    const float decayRate = rpm / (DECAY_INTERVAL_FACTOR * pulseInterval_ms);
    const float decay = decayRate * (now - lastDecay_ms);
    if (rpm > decay && rpm - decay > 0)
    {
        rpm -= decay;
    } else
    {
        rpm = 0;
    }
    lastDecay_ms = now;
}

void WOX::sendCAN()
{
    msg.id = TireRPMId;
    msg.buf[0] = wheelId;
    BufferPacker<sizeof(uint8_t) + sizeof(float)> packer(msg.buf);
    packer.skip<uint8_t>();
    packer.pack(rpm);
    can->write(msg);
}

void WOX::run()
{
    if (millis() - lastSent_ms >= sendInterval_ms)
    {
        lastSent_ms = millis();
        calculateRPM();
        sendCAN();
    }
}
