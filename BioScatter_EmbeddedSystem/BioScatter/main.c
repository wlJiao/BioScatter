/****************************************************************************************
 * System: This is a task scheduling system. The task ID is represented by a number
 * ranging from 0 to 15. During each scheduling, the task with a smaller ID has a higher
 * priority and will be executed first. One ID can correspond to only one task. The
 * system supports a maximum of 16 tasks.
 *
 * If you want to use a scheduling system, you must include the header file system.h.
 * You also need to create a sysconf.h file where you set the total number of tasks by
 * defining TASK_COUNT with a macro.
 *
 * System instructions:
 * 1. SysInit() must be called at the beginning of the main function.
 * 2. SysSchedule()  must be called at the ending of the main function.
 * 3. To register a task with the system through the TskCreate() function, you must
 *    provide a task function entry and task ID.
 * 4. A task can be set to ready state by calling TskSetReady().
 * 5. TskExit() must be called in each task entry function to indicate that the current
 *    task has completed.
 *
 * Note:
 * 1. Task functions cannot contain infinite loops.
 * 2. If TskExit() is not called in the task function, the task will always be scheduled.
 ****************************************************************************************/

#include <msp430.h>
#include "system.h"
#include "sensor.h"
#include "voltage.h"
#include "communication.h"

void main(void) {
    /* Initialize system */
    // 1. Setting the task scheduler.
    // 2. Setting the GPIO. Turn off the watchdog.
    // 3. Set the system clock source to the external low-frequency crystal oscillator.
    // Note: This interface must be called at the beginning of the main function.
    SysInit();

    /* Related modules initialization */
    // These XXX_Init() are defined in the source files of each module.
    CM_Init();  // Initializes the communication module
    SS_Init();  // Initializes the sensor module
    V_Init();   // Initialize the voltage module

    /* Related tasks creation */
    // 1. The entry functions for these tasks are defined in the source files of each module.
    // 2. The ids of these tasks are defined in the sysconf.h file.
    TskCreate(SSTask_SweepVolt, SSTASK_SWEEPVOLT);  // Sensor Sweep voltage
    TskCreate(SSTask_Activate, SSTASK_ACTIVATE);    // Activate sensor
    TskCreate(VTask_Probe, VTASK_PROBE);            // Power voltage measurement
    TskCreate(VTask_Activate, VTASK_ACTIVATE);      // Activate the power voltage measurement module
    TskCreate(CMTask_Activate, CMTASK_ACTIVATE);    // Activate the communication module

    /* System task scheduling */
    // Note: This interface must be called at the ending of the main function.
    SysSchedule();
}
