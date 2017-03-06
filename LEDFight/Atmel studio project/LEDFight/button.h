/*
 * button.h
 *
 * Created: 2014-11-13 00:24:34
 *  Author: Arek Chorian
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#include "definitons.h"

volatile button_struct button_parameters;
volatile u08 player1_click_count;
volatile u08 player2_click_count;

ISR(TIMER0_OVF_vect);
ISR(TIMER2_COMP_vect);

#endif /* BUTTON_H_ */