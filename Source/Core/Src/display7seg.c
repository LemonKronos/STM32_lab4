/*
 * display7seg.c
 *
 *  Created on: 1 thg 10, 2024
 *      Author: TRONG DAT
 */
#include "display7seg.h"
#include "main.h"
#include "global.h"
#include "software_timer.h"

extern traffic_way main_traffic, side_traffic;

GPIO_TypeDef* ports[7] = {
    SEG0_GPIO_Port,
    SEG1_GPIO_Port,
    SEG2_GPIO_Port,
    SEG3_GPIO_Port,
    SEG4_GPIO_Port,
    SEG5_GPIO_Port,
    SEG6_GPIO_Port
};

uint16_t pins[7] = {
    SEG0_Pin,
    SEG1_Pin,
    SEG2_Pin,
    SEG3_Pin,
    SEG4_Pin,
    SEG5_Pin,
    SEG6_Pin
};


void display7SEG(uint8_t index){
	switch(index){
	case 0://SEG_0
		number7SEG(led_buffer[0]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	case 1://SEG_1
		number7SEG(led_buffer[1]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	case 2://SEG_2
		number7SEG(led_buffer[2]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	case 3://SEG_3
		number7SEG(led_buffer[3]);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		break;
	case 99:// ALL OFF
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	default:
		index = 0;
		break;
	}
};

void update7SEG(update_from where){
	if(where == traffic){
		led_buffer[0] = main_traffic.count_down / 10;
		if(led_buffer[0] == 0) led_buffer[0] = 10;
		led_buffer[1] = main_traffic.count_down % 10;

		led_buffer[2] = side_traffic.count_down / 10;
		if(led_buffer[2] == 0) led_buffer[2] = 10;
		led_buffer[3] = side_traffic.count_down % 10;
	}
	else if(where == counter){
		led_buffer[0] = led_counter[0] / 10;
		if(led_buffer[0] == 0) led_buffer[0] = 10;
		led_buffer[1] = led_counter[0] % 10;

		led_buffer[2] = led_counter[1] / 10;
		if(led_buffer[2] == 0) led_buffer[2] = 10;
		led_buffer[3] = led_counter[1] % 10;
	}
};

void countDown7SEG(){
	main_traffic.count_down--;
	side_traffic.count_down--;
	update7SEG(traffic);
};

void number7SEG(uint8_t number){
	switch(number) {
	    case 10: // ALL OFF
	        HAL_GPIO_WritePin(ports[0], pins[0], SET);
	        HAL_GPIO_WritePin(ports[1], pins[1], SET);
	        HAL_GPIO_WritePin(ports[2], pins[2], SET);
	        HAL_GPIO_WritePin(ports[3], pins[3], SET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], SET);
	        break;
	    case 0:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], RESET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], SET);
	        break;
	    case 1:
	        HAL_GPIO_WritePin(ports[0], pins[0], SET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], SET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], SET);
	        break;
	    case 2:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], SET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], RESET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 3:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 4:
	        HAL_GPIO_WritePin(ports[0], pins[0], SET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], SET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 5:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], SET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 6:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], SET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], RESET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 7:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], SET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], SET);
	        break;
	    case 8:
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], RESET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    case 9:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], RESET);
	        HAL_GPIO_WritePin(ports[2], pins[2], RESET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], RESET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	        break;
	    default:
	        HAL_GPIO_WritePin(ports[0], pins[0], RESET);
	        HAL_GPIO_WritePin(ports[1], pins[1], SET);
	        HAL_GPIO_WritePin(ports[2], pins[2], SET);
	        HAL_GPIO_WritePin(ports[3], pins[3], RESET);
	        HAL_GPIO_WritePin(ports[4], pins[4], SET);
	        HAL_GPIO_WritePin(ports[5], pins[5], SET);
	        HAL_GPIO_WritePin(ports[6], pins[6], RESET);
	}
};

void unit_test_7seg(){
	if(timer_flag[0] >= 1){
		if(led_counter[0] > 0) led_counter[0]--;
		else led_counter[0] = 99;
		if(led_counter[1] > 0) led_counter[1]--;
		else led_counter[1] = 99;
		update7SEG(counter);
		HAL_GPIO_TogglePin(TEST_Timer_GPIO_Port, TEST_Timer_Pin);

		set_timer(1000, &timer_flag[0]);
	}
	if(timer_flag[1] >= 1){
		if(led_index >= MAX_LED) led_index = 0;
		display7SEG(led_index++);
		HAL_GPIO_TogglePin(TEST_Button_GPIO_Port, TEST_Button_Pin);

		set_timer(250, &timer_flag[1]);
	}
};
