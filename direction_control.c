/*
 * direction_control.c
 *
 *  Created on: Dec 2, 2019
 *      Author: IO20113053
 */
#include "direction_control.h"
#include "include/Can.h"
#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"

void Adjust_direction()
{
    ui32Adjust_Direction = (steering_t)msgData[0]; //PD0 for direction PWM
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    switch(ui32Adjust_Direction)
    {

    case (CENTER_COMMAND):
        Direction = CENTER_VALUE_DIRECTION;
        break;

    case (RIGHT_COMMAND):
        Direction = FULL_RIGHT_VALUE;
        break;

    case (HALF_RIGHT_COMMAND):
        Direction = HALF_RIGHT_VALUE;
        break;

    case (LEFT_COMMAND):
        Direction = FULL_LEFT_VALUE;
        break;

    case (HALF_LEFT_COMMAND):
        Direction = HALF_LEFT_VALUE;
        break;

    default:
        Direction = DEFAULT_DIRECTION_VALUE;
        break;
    }
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, Direction * ui32Load / 100);
    SysCtlDelay(100000);
}
