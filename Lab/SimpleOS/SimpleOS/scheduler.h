#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "main.h"

#define MAX_TASK_SIZE 10

typedef struct TASK {
	uint32_t TID;
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	void (*pTask)();
} task_t;

typedef struct queue {
	task_t* task[MAX_TASK_SIZE];
	uint32_t size;
} queue_t;


task_t* createTask(uint32_t TID, uint32_t Period, uint32_t Delay, void(*pTask)());
void SCH_INIT();
uint32_t SCH_Add_Task(void (*func)(), uint32_t Delay, uint32_t Period);
void SCH_Update_Task();
void SCH_Dispatch_Task();
//uint8_t SCH_Delete_Task(const uint32_t TASK_IDX);

#endif // !_SCHEDULER_H_

