#ifndef KSOTARIR_H
#define KSOTARIR_H
#include <stdint.h>

namespace KsotarIr
{
    void init();
    bool rawSend(const uint8_t *data, uint8_t size);
    extern void (*readyCallBack)(uint8_t b1, uint8_t b2);
};

#endif // KSOTARIR_H
