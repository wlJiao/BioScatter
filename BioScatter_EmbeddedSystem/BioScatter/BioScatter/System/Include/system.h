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

#ifndef SYSTEM_INCLUDE_SYSTEM_H_
#define SYSTEM_INCLUDE_SYSTEM_H_

#include <msp430.h>
#include "sysconf.h"
#include "sysdef.h"
#include "board.h"

/* System task Count */
// You also need to create a sysconf.h file where you set the total number of tasks by defining TASK_COUNT with a macro.
// If you don't, the total number of tasks will always be zero, which will cause tasks to not be scheduled properly.
#ifndef TASK_COUNT
#define TASK_COUNT      0
#endif

/* System global variable */
extern volatile task_t curTask;                                       // ID of the task that is being executed.
extern volatile uint16_t tskReady;                                    // When task x(ID) is ready, tskReady will be set to 1 in the x-th position.
extern void (*tskList[TASK_COUNT])(void);                             // Task list, which holds the function entry for all tasks.
extern const uint8_t __lowest_bit_bitmap[];                           // Used to find the position of the lowest 1 in tskReady.

void SysInit(void);                                                   // System initialize.
void SysSchedule(void);                                               // The system starts scheduling tasks and does not return
void TskCreate(void (*entry)(void), task_t task);                     // To register a system task, you must specify the task entry and task ID

static inline void TskSetReady(task_t task){tskReady |= (1<<task);}   // Set a task to ready state for execution by the scheduled system
static inline void TskExit(void){tskReady &= ~(1<<curTask);}          // Called in the task entry function to indicate the completion of the current task
static inline int __ffs(int value)                                    // To find the position of the lowest 1 in tskReady.
{
    if (value == 0) return 0;
    if (value & 0xff)
        return __lowest_bit_bitmap[value & 0xff] + 1;
    if (value & 0xff00)
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;
    return 0;
}

#endif /* SYSTEM_INCLUDE_SYSTEM_H_ */
