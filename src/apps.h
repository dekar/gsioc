#ifndef APPS_H
#define APPS_H
#include <stdint.h>





// Настройки

    // Максимальное количество регистрируемых функций
    #define MAX_NUM_OF_FUNC 20

    // Регистрирую вывод.


//Прототипы внешних функций
namespace APPS
{
    void init (void);
    void pool (void);
    void regFunc(bool (*execute)(uint8_t, const uint8_t  * const), const char c);
    bool pushPkg(const uint8_t * pkg, uint8_t size);

}

#endif // APPS_H
