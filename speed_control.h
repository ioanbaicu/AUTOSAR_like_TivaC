/*
 * speed_control.h
 *
 *  Created on: Dec 3, 2019
 *      Author: IO20113053
 */

#ifndef SPEED_CONTROL_H_
#define SPEED_CONTROL_H_
#include <stdint.h>
//*****************************************************************************
//
// Speed control PWM values
//
//*****************************************************************************

#define REVERSE_SPEED_1         0x47
#define REVERSE_SPEED_2         0x48
#define REVERSE_SPEED_3         0x49
#define REVERSE_FULL_SPEED      0x4A

#define FORWARD_SPEED_1         0x3D
#define FORWARD_SPEED_2         0x3C
#define FORWARD_SPEED_3         0x3B
#define FORWARD_FULL_SPEED      0x3A

#define CENTER_VALUE_SPEED      0x43
#define DEFAULT_VALUE_SPEED     0x00

#define PWM_FREQUENCY           56

#define ACTIVE                  0x01
#define INACTIVE                0x00

extern void Adjust_speed();

//*****************************************************************************
//
// Speed control commands
//
//*****************************************************************************

typedef enum {
    ZERO = 0,
    INIT_VALUE = 1,
    FR_SPEED1,
    FR_SPEED2,
    FR_SPEED3,
    FR_FULL,
    REV_SPEED1,
    REV_SPEED2,
    REV_SPEED3,
    REV_FULL,
    STOP
} acceleration_t;

volatile uint32_t Speed;
volatile acceleration_t ui32Adjust_Speed;
volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;

#endif /* SPEED_CONTROL_H_ */
