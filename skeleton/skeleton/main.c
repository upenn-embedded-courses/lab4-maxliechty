/*
 * skeleton.c
 *
 * Created: 22-Oct-21 09:18:05
 * Author : maxwl
 */ 

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include "lib\ST7735.h"
#include "lib\LCD_GFX.h"
#include "lib\paddles.h"
#include "lib\scoring.h"
#include "lib\buzzer.h"
#include "lib\ball.h"

const uint16_t bkg = BLACK;
volatile int mode;

void pick_mode_joystick()
{	
	DDRD &= ~(1 << DDD4);
	PORTD |= (1 << DDD4);
	
	LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", BLACK, WHITE);
	LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", WHITE, BLACK);
	while(1)
	{
		if (ADC >= 530)
		{
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", WHITE, BLACK);
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", BLACK, WHITE);
			mode = MEDIUM_FAST;
		}
		else if (ADC <= 490)
		{
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", WHITE, BLACK);
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", BLACK, WHITE);
			mode = FAST;
		}
		else
		{
			mode = MEDIUM_FAST;
		}

		if (!(PIND & (1 << PIND4)))
		{
			noteHigh();
			LCD_drawBlock(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, LCD_WIDTH / 2 + 20, LCD_HEIGHT / 2 + 16, BLACK);
			break;
		}
	}	
}

void pick_mode_blynk()
{
	LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", BLACK, WHITE);
	LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", WHITE, BLACK);
	while(1)
	{
		if(!(PIND & (1 << PIND5)))
		{
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", WHITE, BLACK);
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", BLACK, WHITE);
			mode = MEDIUM_FAST;
		}
		else if(!(PIND & (1 << PIND2)))
		{
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, "EASY", WHITE, BLACK);
			LCD_drawString(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 + 8, "HARD", BLACK, WHITE);
			mode = FAST;
		}
		else
		{
			mode = MEDIUM_FAST;
		}

		if (!(PIND & (1 << PIND7)))
		{
			noteHigh();
			LCD_drawBlock(LCD_WIDTH / 2 - 10, LCD_HEIGHT / 2 - 8, LCD_WIDTH / 2 + 20, LCD_HEIGHT / 2 + 16, BLACK);
			break;
		}
	}
}

void repair_background()
{
	for(int i = 0; i < LCD_HEIGHT; i += 3)
	{
		LCD_drawPixel(LCD_WIDTH / 2, i, WHITE);
	}
}

void Initialize()
{
	DDRB &= ~(1 << DDB4);

	lcd_init();
	if (PINB & (1 << PINB4))
	{
		nodeMCU_init();
	}
	else
	{
		joystick_init();
	}
	LCD_setScreen(bkg);
	buzzer_init();
	if (PINB & (1 << PINB4))
	{
		pick_mode_blynk();
	}
	else
	{
		pick_mode_joystick();		
	}
	scoring_init();
	ball_init();
}

int main(void)
{
	Initialize();
	while (1)
	{
		update_paddle(ADC);
		update_cpu_paddle(mode);
		update_ball();
/*		update_score();*/
		repair_background();
// 		if (get_cpu_paddle_position() == BOTTOM || get_paddle_position() == BOTTOM || get_cpu_paddle_position() == TOP || get_paddle_position() == TOP)
// 		{
// 			/*noteLow();*/
// 		}
// 		LCD_drawLine(LCD_WIDTH / 2, LCD_HEIGHT / 2, LCD_WIDTH / 3, 0, RED);
// 		LCD_drawLine(LCD_WIDTH / 2, LCD_HEIGHT / 2, 0, LCD_HEIGHT / 3, WHITE);
// 		LCD_drawLine(LCD_WIDTH / 2, LCD_HEIGHT / 2, LCD_WIDTH - LCD_WIDTH / 3, 0, BLUE);
// 		LCD_drawLine(LCD_WIDTH / 2, LCD_HEIGHT / 2, LCD_WIDTH, LCD_HEIGHT / 3, YELLOW);
	}
}