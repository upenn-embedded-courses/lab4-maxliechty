/*
 * scoring.c
 *
 * Created: 06-Nov-21 21:16:08
 *  Author: maxwl
 */ 

#define F_CPU 16000000UL

#include <avr/wdt.h>
#include <util/delay.h>
#include "scoring.h"

#define soft_reset()

void scoring_init()
{
	DDRD |= (1 << DDD1);
	update_score(0, CPU);
	update_score(0, PLAYER);
}

void update_score(int score, int player)
{
	int x = 0;
	if (player == PLAYER)
	{
		x = LCD_WIDTH / 2 + 20;
	}
	else if (player == CPU)
	{
		x = LCD_WIDTH / 2 - 25;
	}
	
	if (score == 1)
	{
		LCD_drawString(x, 8, "01", WHITE, BLACK);
		LCD_drawString(x, 8, "01", WHITE, BLACK);
	}
	else if (score == 2)
	{
		LCD_drawString(x, 8, "02", WHITE, BLACK);
		LCD_drawString(x, 8, "02", WHITE, BLACK);
	}
	else if (score == 3)
	{
		LCD_drawString(x, 8, "03", WHITE, BLACK);
		LCD_drawString(x, 8, "03", WHITE, BLACK);
	}
	else if (score == 4)
	{
		LCD_drawString(x, 8, "04", WHITE, BLACK);
		LCD_drawString(x, 8, "04", WHITE, BLACK);
	}
	else if (score == 5)
	{
		LCD_drawString(x, 8, "05", WHITE, BLACK);
		LCD_drawString(x, 8, "05", WHITE, BLACK);
	}
	else if (score == 6)
	{
		LCD_drawString(x, 8, "06", WHITE, BLACK);
		LCD_drawString(x, 8, "06", WHITE, BLACK);
	}
	else if (score == 7)
	{
		LCD_drawString(x, 8, "07", WHITE, BLACK);
		LCD_drawString(x, 8, "07", WHITE, BLACK);
	}
	else if (score == 8)
	{
		LCD_drawString(x, 8, "08", WHITE, BLACK);
		LCD_drawString(x, 8, "08", WHITE, BLACK);
	}
	else if (score == 9)
	{
		LCD_drawString(x, 8, "09", WHITE, BLACK);
		LCD_drawString(x, 8, "09", WHITE, BLACK);
	}
	else if (score == 10)
	{
		LCD_drawString(x, 8, "10", WHITE, BLACK);
		LCD_drawString(x, 8, "10", WHITE, BLACK);
	}
	else if (score == 11)
	{
		LCD_drawString(x, 8, "11", WHITE, BLACK);
		LCD_drawString(x, 8, "11", WHITE, BLACK);
	}
	else
	{
		LCD_drawString(x, 8, "00", WHITE, BLACK);
		LCD_drawString(x, 8, "00", WHITE, BLACK);
	}
}

void winner(int player)
{
	if (player == PLAYER)
	{
		LCD_drawString(LCD_WIDTH / 2 - (13 * CHAR_WIDTH) / 2, LCD_HEIGHT / 2 - (CHAR_HEIGHT / 2), "PLAYER 1 WINS", BLACK, WHITE);
	}
	else if (player == CPU)
	{
		LCD_drawString(LCD_WIDTH / 2 - (13 * CHAR_WIDTH) / 2, LCD_HEIGHT / 2 - (CHAR_HEIGHT / 2), "COMPUTER WINS", BLACK, WHITE);
	}
	_delay_ms(1000);
	do
	{
		wdt_enable(WDTO_15MS);
		for(;;)
		{
		}
	} while (0);
}