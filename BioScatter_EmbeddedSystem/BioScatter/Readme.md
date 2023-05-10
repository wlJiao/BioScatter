# Introduction

The whole program consists of the following four parts.

- **Task scheduling system**: It provides the task creation interface for users to use, and the following three module-related tasks are created using the interface provided by it. In addition, it includes several functional interfaces for completing system initialization.
- **Communication module**: It is responsible for communicating with the reader, providing a communication interface for other modules, and activating the sleeping tag.
- **Voltage monitoring and calibration module**: During the working period of tag, it completes the monitoring task of the power supply voltage and corrects the voltage of the voltage scanning module in time
- **Sensor module, or voltage sweep module**: It is responsible for the most important sensing task of tag, controlling the voltage applied to the electrode and completing the voltage sweep work.

# Files Declaration

- `System` folder: Task scheduling system code. It mainly includes system initialization, task registration, task scheduling and other functions.
- `Communication` folder: Communication module code. It includes task functions, module initialization functions, communication interface functions, and other functions.
- `Voltage` folder: Voltage monitoring and calibration module code. It includes task functions and module initialization functions, among other functions.
- `Sensor` folder: Sensor module code. It includes task functions and module initialization functions, among other functions.
- `sysconf.h`: The system task scheduling depends on `sysconf.h`, specifically, on the `TASK_COUNT` macro defined in `sysconf.h`. `TASK_COUNT` specifies the total number of tasks on the system and must therefore be defined. 
  > In addition, since some global variables are required for state switching between modules, we also declare some global variables and macro definitions in this file, which are defined in the `sysconf.c` file.
- `sysconf.c`: In this file, we define some global variables and macro definitions for each module to use for state switching.
- `main.c`: Complete system initialization, module initialization, task registration and start system scheduling in the main function.
- Other files and folders: CCS IDE project files and MSP430 system library files.

# System and Task

In order to improve the extensibility and maintainability of the code, we write a simple scheduling system.

Task is the basic unit of system scheduling, it is essentially a function. When scheduling a task, the system will execute the complete task from the beginning to the end (corresponding to the entire function body). This means that the next task cannot be scheduled until the last one is completely finished.

The MSP430 will remain in low-power mode LPM3 or LPM4 if there are no tasks in the system that are in a ready state.

The task ID is represented by a number ranging from 0 to 15. During each scheduling, the task with a smaller ID has a higher priority and will be executed first. One ID can correspond to only one task. The system supports a maximum of 16 tasks. In this application scenario, 16 tasks will satisfy our needs. In fact, the system can consist of up to 64 tasks (requiring changes to parts of the system code).

If you want to use the scheduling system, you must include the header file `system.h`.
You also need to create a `sysconf.h` file where you set the total number of tasks by defining `TASK_COUNT` with a macro.

System functions:
1. `SysInit()` must be called at the beginning of the main function, it initializes the system and MCU..
2. `SysSchedule()`  must be called at the ending of the main function, after it is invoked, the task registered in the system is scheduled.
3. To register a task with the system through the `TskCreate()` function, you must provide a task function entry and task ID.
4. A task can be set to ready state by calling `TskSetReady()`.
5. `TskExit()` must be called in each task entry function to indicate that the current task has completed.

Note:
1. Task functions cannot contain infinite loops.
2. If `TskExit()` is not called in the task function, the task will always be scheduled.
