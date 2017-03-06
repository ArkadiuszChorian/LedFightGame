/*
 * led.h
 *
 *  Created on: 10-11-2014
 *      Author: Arek Chorian
 */

#ifndef LED_H_
#define LED_H_

#include "definitons.h"
#include "button.h"

volatile u32 led_states;
volatile u08 saved_number;

extern volatile button_struct button_parameters;
extern volatile u08 player1_click_count;
extern volatile u08 player2_click_count;

void change_led_states (bool);
inline void shift_bits (bool) __attribute__((always_inline));

ISR(TIMER1_COMPA_vect);
ISR(TIMER1_COMPB_vect);

inline void shift_bits (bool direction)
{
	if (direction == RIGHT)
	{
		led_states = (led_states>>2)|(1UL<<31);
	}
	if (direction == LEFT)
	{
		led_states = (led_states<<2)|1UL;
	}
}

#endif /* LED_H_ */
