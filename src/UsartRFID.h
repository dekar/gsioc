#ifndef USARTRFID_H
#define USARTRFID_H
#include <stdint.h>

namespace UsartRFID
{
    void init();
    void start();
    void stop();
    void regCB(bool (*callback)(uint8_t *, uint8_t));
};

#endif // USARTRFID_H
