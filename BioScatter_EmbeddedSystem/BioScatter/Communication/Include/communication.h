#ifndef COMMUNICATION_INCLUDE_COMMUNICATION_H_
#define COMMUNICATION_INCLUDE_COMMUNICATION_H_

#include <msp430.h>
#include "system.h"

/* Task function entry */
void CMTask_Activate(void);

/* Other function*/
void CM_Init(void);                    // Initialization
void CM_SendData(unsigned char data);  // Send 8 bits of data

#endif /* COMMUNICATION_INCLUDE_COMMUNICATION_H_ */
