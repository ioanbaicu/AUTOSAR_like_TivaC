/*
 * speed_control.c
 *
 *  Created on: Dec 3, 2019
 *      Author: IO20113053
 */

#include "speed_control.h"
#include "driverlib/pwm.h"
#include "inc/hw_memmap.h"
#include "include/Can.h"
#include "driverlib/sysctl.h"

volatile uint32_t break_command;
acceleration_t previous_command = ZERO;

void Adjust_speed()
{
    ui32Adjust_Speed = (acceleration_t)msgData[1];     //PD1 for speed PWM
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    if (break_command == ACTIVE)
    {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, CENTER_VALUE_SPEED * ui32Load / 100);
        SysCtlDelay(100000);
        Speed = 0;
        break_command = INACTIVE;
    }
    if (previous_command != ui32Adjust_Speed)
    {
        switch (ui32Adjust_Speed){

        case INIT_VALUE://1
            break_command = INACTIVE;
            Speed = CENTER_VALUE_SPEED;
            break;

        case FR_SPEED1://2
            Speed = FORWARD_SPEED_1;
            break_command = INACTIVE;
            break;

        case FR_SPEED2://3
            break_command = INACTIVE;
            Speed = FORWARD_SPEED_2;
            break;

        case FR_SPEED3://4
            break_command = INACTIVE;
            Speed = FORWARD_SPEED_3;
            break;

        case FR_FULL://5
            break_command = INACTIVE;
            Speed = FORWARD_FULL_SPEED;
            break;

        case REV_SPEED1://6
            break_command = INACTIVE;
            Speed = REVERSE_SPEED_1;
            break;

        case REV_SPEED2://7
            break_command = INACTIVE;
            Speed = REVERSE_SPEED_2;
            break;

        case REV_SPEED3://8
            break_command = INACTIVE;
            Speed = REVERSE_SPEED_3;
            break;

        case REV_FULL://9
            break_command = INACTIVE;
            Speed = REVERSE_FULL_SPEED;
            break;

        case STOP://A
        {
            if (break_command == INACTIVE)
            {
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, CENTER_VALUE_SPEED * ui32Load / 100);
                SysCtlDelay(100000);
                PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, REVERSE_SPEED_1 * ui32Load / 100);
                SysCtlDelay(400000);
                break_command = ACTIVE;
            }
            break;
        }

        default:
            Speed = DEFAULT_VALUE_SPEED;
            break;
        }
    }
    else
    {
        /*make misra happy*/
    }
    previous_command = ui32Adjust_Speed;
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, Speed * ui32Load / 100);
    SysCtlDelay(100000);
}
