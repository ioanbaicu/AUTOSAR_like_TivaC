#include <Rte/Rte_PWMs.h>
#include "Rtetypes.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include <stdlib.h>
#include "include/Can.h"
#include "direction_control.h"
#include "speed_control.h"

#define PWM_FREQUENCY 56


//InitConsole();

void
SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}


void PWMInit()
{
    volatile int ui32Load;
    volatile int ui32PWMClock;
    volatile int ui32Width;
    volatile int ui8Adjust;

    ui8Adjust = 0;
    SysCtlPWMClockSet(SYSCTL_PWMDIV_8);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PD0_M0PWM6);
    GPIOPinConfigure(GPIO_PD1_M0PWM7);
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
    ui32Width = (ui8Adjust * ui32Load / 1000);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, ui32Load);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, CENTER_VALUE_DIRECTION * ui32Load / 100);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, CENTER_VALUE_SPEED * ui32Load / 100);
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT|PWM_OUT_7_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);
}

/************************/

void SpeedAndDirection(    )
{

    Adjust_direction();
    Adjust_speed();

}

