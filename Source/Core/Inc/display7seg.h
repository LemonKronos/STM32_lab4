/*
 * display7seg.h
 *
 *  Created on: 1 thg 10, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "main.h"
#include "global.h"

extern uint8_t led_buffer[];
extern uint8_t led_index;
extern uint8_t led_counter[];
GPIO_TypeDef* port[7];
uint16_t pin[7];

//typedef enum{
//	traffic,
//	counter
//}update_from;

void display7SEG(uint8_t index);

void update7SEG(update_from where);

void countDown7SEG();

void number7SEG(uint8_t number);

void unit_test_7seg();

#endif /* INC_DISPLAY7SEG_H_ */
