/*
 * SCH_Task.c
 *
 *  Created on: Nov 28, 2024
 *      Author: TRONG DAT
 */
#include "SCH_Task.h"
#include "global.h"
#include "display7seg.h"
#include "fsm_input_driven.h"

extern traffic_way main_traffic, side_traffic;

void LedBlinky(){
	HAL_GPIO_TogglePin(TEST_Timer_GPIO_Port, TEST_Timer_Pin);
}
void timeCountDown(){
	main_traffic.count_down--;
	side_traffic.count_down--;
	update7SEG(traffic);
}
void timeCountUpFast(){
	if(led_counter[0] < MAX_COUNT_DOWN) led_counter[0]++;
	else led_counter[0] = 0;
	update7SEG(counter);
}
void timeCountDownFast(){
	if(led_counter[0] > 0) led_counter[0]--;
	else led_counter[0] = MAX_COUNT_DOWN;
	update7SEG(counter);
}
void display7segment(){
	if(led_index >= MAX_LED) led_index = 0;
	display7SEG(led_index++);
}
void toggleLedColor(){
	ledColor* color = (ledColor*)TaskPara.para1;
	switch(*color){
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
