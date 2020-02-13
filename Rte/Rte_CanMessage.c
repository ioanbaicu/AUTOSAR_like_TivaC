#include <Rte/Rte_CanMessage.h>
#include "Rtetypes.h"
#include "driverlib/can.h"
#include "include/Can.h"


void CanReceiveMessage()
{
    if(rxFlag) { // rx interrupt has occured

    msg.pui8MsgData = msgData; // set pointer to rx buffer
    CANMessageGet(0x40040000, 1, &msg, 0); // read CAN message object 1 from CAN peripheral

    rxFlag = 0; // clear rx flag

    }
}
