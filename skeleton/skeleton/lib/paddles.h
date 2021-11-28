/*
 * paddles.h
 *
 * Created: 06-Nov-21 16:05:29
 *  Author: maxwl
 */ 
#include <stdlib.h>

#include "LCD_GFX.h"
#include "ST7735.h"

#ifndef PADDLES_H_
#define PADDLES_H_

#define ADC_MAX	1023
#define ADC_MIN 0

#define paddle_width  1
#define paddle_height  15

#define SLOW			1
#define MEDIUM_SLOW		2
#define MEDIUM_FAST		4
#define FAST			8
#define VERY_FAST		16

#define TOP		0
#define BOTTOM	(LCD_HEIGHT - paddle_height - 1)

#define JOYSTICK	0
#define	NODE		1

void joystick_init();
void nodeMCU_init();
void update_paddle(int ADC_value);
void update_cpu_paddle(int mode);
int get_speed(int ADC_value);
int get_paddle_position();
int get_cpu_paddle_position();

#endif /* PADDLES_H_ */