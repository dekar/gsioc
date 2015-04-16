#ifndef USB_H
#define USB_H
#include <stdint.h>


namespace USB
{
    void init();
    void cableConnect (bool enable);
    void sendRawData(const uint8_t* data, uint16_t size);
    void pool();
    extern bool(* incommingFunc)(const uint8_t * const data, uint8_t size);
    bool isPCConnected();
};

#endif // USB_H
