#ifndef VOLTAGE_INCLUDE_VOLTAGE_H_
#define VOLTAGE_INCLUDE_VOLTAGE_H_

#include <msp430.h>
#include "system.h"

/* Macro definition */
#define ChargingDuration                    (32768/2)  // Set the capacitor charging duration.
#define PWMInputVolt                        3.3        // Set the input voltage of the PWM-DAC circuit.

/* Task function entry */
void VTask_Probe(void);    // Power supply voltage detection and PWM-DAC duty ratio calibration.
void VTask_Activate(void); // Activate a voltage detection course.

/* Other function*/
void V_Init();             // Initialize the voltage module


#endif /* VOLTAGE_INCLUDE_VOLTAGE_H_ */
