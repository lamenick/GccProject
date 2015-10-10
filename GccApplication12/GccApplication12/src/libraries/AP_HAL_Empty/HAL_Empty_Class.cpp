
#include "libraries/AP_HAL/AP_HAL.h"

#include "libraries/AP_HAL_Empty/HAL_Empty_Class.h"
#include "libraries/AP_HAL_Empty/AP_HAL_Empty.h"
#include "libraries/AP_HAL_Empty/UARTDriver.h"
#include "libraries/AP_HAL_Empty/Scheduler.h"


using namespace Empty;
using namespace AP_HAL;

static EmptyUARTDriver uartDriverInstance;
static EmptyScheduler schedulerInstance;

Empty::HAL_Empty::HAL_Empty() :
    AP_HAL::HAL(
        &uartDriverInstance,
        &schedulerInstance)
{}

void Empty::HAL_Empty::init(int argc,char* const argv[]) const {
    /* initialize all drivers and private members here.
     * up to the programmer to do this in the correct order.
     * Scheduler should likely come first. */
    scheduler->init(NULL);
    console->begin(9600);
}

const HAL_Empty AP_HAL_Empty;

