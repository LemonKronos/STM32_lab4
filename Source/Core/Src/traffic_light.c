/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2024
 *      Author: TRONG DAT
 */
#include "main.h"
#include "traffic_light.h"
#include "global.h"
#include "software_timer.h"
#include "display7seg.h"

traffic_mode	t_mode_main = RED,
				t_mode_side = YELLOW;

void fsm_traffic(traffic_mode* mode, traffic_way* Tway){
	switch(*mode){
	case RED:
		if(Tway->count_down == 0){
			*mode = GREEN;
			lit_green(Tway->way);
			Tway->count_down = Tway->green;
			update7SEG(traffic);
		}
		break;
	case YELLOW:
		if(Tway->count_down == 0){
			*mode = RED;
			lit_red(Tway->way);
			Tway->count_down = Tway->red;
			update7SEG(traffic);
		}
		break;
	case GREEN:
		if(Tway->count_down == 0){
			*mode = YELLOW;
			lit_yellow(Tway->way);
			Tway->count_down = Tway->yellow;
			update7SEG(traffic);
		}
		break;
	default:
		*mode = RED;
		lit_red(Tway->way);
		Tway->count_down = Tway->red;
		break;
	}
}

void lit_red(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, RESET);
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, RESET);
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
	}
}

void lit_yellow(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, RESET);
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, SET);
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, RESET);
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, SET);
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
	}
}

void lit_green(whichWay way){
	if(way == main_way){
		HAL_GPIO_WritePin(LED0_G_GPIO_Port, LED0_G_Pin, RESET);
		HAL_GPIO_WritePin(LED0_R_GPIO_Port, LED0_R_Pin, SET);
		HAL_GPIO_WritePin(LED0_Y_GPIO_Port, LED0_Y_Pin, SET);
	}
	if(way == side_way){
		HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, RESET);
		HAL_GPIO_WritePin(LED1_R_GPIO_Port, LED1_R_Pin, SET);
		HAL_GPIO_WritePin(LED1_Y_GPIO_Port, LED1_Y_Pin, SET);
	}
}
