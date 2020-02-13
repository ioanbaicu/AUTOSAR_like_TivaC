
#pragma diag_push
#pragma CHECK_MISRA("none")

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "OS/include/task.h"
#include "OS/include/event.h"
#include "OS/include/InitConsole.h"
#include "include/Com.h"
#include "include/CanTp_Cfg.h"
#include "include/CanTp.h"
#include "include/CanIf.h"
#include "include/Can.h"
#include "Dio.h"
#include <Rte/Rte_PWMs.h>
#include "Rte/Rte_CanMessage.h"


DeclareTask(T1);
DeclareEvent(BSW_Event_Com_MainFunctionRx);


int main(void){

    InitGPIO();
    PWMInit();
    Can_Init();
    StartOS(OSDEFAULTAPPMODE);
	return 0;
}

TASK(T1)
{
    EventMaskType NewEvent;
    while(true)
    {
        WaitEvent(BSW_Event_Com_MainFunctionRx);
        GetEvent(T1, &NewEvent);
        ClearEvent(NewEvent);
        if(NewEvent & BSW_Event_Com_MainFunctionRx)
        {
            CanReceiveMessage();
            SpeedAndDirection();
        }

        TerminateTask();
    }
}
