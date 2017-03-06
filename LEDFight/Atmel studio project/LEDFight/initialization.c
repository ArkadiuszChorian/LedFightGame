/*
 * initialization.c
 *
 * Created: 2015-01-06 01:29:38
 *  Author: Arek Chorian
 */ 

#include "initialization.h"

u08 polish_characters[8][8] EEMEM = {   {0,0,14,1,15,17,15,2},            // ¹
										{2,4,14,16,16,17,14,0},           // æ
										{0,0,14,17,31,16,14,2},           // ê
										{12,4,6,4,12,4,14,0},             // ³
										{2,4,22,25,17,17,17,0},           // ñ
										{2,4,14,17,17,17,14,0},           // ó
										{2,4,14,16,14,1,30,0},            // œ
										{4,0,31,2,4,8,31,0}      };		  // ¿											
	
void init_io ()
{
	PORT_BTN1 |= (1<<PIN_BTN1);
	PORT_BTN2 |= (1<<PIN_BTN2);
	
	PORT_BTN1B |= (1<<PIN_BTN1B);
	PORT_BTN2B |= (1<<PIN_BTN2B);
	
	DDR_DS   |= (1<<PIN_DS);
	DDR_SHCP |= (1<<PIN_SHCP);
	DDR_STCP |= (1<<PIN_STCP);
	
	DDR_BONUS |= (1<<PIN_REDB)|(1<<PIN_GRNB)|(1<<PIN_BLUB);
}

void init_timer0 ()
{
	TCCR0 |= (1<<CS02); //Preskaler 256
	TCNT0 = TIMER0_CLEAR; //Liczy od 132 co 4ms
}

void init_timer1 ()
{
	TCCR1B |= (1<<WGM12);
	TCCR1B |= (1<<CS12);
	//OCR1A   = 249; //co 8ms
	//OCR1A   = 30; //co 1ms
	//OCR1A   = 62499; //co 2 sec
	//OCR1A   = 31249; //co 1 sec
	//OCR1B   = 31249;
	OCR1B   = 30;
	//OCR1A   = FREQUENCY_OF_BONUS;
	OCR1A = game_settings.frequency_of_bonus;
	//OCR1A   = 3124; //co 100ms
	//OCR1A   = 5;
}

void init_timer2 ()
{
	TCCR2 |= (1<<WGM21); //Tryb CTC
	TCCR2 |= (1<<CS22)|(1<<CS21); //Preskaler 256
	OCR2   = 124; //Rejestr do porownania co 4 ms
}

void init_adc ()
{
	//funkcja inicjuje ADC w tryb Free Running,
	//wywo³uj¹c jednoczeœnie pierwszy pomiar

	//ustawiamy rejestr ADMUX
	//wybierz kana³ pomiarowy nr 0 czyli pin PC0, MUX3:0=0
	//wyrównaj wynik pomiaru do prawej, ADLAR=0
	//napiêcie odniesienia AVcc z kondensatorem na AREF
	//je¿eli nie wykorzystujesz ADC do innych celów, to mo¿esz
	//nie dodawaæ kondensatora
	ADMUX  = (1<<REFS0);

	//ustawiamy rejestr ADCSRA
	//ADCSRA  |=  (1<<ADPS0); //preskaler 2, pomiar co 3,25 us, pelna liczba po 29 us
	//ADCSRA  |=  (1<<ADPS1)|(1<<ADPS0); //ustaw preskaler ADC na 8
	ADCSRA  |=  (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ustaw preskaler ADC na 128, pelna liczba losowa co 1,664 ms
	//ADCSRA  |=  (1<<ADPS2)|(1<<ADPS1); //ustaw preskaler ADC na 64, pelna liczba losowa co 0,832 ms
	ADCSRA  |=  (1<<ADEN); //w³¹cz ADC
	ADCSRA  |=  (1<<ADFR); //w³¹cz tryb FREE RUNNING
	ADCSRA  |=  (1<<ADIE); //w³¹cz przerwania z ADC
	ADCSRA  |= (1<<ADSC);  //rozpocznij pierwszy pomiar ADC
}

void init_data ()
{
	led_states = 0b10101010101010101010110101010101;
	change_led_states(INIT);
	LEDMINUS_BONUS_OFF;
	LEDPLUS_BONUS_OFF;
	RELAX_BONUS_OFF;
	button_parameters.button1_state = 0;
	button_parameters.button1_to_check = check_1_to_0;
	button_parameters.button2_state = 0;
	button_parameters.button2_to_check = check_1_to_0;
	player1_click_count = 0;
	player2_click_count = 0;
}

void program_polish_characters ()
{
	register u08 adress = 0x80;
	for (int i = 0; i < 8; i++)
	{
		lcd_defchar_E(adress++,polish_characters[i]);
	}
	
	lcd_locate(0,0);
}