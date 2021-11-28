/*
 * buzzer.c
 *
 * Created: 13-Nov-21 11:51:11
 *  Author: maxwl
 */ 

#include "buzzer.h"

void buzzer_init()
{
	DDRD |= (1 << DDD3);
	
	TCCR2B |= (1 << CS20);
	TCCR2B |= (1 << CS21);
	TCCR2B &= ~(1 << CS22);

	TCCR2A |= (1 << WGM20);
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << WGM22);

	TCCR2A |= (1 << COM2A0);
	TCCR2A &= ~(1 << COM0A1);
	OCR2A = 0;
	
	TCCR2A &= ~(1 << COM2B0);
	TCCR2A |= (1 << COM2B1);
	OCR2B = (float)OCR2A / 20;
	
	start_sound();
}

void start_sound()
{
	noteHigh();
	off();
	_delay_ms(100);
	noteHigh();
	off();
}

void noteLow()
{
	OCR2A = LOW_NOTE;
	OCR2B = (float)OCR2A / 20;
	_delay_ms(100);
	off();
}

void noteHigh()
{
	OCR2A = HIGH_NOTE;
	OCR2B = (float)OCR2A / 20;
	_delay_ms(10);
	off();
}

void off()
{
	OCR2A = 0;
	OCR2B = 0;
}