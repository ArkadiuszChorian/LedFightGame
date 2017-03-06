/*
 * button.c
 *
 * Created: 2014-11-13 00:24:17
 *  Author: Arek Chorian
 */ 

#include "button.h"

ISR(TIMER0_OVF_vect)
{
	static u08 autoclick_release = 0;
	static u16 relax_bonus_disable = 0;
	if (button_parameters.button1_to_check == check_1_to_0)
	{
		if( BTN1_0 && button_parameters.button1_state)
		{
			button_parameters.button1_state = !button_parameters.button1_state;
		}
	}
	
	if (button_parameters.button1_to_check == check_0_to_1)
	{
		if( BTN1_1 && !button_parameters.button1_state)
		{
			if(!button_parameters.button1_relax)
			player1_click_count++;
			button_parameters.button1_state = !button_parameters.button1_state;
		}
	}
	
	if (button_parameters.button1_relax)
	{
		autoclick_release++;
		relax_bonus_disable++;
		
		if(autoclick_release == game_settings.speed_of_autoclick)
		{
			player1_click_count++;
			autoclick_release = 0;
		}
		if(relax_bonus_disable == game_settings.time_of_autoclick)
		{
			button_parameters.button1_relax = 0;
			relax_bonus_disable = 0;
		}
	}
	
	TIMER0_CLEAR;
}

ISR(TIMER2_COMP_vect)
{
	static u08 autoclick_release = 0;
	static u16 relax_bonus_disable = 0;
	
	if(button_parameters.button2_to_check == check_1_to_0)
	{
		if( BTN2_0 && button_parameters.button2_state)
		{
			button_parameters.button2_state = !button_parameters.button2_state;
		}
	}
	
	if(button_parameters.button2_to_check == check_0_to_1)
	{
		if( BTN2_1 && !button_parameters.button2_state)
		{
			if(!button_parameters.button2_relax)
			player2_click_count++;
			button_parameters.button2_state = !button_parameters.button2_state;
		}
	}
	
	if (button_parameters.button2_relax)
	{
		autoclick_release++;
		relax_bonus_disable++;
		
		if(autoclick_release == game_settings.speed_of_autoclick)
		{
			player2_click_count++;
			autoclick_release = 0;
		}
		if(relax_bonus_disable == game_settings.time_of_autoclick)
		{
			button_parameters.button2_relax = 0;
			relax_bonus_disable = 0;
		}
	}
}