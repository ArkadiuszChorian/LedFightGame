/*
 * common.h
 *
 * Created: 2015-01-05 23:45:45
 *  Author: Arek Chorian
 */ 

#ifndef COMMON_H_
#define COMMON_H_

#include "definitons.h"
#include "initialization.h"

volatile u08 random_number;

ISR(ADC_vect);

void save_current_settings ();
void load_last_settings ();
void load_default_settings ();
void check_last_settings ();

void game_setup ();
void check_end_of_battle ();

void button1_change_detect ();
void button1b_change_detect ();
void button2_change_detect ();
void button2b_change_detect ();

#endif /* COMMON_H_ */