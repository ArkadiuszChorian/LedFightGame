/*
 * definitons.h
 *
 *  Created on: 10-11-2014
 *      Author: Arek Chorian
 */

#ifndef DEFINITONS_H_
#define DEFINITONS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd44780.h"

//----------Sta³e-----------

//Flagi sprawdzenia stanu przycisku
#define check_0_to_1  1
#define check_1_to_0  0

//Prawda i fa³sz
#define true  1
#define false 0

//Flagi kierunku
#define RIGHT 1
#define LEFT 0
#define INIT 2
#define NO_SHIFT 2
#define CLEAN 3

//Domyœlne ustawienia gry
#define DEFAULT_frequency_of_bonus		62499
#define DEFAULT_ledminus_auto_disable	true
#define DEFAULT_ledminus_bonus_enable	true
#define DEFAULT_ledplus_bonus_enable	true
#define DEFAULT_number_of_leds			22
#define DEFAULT_probability_of_bonus	5
#define DEFAULT_relax_bonus_enable		true
#define DEFAULT_speed_of_autoclick		40
#define DEFAULT_threshold_of_change		1
#define DEFAULT_time_of_autoclick		1250
#define DEFAULT_player1_wins			false
#define DEFAULT_player2_wins			false
#define DEFAULT_shift_direction			NO_SHIFT

//OpóŸnienie przycisków w menu gry
#define DELAY_FOR_BUTTONS 200

//Polskie znaki
#define _a "\x80"
#define _c "\x81"
#define _e "\x82"
#define _l "\x83"
#define _n "\x84"
#define _o "\x85"
#define _s "\x86"
#define _z "\x87"

//----------Pod³¹czenie sygna³ów----------

//DS_LEDS
#define PIN_DS	 PB1
#define DDR_DS   DDRB
#define PORT_DS  PORTB

//SHCP_LEDS
#define PIN_SHCP	PC2
#define DDR_SHCP  	DDRC
#define PORT_SHCP 	PORTC

//STCP_LEDS
#define PIN_STCP 	PC1
#define DDR_STCP  	DDRC
#define PORT_STCP  	PORTC

//BUTTON_1
#define PIN_BTN1 	PD5
#define DDR_BTN1  	DDRD
#define PORT_BTN1  	PORTD
#define PINS_BTN1	PIND

//BUTTON_1_BONUS
#define PIN_BTN1B 	PD6
#define DDR_BTN1B   DDRD
#define PORT_BTN1B  PORTD
#define PINS_BTN1B	PIND

//BUTTON_2
#define PIN_BTN2 	PD7
#define DDR_BTN2  	DDRD
#define PORT_BTN2  	PORTD
#define PINS_BTN2 	PIND

//BUTTON_2_BONUS
#define PIN_BTN2B 	PB0
#define DDR_BTN2B  	DDRB
#define PORT_BTN2B  PORTB
#define PINS_BTN2B 	PINB

//BONUS LEDS
#define DDR_BONUS  	DDRC
#define PORT_BONUS  PORTC
#define PINS_BONUS 	PINC

//RED BONUS
#define PIN_REDB 	PC5

//GREEN BONUS
#define PIN_GRNB 	PC4

//BLUE BONUS
#define PIN_BLUB 	PC3

//----------Ustawianie stanu sygna³ów i rejestrów----------

//Dioda bonusowa
#define LEDMINUS_BONUS_OFF  PORT_BONUS |= (1<<PIN_REDB)
#define LEDMINUS_BONUS_ON   PORT_BONUS &= ~(1<<PIN_REDB)
#define LEDMINUS_BONUS_TOG  PORT_BONUS ^= (1<<PIN_REDB)
#define LEDPLUS_BONUS_OFF   PORT_BONUS |= (1<<PIN_GRNB)
#define LEDPLUS_BONUS_ON    PORT_BONUS &= ~(1<<PIN_GRNB)
#define LEDPLUS_BONUS_TOG   PORT_BONUS ^= (1<<PIN_GRNB)
#define RELAX_BONUS_OFF     PORT_BONUS |= (1<<PIN_BLUB)
#define RELAX_BONUS_ON      PORT_BONUS &= ~(1<<PIN_BLUB)
#define RELAX_BONUS_TOG     PORT_BONUS ^= (1<<PIN_BLUB)

//Odblokowanie i blokowanie przerwañ
#define ENABLE_PLAYER1_INTERRUPT     TIMSK |= (1<<TOIE0)
#define DISABLE_PLAYER1_INTERRUPT    TIMSK &= ~(1<<TOIE0)
#define ENABLE_PLAYER2_INTERRUPT     TIMSK |= (1<<OCIE2)
#define DISABLE_PLAYER2_INTERRUPT    TIMSK &= ~(1<<OCIE2)
#define ENABLE_LEDCHANGE_INTERRUPT   TIMSK |= (1<<OCIE1B)
#define DISABLE_LEDCHANGE_INTERRUPT  TIMSK &= ~(1<<OCIE1B)
#define ENABLE_BONUS_INTERRUPT		 TIMSK |= (1<<OCIE1A)
#define DISABLE_BONUS_INTERRUPT		 TIMSK &= ~(1<<OCIE1A)

//Uruchomienie i wy³¹czenie ADC
#define ENABLE_ADC					 ADCSRA |=  (1<<ADEN)
#define DISABLE_ADC					 ADCSRA &=  ~(1<<ADEN)

//Sygna³y rejestrów przesuwnych
#define DS_0	PORT_DS		|=  (1<<PIN_DS)
#define DS_1	PORT_DS		&= ~(1<<PIN_DS)
#define SHCP_0	PORT_SHCP	&= ~(1<<PIN_SHCP)
#define SHCP_1	PORT_SHCP	|=  (1<<PIN_SHCP)
#define STCP_0	PORT_STCP	&= ~(1<<PIN_STCP)
#define STCP_1	PORT_STCP	|=  (1<<PIN_STCP)

//----------Sprawdzenie stanu sygna³ów----------

//Stany diod bonusowych
#define LEDMINUS_BONUS_STATE (~PINS_BONUS & (1<<PIN_REDB))
#define LEDPLUS_BONUS_STATE  (~PINS_BONUS & (1<<PIN_GRNB))
#define RELAX_BONUS_STATE    (~PINS_BONUS & (1<<PIN_BLUB))

//Stany przycisków walki
#define BTN1_0 ( PINS_BTN1 & (1<<PIN_BTN1))
#define BTN1_1 (~PINS_BTN1 & (1<<PIN_BTN1))
#define BTN2_0 ( PINS_BTN2 & (1<<PIN_BTN2))
#define BTN2_1 (~PINS_BTN2 & (1<<PIN_BTN2))

//Stany przycisków bonusu
#define BTN1B_0 ( PINS_BTN1B & (1<<PIN_BTN1B))
#define BTN1B_1 (~PINS_BTN1B & (1<<PIN_BTN1B))
#define BTN2B_0 ( PINS_BTN2B & (1<<PIN_BTN2B))
#define BTN2B_1 (~PINS_BTN2B & (1<<PIN_BTN2B))

//----------Makra dodatkowe----------

//Liczba nieu¿ywanych pól
#define NUMBER_OF_EMPTY_BITS ((22-game_settings.number_of_leds)>>1)

//Sprawdzenie x bitu zmiennej stanu pola walki
#define CHECK_BIT(x) (led_states & (1UL<<x))

//Sprawdzenie czy któryœ z graczy zwyciê¿y³
#define CHECKIF_PLAYER1_WINS (led_states & (1UL<<((game_settings.number_of_leds + NUMBER_OF_EMPTY_BITS))))
#define CHECKIF_PLAYER2_WINS (~led_states & (1UL<<(NUMBER_OF_EMPTY_BITS)))

//Czyszczenie Timerów
#define TIMER0_CLEAR TCNT0 = 132
#define TIMER2_CLEAR TCNT2 = 0

//Nazwy przycisków w menu
#define SELECT_BUTTON	BTN1_1
#define RETURN_BUTTON	BTN1B_1
#define PLUS_BUTTON		BTN2_1
#define MINUS_BUTTON	BTN2B_1

//Typy danych

typedef uint8_t u08;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint8_t bool;

typedef struct
{
	bool button1_state:1;
	bool button2_state:1;
	bool button1_to_check:1;
	bool button2_to_check:1;
	bool button1_relax:1;
	bool button2_relax:1;
}button_struct;

typedef struct
{
	u08 number_of_leds:5;
	u08 threshold_of_change:2;
	u16 frequency_of_bonus:16;
	u08 probability_of_bonus:4;
	bool ledminus_bonus_enable:1;
	bool ledplus_bonus_enable:1;
	bool relax_bonus_enable:1;
	u08 speed_of_autoclick:8;
	u16 time_of_autoclick:13;
	bool ledminus_auto_disable:1;
	bool player1_wins:1;
	bool player2_wins:1;
	bool shift_direction:2;
}settings_struct;

enum menu_blocks
{
	QUICK_GAME = 1,
	SETTINGS,
	INFO,
	RESET_SETTINGS
};

enum menu_blocks2
{
	MAIN_MENU = 0,
	NUMBER_OF_LEDS,
	THRESHOLD_OF_CHANGE,
	FREQUENCY_OF_BONUS,
	PROBABILITY_OF_BONUS,
	LEDMINUS_BONUS,
	LEDPLUS_BONUS,
	RELAX_BONUS,
	SPEED_OF_AUTOCLICK,
	TIME_OF_AUTOCLICK,
	LEDMINUS_AUTODISABLE
};

//Bie¿¹ce ustawienia gry
volatile settings_struct game_settings;

#endif /* DEFINITONS_H_ */
