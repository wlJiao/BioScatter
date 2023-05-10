#ifndef SENSOR_INCLUDE_SENSOR_H_
#define SENSOR_INCLUDE_SENSOR_H_

#include <msp430.h>
#include "communication.h"
#include "system.h"

/* Task function entry */
void SSTask_Activate(void);
void SSTask_SweepVolt(void);

/* Macro definition */
#define PWMInputVolt                      3.3                                        // Input voltage of the PWM-DAC circuit
#define PWM_Freq                          512                                        // PWM-DAC frequency (Hz)
#define sweep_voltage_value_max           1.2                                        // Maximum output voltage of the PWM-DAC
#define sweep_voltage_value_min           0.4                                        // Minimum output voltage of PWM-DAC
#define sweep_voltage_duration            8                                          // PWM-DAC voltage sweep duration

/* Other Macro definition */
#define PWM_period                        (32768/PWM_Freq)
#define PWM_Duty_radio_max                (sweep_voltage_value_max/PWMInputVolt)
#define PWM_Duty_radio_min                (sweep_voltage_value_min/PWMInputVolt)
#define Outburst_Value_max                (PWM_Duty_radio_max * PWM_period)
#define Outburst_Value_min                (PWM_Duty_radio_min * PWM_period)
#define D_Value                           (Outburst_Value_max - Outburst_Value_min)
#define Update_Points                     ((32768/D_Value)*sweep_voltage_duration)

/* Other function*/
void SS_Init(void);                                      // Initializes the sensor module
void Control_RFSwitch(int c_1,int c_2,int c_3,int c_4);  // Set the current amplification factor

#endif /* SENSOR_INCLUDE_SENSOR_H_ */
