/*
 * global.h
 *
 *  Created on: 28 thg 10, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define UNIT_TEST
#define P_CLOCK

#ifdef P_CLOCK
  int p_flag;
  int p_dur;
  void p_clockSet(int dur);
void p_clockRun();
#endif

// software timer
#define SEC 1000
#define NUM_FLAG 5
	/* FLAG NOTE
	 *0 blinky led
	 *1 main way
	 *2 side way
	 *3 1s to count down for 7seg led
	 *4 refresh for 7seg led
	 *5 countdown 500ms in hold state
	 * */

volatile uint8_t timer_flag[NUM_FLAG];

// 7 segment led
#define REFRESH_RATE 5 //Hz
#define REFRESH_CYCLE 100/REFRESH_RATE //10ms
#define MAX_LED 4
uint8_t led_buffer[MAX_LED];
uint8_t led_index;
uint8_t led_counter[2];
typedef enum{
	traffic,
	counter
}update_from;

// traffic light
#define MAX_COUNT_DOWN 99
typedef enum whichWay{
	main_way,
	side_way
}whichWay;

typedef struct traffic_way{
	whichWay  way;
	uint8_t count_down;
	uint8_t red, yellow, green;
	uint8_t current_red, current_yellow, current_green;
}traffic_way;

// button
#define NUMBER_OF_BUTTONS 3

typedef enum{
	IDLE,
	PRESS,
	HOLD,
	DOUBLE_TAP,
	TAP_HOLD
}button_state;

button_state BUTTON[NUMBER_OF_BUTTONS];

unsigned char
	flagForButtonPress[NUMBER_OF_BUTTONS],
	flagForButtonHold[NUMBER_OF_BUTTONS],
	flagForButtonDoubleTap[NUMBER_OF_BUTTONS],
	flagForButtonTapHold[NUMBER_OF_BUTTONS];

// finite state machine
typedef enum machine_state{
	mode1,
	mode2,
	mode3,
	mode4,
	modeReset
}machine_state;
volatile machine_state m_mode;

// SCH
typedef struct{
	void* para1;
	void* para2;
	void* para3;
}Task_parameter;
Task_parameter TaskPara;
#endif /* INC_GLOBAL_H_ */
