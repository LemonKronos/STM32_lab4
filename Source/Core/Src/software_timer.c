/*
 * software_timer.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "input_reading.h"
#include "software_timer.h"
#include "main.h"
#include "stdlib.h"
#include "global.h"

uint8_t  currentTimerSlotWheel1 = 0, currentTimerSlotWheel2 = 0;

void set_timer(uint32_t duration, volatile uint8_t* timer_flag){
	*timer_flag = 0;
	Timer* newTimer = (Timer*)malloc(sizeof(Timer));
	if (newTimer == NULL) return;
	newTimer->duration = duration;
	newTimer->timer_flag = timer_flag;
	if(duration / TIMER_CYCLE >= WHEEL1){// assign to wheel 2
		uint8_t newTimerSlot = (currentTimerSlotWheel2 + (duration / TIMER_CYCLE) / WHEEL1) % WHEEL2;
		newTimer->next = timerWheel2[newTimerSlot];
		timerWheel2[newTimerSlot] = newTimer;
	}
	else{// assign to wheel 1
		uint8_t newTimerSlot = (currentTimerSlotWheel1 + duration / TIMER_CYCLE) % WHEEL1;
		newTimer->next = timerWheel1[newTimerSlot];
		timerWheel1[newTimerSlot] = newTimer;
	}
}

void cancel_timer(volatile uint8_t* timer_flag){
	uint8_t flagCancel = 0;
	uint8_t index = 0;
	while(index < WHEEL2 - 1 && flagCancel != 1){
        Timer* processTimer = timerWheel2[index];
        while(processTimer != NULL){
        	if(processTimer->timer_flag == timer_flag){
        		Timer* temp = processTimer;
        		if(temp == timerWheel2[index]){// head
        			timerWheel2[index] = temp->next;
        		}
					processTimer = temp->next;
					free(temp);
					flagCancel = 1;
					break;
        	}
        	else processTimer = processTimer->next;
        }
		index++;
	}
	index = 0;
	while(index < WHEEL1 - 1 && flagCancel != 1){
		Timer* processTimer = timerWheel1[index];
		while(processTimer != NULL){
			if(processTimer->timer_flag == timer_flag){
				Timer* temp = processTimer;
				if(temp == timerWheel1[index]){// head
					timerWheel1[index] = temp->next;
				}
				processTimer = temp->next;
				free(temp);
				flagCancel = 1;
				break;
			}
			else processTimer = processTimer->next;
		}
		index++;
	}
//	if(flagCancel == 0) HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, RESET);
//	else HAL_GPIO_WritePin(TEST_GPIO_Port, TEST_Pin, SET);
}

void timer_tick(){
    if (currentTimerSlotWheel1 <= 0){
        Timer* processTimer = timerWheel2[currentTimerSlotWheel2];
        while (processTimer != NULL){
            uint8_t newTimerSlot = (processTimer->duration / TIMER_CYCLE) % WHEEL1;
            Timer* newTimer = (Timer*)malloc(sizeof(Timer));
            if (newTimer == NULL) return;
            newTimer->duration = processTimer->duration % (WHEEL1 * TIMER_CYCLE);
            newTimer->timer_flag = processTimer->timer_flag;
            newTimer->next = timerWheel1[newTimerSlot];
            timerWheel1[newTimerSlot] = newTimer;

            Timer* temp = processTimer;
            processTimer = processTimer->next;
            free(temp);
        }
        timerWheel2[currentTimerSlotWheel2] = NULL;
    }

    Timer* processTimer = timerWheel1[currentTimerSlotWheel1];
    while (processTimer != NULL) {
        *(processTimer->timer_flag) = 1;
        Timer* temp = processTimer;
        processTimer = processTimer->next;
        free(temp);
    }
    timerWheel1[currentTimerSlotWheel1] = NULL;
    currentTimerSlotWheel1 = (currentTimerSlotWheel1 + 1) % WHEEL1;
    if(currentTimerSlotWheel1 >= 99) currentTimerSlotWheel2 = (currentTimerSlotWheel2 + 1) % WHEEL2;
}

//void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
//	if( htim->Instance == TIM2 ){
//		timer_tick();
//		button_reading();
//#ifdef P_CLOCK
//		p_clockRun();
//#endif
//	}
//}

void unit_test_software_timer(){
	if(timer_flag[0] == 1){
		HAL_GPIO_TogglePin(TEST_Timer_GPIO_Port, TEST_Timer_Pin);
		set_timer(1000, &timer_flag[0]);
	}
}

