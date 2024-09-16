#ifndef WOX_H
#define WOX_H
#include <FlexCAN_T4.h>
class WOX {
    private:
        int rpm = 0;
        int rollTime = 500;
        int seenHoles = 0;
        int wheel;
        int lastCheck = 0;
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can;
        CAN_message_t msg;
        
    public:
        WOX();
        WOX(int inWheel);
        void addHole();
        void sendCAN();
        void calculateRPM();
        void reset();
        void boot();
        void run();

    //1       2
    //3       4
    //Wheels are in the above layout
};
#endif