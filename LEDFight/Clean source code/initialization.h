/*
 * initialization.h
 *
 * Created: 2014-12-03 23:43:35
 *  Author: Arek Chorian
 */ 

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include "led.h"

void init_io ();
void init_timer0 ();
void init_timer1 ();
void init_timer2 ();
void init_adc ();
void init_data ();
void program_polish_characters ();

#endif /* INITIALIZATION_H_ */