/*
 * fsm_run.c
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "fsm_run.h"
#include "global.h"
#include "traffic_light.h"
#include "display7seg.h"
#include "Scheduler.h"
#include "SCH_Task.h"
#include "fsm_input_driven.h"

uint8_t fsm_run_StateChange = 1;
extern uint8_t fsm_input_driven_normal_StateChange;
ledColor* color;

void fsm_run(machine_state mode){
	if(flagForButtonHold[0] == 1){
		m_mode = modeReset;
	}
	switch(mode){
	case mode1:// run normally
		if(flagForButtonPress[0] == 1){
			fsm_run_StateChange = 1;
			SCH_DeleteTask(timeCountDown);
			m_mode = mode2;
			resetButtonFlag();
		}
		else{
			if(fsm_run_StateChange){
				t_mode_main = RED;
				t_mode_side = YELLOW;
//				update7SEG(traffic);
				main_traffic.count_down = 0;
				side_traffic.count_down = 0;
				fsm_input_driven_normal_StateChange = 1;
				fsm_run_StateChange = 0;
			}
			fsm_input_driven_normal();
		}
		break;

	case mode2:
		if(flagForButtonPress[0] == 1){
			fsm_run_StateChange = 1;
			SCH_DeleteTask(toggleLedColor);
			m_mode = mode3;
			resetButtonFlag();
		}
		else{
			if(fsm_run_StateChange){
				flushLed();
				*color = lRED;
				TaskPara.para1 = (void*)color;
				SCH_AddTask(toggleLedColor, 50, 50);
				HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);

				led_counter[0] = main_traffic.red;
				led_counter[1] = 2;
				update7SEG(counter);
				fsm_run_StateChange = 0;
			}
			fsm_input_driven_config(&main_traffic.red, &side_traffic.green);
		}
		break;

	case mode3:
		if(flagForButtonPress[0] == 1){
			fsm_run_StateChange = 1;
			SCH_DeleteTask(toggleLedColor);
			m_mode = mode4;
			resetButtonFlag();
		}
		else{
			if(fsm_run_StateChange){
				flushLed();
				*color = lYELLOW;
				TaskPara.para1 = (void*)color;
				SCH_AddTask(toggleLedColor, 50, 50);

				led_counter[0] = main_traffic.yellow;
				led_counter[1] = 3;
				update7SEG(counter);
				fsm_run_StateChange = 0;
			}
			fsm_input_driven_config(&main_traffic.yellow, &side_traffic.red);
		}
		break;

	case mode4:
		if(flagForButtonPress[0] == 1){
			fsm_run_StateChange = 1;
			SCH_DeleteTask(toggleLedColor);
			m_mode = mode1;
			resetButtonFlag();
		}
		else{
			if(fsm_run_StateChange){
				flushLed();
				*color = lGREEN;
				TaskPara.para1 = (void*)color;
				SCH_AddTask(toggleLedColor, 50, 50);

				led_counter[0] = main_traffic.green;
				led_counter[1] = 4;
				update7SEG(counter);
				fsm_run_StateChange = 0;
			}
			fsm_input_driven_config(&main_traffic.green, &side_traffic.red);
		}
		break;

	default:// modeReset
		if(BUTTON[0] != HOLD){
			NVIC_SystemReset();
		}
		HAL_GPIO_TogglePin(TEST_GPIO_Port, TEST_Pin);
		break;
	}
}
