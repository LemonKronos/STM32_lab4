/*
 * input_processing.c
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */
#include "fsm_input_driven.h"
#include "main.h"
#include "global.h"
#include "display7seg.h"
#include "Scheduler.h"
#include "SCH_Task.h"

extern volatile uint8_t timer_flag[];

normal_mode Nmode = NORMAL;
config_mode Cmode = WAIT;

uint8_t fsm_input_driven_normal_StateChange = 1;
uint8_t fsm_input_driven_config_StateChange = 1;

void fsm_input_driven_normal(){
	switch(Nmode){
	case NORMAL:
		if(flagForButtonPress[1] == 1){
			fsm_input_driven_normal_StateChange = 1;
			Nmode = FREEZE;
			resetButtonFlag();
		}
		else if(flagForButtonPress[2] == 1){
			fsm_input_driven_normal_StateChange = 1;
			Nmode = FORWARD;
			resetButtonFlag();
		}
		else if(flagForButtonHold[2] == 1){
			fsm_input_driven_normal_StateChange = 1;
			Nmode = FAST;
			resetButtonFlag();
		}
		else{// RUN NORMAL
			if(fsm_input_driven_normal_StateChange){
				SCH_AddTask(timeCountDown, 100, 100);
				fsm_input_driven_normal_StateChange = 0;
			}
			fsm_traffic(&t_mode_main, &main_traffic);
			fsm_traffic(&t_mode_side, &side_traffic);
		}
		break;
	case FREEZE:
		if(flagForButtonPress[1] == 1){// CHECK BUTTON
			fsm_input_driven_normal_StateChange = 1;
			Nmode = NORMAL;
			resetButtonFlag();
		}
		else if(flagForButtonPress[2] == 1){
			Nmode = FORWARD;
			resetButtonFlag();
		}
		else{// RUN FREEZE
			if(fsm_input_driven_normal_StateChange){
				SCH_DeleteTask(timeCountDown);
				fsm_input_driven_normal_StateChange = 0;
			}
			fsm_traffic(&t_mode_main, &main_traffic);
			fsm_traffic(&t_mode_side, &side_traffic);
		}
		break;
	case FAST:
		if(BUTTON[2] == HOLD){
			if(fsm_input_driven_normal_StateChange){
				SCH_DeleteTask(timeCountDown);
				SCH_AddTask(timeCountDown, 50, 50);
				fsm_input_driven_normal_StateChange = 0;
			}
			fsm_traffic(&t_mode_main, &main_traffic);
			fsm_traffic(&t_mode_side, &side_traffic);
		}
		else{
			SCH_DeleteTask(timeCountDown);
			fsm_input_driven_normal_StateChange = 1;
			Nmode = NORMAL;
			resetButtonFlag();
		}
		break;
	case FORWARD:
		SCH_DeleteTask(timeCountDown);
		if(main_traffic.count_down > side_traffic.count_down){
			main_traffic.count_down -= side_traffic.count_down;
			side_traffic.count_down = 0;
		}
		else{
			side_traffic.count_down -= main_traffic.count_down;
			main_traffic.count_down = 0;
		}
		update7SEG(traffic);
		fsm_input_driven_normal_StateChange = 0;
		Nmode = FREEZE;
		resetButtonFlag();
		break;
	default:
		Nmode = NORMAL;
		HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
		break;
	}
}

void fsm_input_driven_config(uint8_t* time1, uint8_t* time2){
	switch(Cmode){
	case WAIT:
		if(flagForButtonPress[1] == 1){
			Cmode = UP;
			resetButtonFlag();
		}
		else if(flagForButtonHold[1] == 1){
			fsm_input_driven_config_StateChange = 1;
			Cmode = UP_FAST;
			resetButtonFlag();
		}
		else if(flagForButtonDoubleTap[1] == 1){
			Cmode = DOWN;
			resetButtonFlag();
		}
		else if(flagForButtonTapHold[1] == 1){
			fsm_input_driven_config_StateChange = 1;
			Cmode = DOWN_FAST;
			resetButtonFlag();
		}
		else if(flagForButtonPress[2] == 1){
			if(led_counter[0] != 0){
				if(led_counter[0] >= *time1){
					*time2 = *time2 + (led_counter[0] - *time1);
				}
				else{
					*time2 = *time2 - (*time1 - led_counter[0]);
				}
				*time1 = led_counter[0];
			}
		}
		else{// RUN WAIT
			if(fsm_input_driven_config_StateChange){
				// NOTHING HERE
				fsm_input_driven_config_StateChange = 0;
			}
		}
		break;
	case UP:
		if(led_counter[0] < MAX_COUNT_DOWN) led_counter[0]++;
		else led_counter[0] = 0;
		update7SEG(counter);
		Cmode = WAIT;
		break;
	case UP_FAST:
		if(BUTTON[1] == HOLD){
			if(fsm_input_driven_config_StateChange){
				SCH_AddTask(timeCountUpFast, 25, 25);
				fsm_input_driven_config_StateChange = 0;
			}
		}
		else{
			SCH_DeleteTask(timeCountUpFast);
			resetButtonFlag();
			Cmode = WAIT;
		}
		break;
	case DOWN:
		if(led_counter[0] > 0) led_counter[0]--;
		else led_counter[0] = MAX_COUNT_DOWN;
		update7SEG(counter);
		Cmode = WAIT;
		break;
	case DOWN_FAST:
		if(BUTTON[1] == TAP_HOLD){
			if(fsm_input_driven_config_StateChange){
				SCH_AddTask(timeCountDownFast, 25, 25);
				fsm_input_driven_config_StateChange = 0;
			}
		}
		else{
			SCH_DeleteTask(timeCountDownFast);
			resetButtonFlag();
			Cmode = WAIT;
		}
		break;
	default:
		Cmode = WAIT;
		break;
	}
}

void toggleLed(ledColor color){
	switch(color){
	case lRED:
		HAL_GPIO_TogglePin(LED0_R_GPIO_Port, LED0_R_Pin);
		HAL_GPIO_TogglePin(LED1_R_GPIO_Port, LED1_R_Pin);
		break;
	case lYELLOW:
		HAL_GPIO_TogglePin(LED0_Y_GPIO_Port, LED0_Y_Pin);
		HAL_GPIO_TogglePin(LED1_Y_GPIO_Port, LED1_Y_Pin);
		break;
	case lGREEN:
		HAL_GPIO_TogglePin(LED0_G_GPIO_Port, LED0_G_Pin);
		HAL_GPIO_TogglePin(LED1_G_GPIO_Port, LED1_G_Pin);
		break;
	}
}

void flushLed(){
	HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
	HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
	HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
	HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
	HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
	HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
}
