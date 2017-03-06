/*
 * LEDFight.c
 *
 * Created: 2014-11-11 00:39:54
 *  Author: Arek Chorian
 */ 

#include "common.h"

int main(void)
{
	sei();
	
	ENABLE_PLAYER1_INTERRUPT;  
	ENABLE_PLAYER2_INTERRUPT;     
	ENABLE_LEDCHANGE_INTERRUPT;   
	ENABLE_BONUS_INTERRUPT;	
	
	init_io();
	init_data();
	lcd_init();
	check_last_settings();
	program_polish_characters();
	init_adc();
	_delay_ms(10);
	DISABLE_ADC;
	srand(random_number);
	
	lcd_cls();
	lcd_locate(0,0);
	lcd_str(":::::: LED :::::");
	lcd_locate(1,0);
	lcd_str("::::: FIGHT ::::");
	_delay_ms(2000);
	
	game_setup();	
	
    while(1)
    {		
		check_end_of_battle();		
		button1_change_detect();
		button1b_change_detect();
		button2_change_detect();
		button2b_change_detect();
    }
}