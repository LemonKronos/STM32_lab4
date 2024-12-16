/*
 * Scheduler.h
 *
 *  Created on: Nov 28, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
#include "stdlib.h"
#include "global.h"

extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim2;

//#define SCH_REPORT_STATUS
#ifdef SCH_REPORT_STATUS
    #define ERROR_PORT PORTA
#endif

typedef struct STask STask;
struct STask{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint8_t TaskID;
	STask* next;
};
STask* SCH_Task_List;

#define SCH_MAX_TASK 20
uint8_t RUNNING_TASK;
uint8_t ID_HOLDER;

typedef enum{
	NO_ERROR,
	ERROR_SCH_TASK_EMPTY,
	ERROR_SCH_REACH_MAX_TASKS
} E_CODE;
E_CODE ERROR_CODE;

typedef enum{
	FAILED,
	DONE
} R_CODE;

void SCH_Init();
void SCH_Update();
void SCH_AddTask(void (*pFunction)(), uint32_t, uint32_t);
void SCH_Dispatch();
R_CODE SCH_DeleteTask(const void (*pFunction)());
	#ifdef SCH_REPORT_STATUS
void SCH_ReportStatus();
	#endif
void SCH_GoSleep();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);
#endif /* INC_SCHEDULER_H_ */
