/*
 * software_timer.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

#define TIMER_CYCLE 10
#define WHEEL1 100
#define WHEEL2 99

extern volatile uint8_t timer_flag[];

uint8_t currentTimerSlotWheel1, currentTimerSlotWheel2;

typedef struct Timer{
	uint16_t duration;
	volatile uint8_t* timer_flag;
	struct Timer* next;
} Timer;

Timer* timerWheel1[WHEEL1];
Timer* timerWheel2[WHEEL2];

void set_timer(uint32_t duration, volatile uint8_t* timer_flag);

void cancel_timer(volatile uint8_t* timer_flag);

void timer_tick();

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim );

void unit_test_software_timer();

#endif /* INC_SOFTWARE_TIMER_H_ */
