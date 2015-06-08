#ifndef USARTRFID_H
#define USARTRFID_H
#include <stdint.h>

namespace USART
{
    void init();
    void setBitRate(uint32_t bitrate);
};

#endif // USARTRFID_H
