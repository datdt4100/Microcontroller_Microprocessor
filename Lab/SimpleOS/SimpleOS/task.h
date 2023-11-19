#ifndef _TASK_H_
#define _TASK_H_
#include "main.h"
#define MAX_TASK_SIZE 10

typedef struct TASK {
	uint32_t TID;
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	void (*pTask)();
} task_t;


task_t* taskList[MAX_TASK_SIZE];
int runSize;

task_t* taskRun[MAX_TASK_SIZE];
int taskSize;

uint8_t isEmpty()
{
	return (taskSize == 0);
}
task_t* createTask(uint32_t TID, uint32_t Period, uint32_t Delay, void(*pTask)())
{
	task_t* newTask = (task_t*)malloc(sizeof(task_t));
	newTask->TID = TID;
	newTask->Delay = Delay;
	newTask->Period = Period;
	newTask->pTask = pTask;
	newTask->RunMe = 0;

	return newTask;
}
void addTask(task_t* pTask)
{
	int idx = taskSize;
	int waitTime = 0;
	while (idx != 0 && taskList[idx - 1]->Delay + waitTime < pTask->Delay)
	{
		waitTime += taskList[idx - 1]->Delay;
		taskList[idx] = taskList[idx - 1];
		idx--;
	}
	pTask->Delay -= waitTime;
	taskList[idx] = pTask;
	if (idx != 0)
	{
		taskList[idx - 1]->Delay -= taskList[idx]->Delay;
	}
}


#endif // !_TASK_H_

