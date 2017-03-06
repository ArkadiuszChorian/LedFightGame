/*
 * led.c
 *
 *  Created on: 10-11-2014
 *      Author: Arek Chorian
 */

#include "led.h"

void change_led_states (bool direction)
{
	shift_bits(direction);
	
	if (direction == CLEAN)
	{
		for (u08 i = 0; i < 24; i++)
		{
			DS_0;
			SHCP_1;
			SHCP_0;
		}
	} 
	else
	{
		for (u08 i = 0; i < NUMBER_OF_EMPTY_BITS; i++)
		{
			DS_0;
			SHCP_1;
			SHCP_0;
		}
		
		for (u08 i = NUMBER_OF_EMPTY_BITS; i < game_settings.number_of_leds+NUMBER_OF_EMPTY_BITS; i++)
		{
			if( CHECK_BIT(i) )
			DS_1;
			else
			DS_0;
			SHCP_1;
			SHCP_0;
		}
		
		for (u08 i = 0; i < NUMBER_OF_EMPTY_BITS; i++)
		{
			DS_0;
			SHCP_1;
			SHCP_0;
		}
		
		if (button_parameters.button1_relax == true)
		DS_1;
		else
		DS_0;
		SHCP_1;
		SHCP_0;
		
		if (button_parameters.button2_relax == true)
		DS_1;
		else
		DS_0;
		SHCP_1;
		SHCP_0;
	}

	STCP_1;
	STCP_0;
}

ISR(TIMER1_COMPB_vect)
{
	if ( player1_click_count > (player2_click_count + game_settings.threshold_of_change) )
	{
		player1_click_count = 0;
		player2_click_count = 0;
		
		if(!button_parameters.button2_relax)
		change_led_states(LEFT);
		
		if (CHECKIF_PLAYER1_WINS)
		{
			game_settings.player1_wins = true;
		}	
	}
	if ( player2_click_count > (player1_click_count + game_settings.threshold_of_change) )
	{
		player1_click_count = 0;
		player2_click_count = 0;
		
		if(!button_parameters.button1_relax)
		change_led_states(RIGHT);
		
		if (CHECKIF_PLAYER2_WINS)
		{
			game_settings.player2_wins = true;
		}
	}
	OCR1B += 30;
}

ISR(TIMER1_COMPA_vect)
{
	static u08 ledminus_auto_off = 0;
	
	if (game_settings.ledminus_auto_disable == true)
	{
		if (ledminus_auto_off == 2)
		{
			LEDMINUS_BONUS_OFF;
			ledminus_auto_off = 0;
		}
		ledminus_auto_off++;
	}
	
	saved_number = rand();
	
	if ( saved_number % game_settings.probability_of_bonus == 0 && game_settings.ledminus_bonus_enable == true )
	{
		LEDPLUS_BONUS_OFF;
		RELAX_BONUS_OFF;
		LEDMINUS_BONUS_ON;
	}
	if ( saved_number % game_settings.probability_of_bonus == 1 && game_settings.ledplus_bonus_enable == true )
	{
		LEDMINUS_BONUS_OFF;
		RELAX_BONUS_OFF;
		LEDPLUS_BONUS_ON;
	}
	if ( saved_number % game_settings.probability_of_bonus == 2 && game_settings.relax_bonus_enable == true )
	{
		LEDMINUS_BONUS_OFF;
		LEDPLUS_BONUS_OFF;
		RELAX_BONUS_ON;
	}
	
	OCR1B = 30;
}