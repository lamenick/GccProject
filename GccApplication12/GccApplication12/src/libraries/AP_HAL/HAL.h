
#ifndef __AP_HAL_HAL_H__
#define __AP_HAL_HAL_H__

#include "AP_HAL_Namespace.h"

#include "UARTDriver.h"

class AP_HAL::HAL {
public:
    HAL(AP_HAL::UARTDriver* _console,
        AP_HAL::Scheduler*  _scheduler)
        :
        console(_console),
        scheduler(_scheduler)
    {}

    virtual void init(int argc, char * const argv[]) const = 0;

    AP_HAL::UARTDriver* console;
    AP_HAL::Scheduler*  scheduler;
};

#endif // __AP_HAL_HAL_H__

