/*
 * input_processing.h
 *
 *  Created on: Oct 9, 2024
 *      Author: TRONG DAT
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "global.h"

extern button_state BUTTON[];

GPIO_PinState button_pin_read(uint8_t index);
void button_reading();
void resetButtonFlag();
//unsigned char is_button_press(unsigned char index);
//unsigned char is_button_hold(unsigned char index);
//unsigned char is_button_double_tap(unsigned char index);
//unsigned char is_button_tap_hold(unsigned char index);

#ifdef UNIT_TEST
void unit_test_button_press();
void unit_test_button_read();
#endif

#endif /* INC_INPUT_READING_H_ */
