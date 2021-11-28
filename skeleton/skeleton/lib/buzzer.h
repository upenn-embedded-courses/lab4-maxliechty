/*
 * buzzer.h
 *
 * Created: 13-Nov-21 11:51:00
 *  Author: maxwl
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "scoring.h"

#ifndef BUZZER_H_
#define BUZZER_H_

#define HIGH_NOTE 240
#define LOW_NOTE 240

void buzzer_init();
void start_sound();
void noteLow();
void noteHigh();
void off();

#endif /* BUZZER_H_ */