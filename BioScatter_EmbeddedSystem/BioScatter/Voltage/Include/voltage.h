#ifndef VOLTAGE_INCLUDE_VOLTAGE_H_
#define VOLTAGE_INCLUDE_VOLTAGE_H_

#include <msp430.h>
#include "system.h"

/* Macro definition */
#define ChargingDuration                    (32768/2)  // Set the capacitor charging duration.
#define PWMInputVolt                        3.3        // Set the input voltage of the PWM circuit.

/* Task function entry */
void VTask_Probe(void);    // Voltage monitor and PWM duty ratio calibrate.
void VTask_Activate(void); // Activate the voltage monitor course.

/* Other function*/
void V_Init();             // Initialize the voltage monitor module.


#endif /* VOLTAGE_INCLUDE_VOLTAGE_H_ */
