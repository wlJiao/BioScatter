/*******************************************************************
 * The system task scheduling depends on sysconf.h, specifically, on
 * the TASK_COUNT macro defined in this file. TASK_COUNT specifies
 * the total number of tasks on the system and must therefore be
 * defined.
 *
 * The task ID is defined as an enumeration type for ease of
 * administration, or it can be specified directly as a task ID
 * with a number in the range 0 to 15.
 *******************************************************************/

#ifndef SYSCONF_H_
#define SYSCONF_H_


/* All task information in the system. */
#define TASK_COUNT               5   // Count of tasks.
enum {                               // Task ID.
    SSTASK_SWEEPVOLT,
    SSTASK_ACTIVATE,
    VTASK_PROBE,
    VTASK_ACTIVATE,
    CMTASK_ACTIVATE
};


/* Some variables and macro definitions required for task execution. */
#define SENSECOUNT                2    // Sense count.
extern unsigned int Setup_senseCount;  // Sense count.
extern float        V_vp;              // The detected power supply voltage.
extern unsigned int V_stopFlag;        // Indicates that the voltage module is stop.
extern unsigned int SS_stopFlag;       // Indicates that the sensor module is stop.
extern unsigned int SS_exceptionFlag;  // Indicates that the sensor module is abnormal.

#endif /* SYSCONF_H_ */
