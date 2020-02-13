/*
 * direction_control.h
 *
 *  Created on: Dec 3, 2019
 *      Author: IO20113053
 */

#ifndef DIRECTION_CONTROL_H_
#define DIRECTION_CONTROL_H_
#include <stdint.h>
//*****************************************************************************
//
// Direction control PWM values
//
//*****************************************************************************

#define FULL_RIGHT_VALUE 0x2A
#define HALF_RIGHT_VALUE 0x34
#define FULL_LEFT_VALUE 0x4E
#define HALF_LEFT_VALUE 0x48
#define CENTER_VALUE_DIRECTION 0x43

#define DEFAULT_DIRECTION_VALUE 0x00

#define PWM_FREQUENCY 56

extern void Adjust_direction();
//*****************************************************************************
//
// Direction control commands
//
//*****************************************************************************
typedef enum {
    CENTER_COMMAND = 1,
    RIGHT_COMMAND,
    HALF_RIGHT_COMMAND,
    LEFT_COMMAND,
    HALF_LEFT_COMMAND
} steering_t;

volatile uint32_t Direction;
volatile steering_t ui32Adjust_Direction;
volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;
#endif /* DIRECTION_CONTROL_H_ */
