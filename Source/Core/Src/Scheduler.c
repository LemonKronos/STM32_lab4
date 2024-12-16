/*
 * Scheduler.c
 *
 *  Created on: Nov 28, 2024
 *      Author: TRONG DAT
 */
#include "Scheduler.h"
#include "input_reading.h"

void SCH_Init(){
	while(SCH_Task_List != NULL){
		STask* temp = SCH_Task_List;
		SCH_Task_List = SCH_Task_List->next;
		free(temp);
	}
	ERROR_CODE = 0;
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_IWDG_Init(&hiwdg);
}

void SCH_Update() {
	if(SCH_Task_List != NULL){
		if(SCH_Task_List->Delay > 0){
			SCH_Task_List->Delay--;
		}
		else{
			STask* temp = SCH_Task_List;
			while(temp->Delay == 0){
				temp->RunMe = 1;
				if(temp->Period){
					RUNNING_TASK--;
					SCH_AddTask(temp->pTask, temp->Period, temp->Period);
				}
				temp = temp->next;
			}
		}
	}
}

void SCH_AddTask(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	if(RUNNING_TASK >= SCH_MAX_TASK){
		ERROR_CODE = ERROR_SCH_REACH_MAX_TASKS;
		return;
	}
	STask* newTask = malloc(sizeof(STask));
	newTask->pTask = pFunction;
	newTask->Delay = DELAY;
	newTask->Period = PERIOD;
	newTask->TaskID = ID_HOLDER++;
	newTask->next = NULL;

	if(SCH_Task_List == NULL){
		SCH_Task_List = newTask;
	}
	else{
		STask* temp = SCH_Task_List;
		STask* pre;
		while(temp != NULL && temp->Delay < newTask->Delay){
			newTask->Delay -= temp->Delay;
			pre = temp;
			temp = temp->next;
		}
		newTask->next = temp;
		if(pre == NULL){
			SCH_Task_List = newTask;
		}
		else{
			pre->next = newTask;
		}
		if(temp != NULL){
			temp->Delay -= newTask->Delay;
		}
	}
	RUNNING_TASK++;
}

void SCH_Dispatch() {
	if(SCH_Task_List != NULL){
		while(SCH_Task_List->RunMe >= 1){
			SCH_Task_List->pTask();
			SCH_Task_List->RunMe--;
			if(SCH_Task_List->Period == 0) RUNNING_TASK--;
			STask* deleteTask = SCH_Task_List;
			SCH_Task_List = SCH_Task_List->next;
			free(deleteTask);
		}
	}
#ifdef SCH_REPORT_STATUS
    SCH_ReportStatus();
#endif
    SCH_GoSleep();
}

R_CODE SCH_DeleteTask(const void (*pFunction)()) {
	if(SCH_Task_List == NULL) ERROR_CODE = ERROR_SCH_TASK_EMPTY;
	else{
		STask* temp = SCH_Task_List;
		if(SCH_Task_List->pTask == pFunction){
			__disable_irq();
			SCH_Task_List = SCH_Task_List->next;
			free(temp);
			__enable_irq();
		}
		while(temp != NULL){
			if(temp->next->pTask == pFunction){
				__disable_irq();
				STask* deleteTask = temp->next;
				temp->next = deleteTask->next;
				free(deleteTask);
				__enable_irq();
			}
			temp = temp->next;
		}
		return DONE;
	}
	return FAILED;
}

#ifdef SCH_REPORT_STATUS
void SCH_ReportStatus(void) {
    #ifdef SCH_REPORT_ERRORS
    if (ERROR_CODE != LAST_ERROR_CODE) {
    	ERROR_PORT = 255 - ERROR_CODE;
    	LAST_ERROR_CODE = ERROR_CODE;
        if (ERROR_CODE != 0) {
            ERROR_TICK_COUNT = 60000;
        } else {
        	ERROR_TICK_COUNT = 0;
        }
    } else {
        if (ERROR_TICK_COUNT != 0) {
            if (--ERROR_TICK_COUNT == 0) {
            	ERROR_CODE = 0;
            }
        }
    }
    #endif
}
#endif

void SCH_GoSleep(){
	__WFI(); // System wait for interrupt
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if(htim->Instance == TIM2){
		button_reading();
		SCH_Update();
		HAL_IWDG_Refresh(&hiwdg);
		#ifdef P_CLOCK
			p_clockRun();
		#endif
	}
}
