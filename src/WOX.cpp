#include <WOX.h>
#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <Reserved.h>
#include <BufferPacker.h>

WOX::WOX(const uint8_t wheelId): wheelId(wheelId)
{
}

void WOX::boot(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>* can)
{
    this->can = can;
}

void WOX::seen()
{
    seenHoles++;
}

void WOX::reset()
{
    seenHoles = 0;
}

void WOX::calculateRPM()
{
    // TODO: Correct count
    // How to handle reverse?
    rpm = seenHoles / 12;
}

void WOX::run()
{
    if (millis() - lastCheck >= interval)
    {
        calculateRPM();
        sendCAN();
        reset();
    }
}

void WOX::sendCAN()
{
    msg.id = TireRPMId;
    msg.buf[0] = wheelId;
    BufferPacker<3> packer(msg.buf);
    packer.skip<uint8_t>();
    packer.pack(rpm);
    can->write(msg);
}
