/*
 * common.c
 *
 * Created: 2015-01-05 23:45:29
 *  Author: Arek Chorian
 */ 

#include "common.h"

settings_struct last_game_settings EEMEM;
const settings_struct default_game_settings PROGMEM = {
	DEFAULT_number_of_leds,
	DEFAULT_threshold_of_change,
	DEFAULT_frequency_of_bonus,
	DEFAULT_probability_of_bonus,
	DEFAULT_ledminus_bonus_enable,
	DEFAULT_ledplus_bonus_enable,
	DEFAULT_relax_bonus_enable,
	DEFAULT_speed_of_autoclick,
	DEFAULT_time_of_autoclick,
	DEFAULT_ledminus_auto_disable,
	DEFAULT_player1_wins,
	DEFAULT_player2_wins,
	DEFAULT_shift_direction
};

void save_current_settings ()
{
	eeprom_write_block((settings_struct *)&game_settings, &last_game_settings, sizeof(game_settings));
}
void load_last_settings ()
{
	eeprom_read_block((settings_struct *)&game_settings, &last_game_settings, sizeof(game_settings));
}
void load_default_settings ()
{
	memcpy_P((settings_struct *)&game_settings, &default_game_settings, sizeof(default_game_settings));
}
void check_last_settings ()
{
	u08 number_of_byte;
	u08 lenght_of_gamesettings = sizeof(game_settings);
	u08 *game_settings_pointer = (u08 *)&game_settings;
	
	load_last_settings();
	
	for (number_of_byte = 0; number_of_byte < lenght_of_gamesettings; number_of_byte++)
	{
		if (0 == *game_settings_pointer++)
		continue;
		else
		break;
	}
	
	if (number_of_byte == lenght_of_gamesettings)
	load_default_settings();
}

void game_setup ()
{
	cli();
	lcd_cls();
	
	enum menu_blocks main_menu_flag = QUICK_GAME;
	enum menu_blocks2 settings_menu_flag = MAIN_MENU;
	
	while(1)
	{
		_delay_ms(100);
		
		if (PLUS_BUTTON && settings_menu_flag == MAIN_MENU)
		{
			if (main_menu_flag < RESET_SETTINGS)
			main_menu_flag++;
			else
			main_menu_flag = QUICK_GAME;
			lcd_cls();
		}
		if (MINUS_BUTTON && settings_menu_flag == MAIN_MENU)
		{
			if (main_menu_flag > QUICK_GAME)
			main_menu_flag--;
			else
			main_menu_flag = RESET_SETTINGS;
			lcd_cls();
		}
		if (RETURN_BUTTON)
		{
			if (settings_menu_flag != MAIN_MENU)
			save_current_settings();
			settings_menu_flag = MAIN_MENU;
			main_menu_flag = QUICK_GAME;
			lcd_cls();
		}
		
		if (main_menu_flag == QUICK_GAME)
		{
			lcd_locate(0,0);
			lcd_str("=== NOWA GRA ===");
			lcd_locate(1,0);
			lcd_str("================");
			if (SELECT_BUTTON)
			{
				break;
				lcd_cls();
			}
		}
		
		if (main_menu_flag == SETTINGS)
		{
			if (settings_menu_flag == MAIN_MENU)
			{
				lcd_locate(0,0);
				lcd_str("===USTAWIENIA===");
				lcd_locate(1,0);
				lcd_str("================");
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == NUMBER_OF_LEDS)
			{
				lcd_locate(0,0);
				lcd_str("Liczba p"_o"l" );
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_int(game_settings.number_of_leds/2);
				lcd_str(" ");
				if (PLUS_BUTTON)
				{
					if (game_settings.number_of_leds < 22)
					{
						game_settings.number_of_leds += 4;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.number_of_leds > 6)
					{
						game_settings.number_of_leds -= 4;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == THRESHOLD_OF_CHANGE)
			{
				lcd_locate(0,0);
				lcd_str("Czu"_l"o"_s _c " pad"_o"w");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_int(game_settings.threshold_of_change+1);
				if (PLUS_BUTTON)
				{
					if (game_settings.threshold_of_change < 3)
					{
						game_settings.threshold_of_change++;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.threshold_of_change > 0)
					{
						game_settings.threshold_of_change--;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == FREQUENCY_OF_BONUS)
			{
				lcd_locate(0,0);
				lcd_str("Cz"_e"sto"_s _c" bonus"_o"w");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("co ");
				lcd_int( (((u32)(game_settings.frequency_of_bonus)+1)*256)/8000);
				lcd_str(" ms ");
				if (PLUS_BUTTON)
				{
					if (game_settings.frequency_of_bonus < 62499)
					{
						game_settings.frequency_of_bonus += 3125;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.frequency_of_bonus > 3124)
					{
						game_settings.frequency_of_bonus -= 3125;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == PROBABILITY_OF_BONUS)
			{
				lcd_locate(0,0);
				lcd_str("Szansa na bonus");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_int( 100/game_settings.probability_of_bonus );
				lcd_str(" %");
				if (PLUS_BUTTON)
				{
					if (game_settings.probability_of_bonus > 3)
					{
						game_settings.probability_of_bonus--;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.probability_of_bonus < 10)
					{
						game_settings.probability_of_bonus++;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == LEDMINUS_BONUS)
			{
				lcd_locate(0,0);
				lcd_str("Bonus odejmuj"_a"cy");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("Aktywny: ");
				lcd_str(game_settings.ledminus_bonus_enable == true ? "TAK" : "NIE");
				if (PLUS_BUTTON)
				{
					game_settings.ledminus_bonus_enable = true;
				}
				if (MINUS_BUTTON)
				{
					game_settings.ledminus_bonus_enable = false;
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == LEDPLUS_BONUS)
			{
				lcd_locate(0,0);
				lcd_str("Bonus dodaj"_a"cy");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("Aktywny: ");
				lcd_str(game_settings.ledplus_bonus_enable == true ? "TAK" : "NIE");
				if (PLUS_BUTTON)
				{
					game_settings.ledplus_bonus_enable = true;
				}
				if (MINUS_BUTTON)
				{
					game_settings.ledplus_bonus_enable = false;
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == RELAX_BONUS)
			{
				lcd_locate(0,0);
				lcd_str("Bonus relaksu");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("Aktywny: ");
				lcd_str(game_settings.relax_bonus_enable == true ? "TAK" : "NIE");
				if (PLUS_BUTTON)
				{
					game_settings.relax_bonus_enable = true;
				}
				if (MINUS_BUTTON)
				{
					game_settings.relax_bonus_enable = false;
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == SPEED_OF_AUTOCLICK)
			{
				lcd_locate(0,0);
				lcd_str("Szybko"_s _c" autoclk");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("co ");
				lcd_int(game_settings.speed_of_autoclick*4);
				lcd_str(" ms ");
				if (PLUS_BUTTON)
				{
					if (game_settings.speed_of_autoclick < 250)
					{
						game_settings.speed_of_autoclick += 5;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.speed_of_autoclick > 25)
					{
						game_settings.speed_of_autoclick -= 5;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == TIME_OF_AUTOCLICK)
			{
				lcd_locate(0,0);
				lcd_str("Czas autoclk");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_int(game_settings.time_of_autoclick*4);
				lcd_str(" ms ");
				if (PLUS_BUTTON)
				{
					if (game_settings.time_of_autoclick < 5000)
					{
						game_settings.time_of_autoclick += 25;
					}
				}
				if (MINUS_BUTTON)
				{
					if (game_settings.time_of_autoclick > 250)
					{
						game_settings.time_of_autoclick -=25;
					}
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			if (settings_menu_flag == LEDMINUS_AUTODISABLE)
			{
				lcd_locate(0,0);
				lcd_str("AutoOFF b.minus");
				lcd_locate(1,0);
				lcd_str("=== ");
				lcd_str("Aktywny: ");
				lcd_str(game_settings.ledminus_auto_disable == true ? "TAK" : "NIE");
				if (PLUS_BUTTON)
				{
					game_settings.ledminus_auto_disable = true;
				}
				if (MINUS_BUTTON)
				{
					game_settings.ledminus_auto_disable = false;
				}
				if (SELECT_BUTTON)
				{
					settings_menu_flag = NUMBER_OF_LEDS;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
		}
		
		if (main_menu_flag == INFO)
		{
			if (settings_menu_flag == MAIN_MENU)
			{
				lcd_locate(0,0);
				lcd_str("===INFORMACJE===");
				lcd_locate(1,0);
				lcd_str("================");
				if (SELECT_BUTTON)
				{
					settings_menu_flag++;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
			else
			{
				lcd_locate(0,0);
				lcd_str(":::LED::FIGHT:::");
				lcd_locate(1,0);
				lcd_str("Autor: A.Chorian");
				if (SELECT_BUTTON)
				{
					main_menu_flag = INFO;
					settings_menu_flag = MAIN_MENU;
					_delay_ms(DELAY_FOR_BUTTONS);
					lcd_cls();
				}
			}
		}
		if (main_menu_flag == RESET_SETTINGS)
		{
			lcd_locate(0,0);
			lcd_str("=== RESETUJ  ===");
			lcd_locate(1,0);
			lcd_str("===USTAWIENIA===");
			if (SELECT_BUTTON)
			{
				load_default_settings();
				save_current_settings();
				main_menu_flag = QUICK_GAME;
				_delay_ms(DELAY_FOR_BUTTONS);
				lcd_cls();
			}
		}
	}
	lcd_cls();
	lcd_locate(0,0);
	lcd_str("  Powodzenia !  ");
	init_data();
	init_timer0();
	init_timer1();
	init_timer2();
	
	LEDMINUS_BONUS_ON;
	LEDPLUS_BONUS_ON;
	RELAX_BONUS_ON;
	_delay_ms(1000);
	LEDMINUS_BONUS_OFF;
	_delay_ms(1000);
	RELAX_BONUS_OFF;
	_delay_ms(1000);
	LEDPLUS_BONUS_OFF;
	
	sei();
}

void check_end_of_battle ()
{
	if (game_settings.player1_wins == true || game_settings.player2_wins == true)
	{
		cli();
		button_parameters.button1_relax = false;
		button_parameters.button2_relax = false;
		lcd_cls();
		lcd_locate(0,0);
		lcd_str("   Zwyci"_e _z"y"_l":   ");
		lcd_locate(1,0);
		lcd_str(game_settings.player1_wins ? "    GRACZ 1 !   " : "    GRACZ 2 !   ");
		game_settings.player1_wins = false;
		game_settings.player2_wins = false;
		LEDMINUS_BONUS_OFF;
		LEDPLUS_BONUS_OFF;
		RELAX_BONUS_OFF;
		_delay_ms(2000);
		change_led_states(CLEAN);
		game_setup();
	}
}

ISR(ADC_vect)
{
	random_number =  (random_number<<1);
	random_number |= ADC & 1;
}



void button1_change_detect ()
{
	if(button_parameters.button1_state)//obsluga przejscia na 0
	{
		if(BTN1_0 && button_parameters.button1_to_check)
		{
			TIMER0_CLEAR;
			button_parameters.button1_to_check = check_1_to_0;
		}
	}

	if(!button_parameters.button1_state)//obsluga przejscia na 1
	{
		if(BTN1_1 && !button_parameters.button1_to_check)
		{
			TIMER0_CLEAR;
			button_parameters.button1_to_check = check_0_to_1;
		}
	}
}

void button1b_change_detect ()
{
	if ( LEDMINUS_BONUS_STATE && BTN1B_1 )
	{
		LEDMINUS_BONUS_OFF;
		change_led_states(RIGHT);
	}
	if ( LEDPLUS_BONUS_STATE && BTN1B_1 )
	{
		LEDPLUS_BONUS_OFF;
		if (!button_parameters.button1_relax)
		change_led_states(LEFT);
	}
	if ( RELAX_BONUS_STATE && BTN1B_1 )
	{
		RELAX_BONUS_OFF;
		button_parameters.button1_relax = 1;
	}
}

void button2_change_detect ()
{
	if(button_parameters.button2_state)//obsluga przejscia na 0
	{
		if(BTN2_0 && button_parameters.button2_to_check)
		{
			TIMER2_CLEAR;
			button_parameters.button2_to_check = check_1_to_0;
		}
	}

	if(!button_parameters.button2_state)//obsluga przejscia na 1
	{
		if(BTN2_1 && !button_parameters.button2_to_check)
		{
			TIMER2_CLEAR;
			button_parameters.button2_to_check = check_0_to_1;
		}
	}
}

void button2b_change_detect ()
{
	if ( LEDMINUS_BONUS_STATE && BTN2B_1 )
	{
		LEDMINUS_BONUS_OFF;
		change_led_states(LEFT);
	}
	if ( LEDPLUS_BONUS_STATE && BTN2B_1 )
	{
		LEDPLUS_BONUS_OFF;
		if (!button_parameters.button1_relax)
		change_led_states(RIGHT);
	}
	if ( RELAX_BONUS_STATE && BTN2B_1 )
	{
		RELAX_BONUS_OFF;
		button_parameters.button2_relax = 1;
	}
}
