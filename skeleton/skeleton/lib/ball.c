/*
 * ball.c
 *
 * Created: 13-Nov-21 17:03:59
 *  Author: maxwl
 */ 
#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "paddles.h"
#include "buzzer.h"

volatile int ball_y = LCD_HEIGHT/2 - 1;
volatile int ball_x = LCD_WIDTH/2 - 1;
volatile int trajectory_x[LCD_WIDTH] = {0};
volatile int trajectory_y[LCD_HEIGHT] = {0};
volatile int pos = 0;
int x_pos[LCD_WIDTH];
int y_pos[LCD_HEIGHT];
volatile int ball_speed_x = 0;
volatile int ball_speed_y = 0;
volatile int paddle_top;
volatile int paddle_bottom;
volatile int cpu_paddle_top;
volatile int cpu_paddle_bottom;
volatile int skip = 0;
volatile int player_score = 0;
volatile int cpu_score = 0;
volatile int score_update = 2;

void ball_init()
{
	srand(time(NULL));
	LCD_drawBlock(ball_x, ball_y, ball_x + RADIUS, ball_y + RADIUS, WHITE);
	launch_ball();
}

void launch_ball()
{
	LCD_drawBlock(ball_x, ball_y, ball_x + RADIUS, ball_y + RADIUS, BLACK);
	do {
		ball_speed_x = (rand() % 12) - 6;
	} while (ball_speed_x == 0);
	ball_speed_y = (rand() % 12) - 6;
	
	update_ball();
}

void update_ball()
{
	LCD_drawBlock(ball_x + RADIUS - ball_speed_x, ball_y + RADIUS - ball_speed_y, ball_x - ball_speed_x, ball_y - ball_speed_y, BLACK);
	if (score_update == PLAYER)
	{
		update_score(player_score, PLAYER);
	}
	else if (score_update == CPU)
	{
		update_score(cpu_score, CPU);
	}
	score_update = 2;
	
	if (ball_x >= LCD_WIDTH - 1 - paddle_width - RADIUS - abs(ball_speed_x) && ball_speed_x > 0)
	{
		int temp_x1 = ball_x;
		ball_x = LCD_WIDTH - 1 - paddle_width - RADIUS - 1;
		ball_y += abs(ball_x - temp_x1) * ball_speed_y;
		ball_speed_x = (rand() % 6) + 1;
		ball_speed_x = -ball_speed_x;
		
		paddle_top = get_paddle_position();
		paddle_bottom = paddle_top + paddle_height;
		
		if(ball_y + RADIUS >= paddle_top && ball_y - RADIUS <= paddle_bottom)
		{
			noteHigh();
			update_speed(paddle_top, paddle_bottom, RIGHT);		
		}
		else
		{
			int temp_x = LCD_WIDTH - 1 - RADIUS;
			int temp_y = ball_y;
			LCD_drawBlock(temp_x, temp_y, temp_x + RADIUS, temp_y + RADIUS, WHITE);
			_delay_ms(10);
			LCD_drawBlock(temp_x, temp_y, temp_x + RADIUS, temp_y + RADIUS, BLACK);
			PORTD |= (1 << DDD1);
			score(CPU);
			PORTD &= ~(1 << DDD1);
		}
	}
	else if (ball_x <= paddle_width + abs(ball_speed_x) && ball_speed_x < 0)
	{
		int temp_x2 = ball_x;
		ball_x = paddle_width + 1;
		ball_y += abs(ball_x - temp_x2) * ball_speed_y;
		ball_speed_x = (rand() % 6) + 1;
		
		cpu_paddle_top = get_cpu_paddle_position();
		cpu_paddle_bottom = cpu_paddle_top + paddle_height;
		
		if(ball_y + RADIUS >= cpu_paddle_top && ball_y - RADIUS <= cpu_paddle_bottom)
		{
			noteHigh();
			update_speed(cpu_paddle_top, cpu_paddle_bottom, LEFT);
		}
		else
		{
			int temp_x = 0;
			int temp_y = ball_y;
			LCD_drawBlock(temp_x, temp_y, temp_x + RADIUS, temp_y + RADIUS, WHITE);
			_delay_ms(10);
			LCD_drawBlock(temp_x, temp_y, temp_x + RADIUS, temp_y + RADIUS, BLACK);
			PORTD |= (1 << DDD1);
			score(PLAYER);
			PORTD &= ~(1 << DDD1);
		}
	}
	
	if (ball_y <= 8 + CHAR_HEIGHT - 1 && ball_y >= 8 - (RADIUS - 1))
	{
		if (ball_x >= LCD_WIDTH / 2 + 20 - (RADIUS - 1) && ball_x <= LCD_WIDTH / 2 + 20 + (CHAR_WIDTH * 2) - 1)
		{
			score_update = PLAYER;
		}
		else if (ball_x >= LCD_WIDTH / 2 - 25 - (RADIUS - 1) && ball_x <= LCD_WIDTH / 2 - 25 + (CHAR_WIDTH * 2) - 1)
		{
			score_update = CPU;
		}
	}
	
	if (ball_y <= 0 + RADIUS + abs(ball_speed_y) || ball_y >= LCD_HEIGHT - RADIUS - abs(ball_speed_y))
	{
		noteHigh();
		ball_speed_y = -ball_speed_y;
	}
	
	LCD_drawBlock(ball_x, ball_y, ball_x + RADIUS, ball_y + RADIUS, WHITE);
 	if (skip == 1)
 	{
 		_delay_ms(500);
 		LCD_drawBlock(ball_x, ball_y, ball_x + RADIUS, ball_y + RADIUS, BLACK);
	}

	ball_x += ball_speed_x;
	if (ball_x < 0)
	{
		ball_x = 0;
	}
	else if (ball_x > LCD_WIDTH - RADIUS - 1)
	{
		ball_x = LCD_WIDTH - RADIUS - 1;
	}
	ball_y += ball_speed_y;
	if (ball_y < 0)
	{
		ball_y = 0;
	}
	else if (ball_y > LCD_HEIGHT - RADIUS - 1)
	{
		ball_y = LCD_HEIGHT - RADIUS - 1;
	}
	skip = 0;
}

void score(int scorer)
{
	noteLow();
	skip = 1;
	ball_x = LCD_WIDTH/2 - 1;
	ball_y = LCD_HEIGHT/2 - 1;
	if (scorer == PLAYER)
	{
		player_score++;
		update_score(player_score, PLAYER);
		if (player_score == 11)
		{
			winner(PLAYER);
		}
	}
	else if (scorer == CPU)
	{
		cpu_score++;
		update_score(cpu_score, CPU);
		if (cpu_score == 11)
		{
			winner(CPU);
		}
	}
	launch_ball();
}

void update_speed(int paddle_pos_top, int paddle_pos_bottom, int direction)
{
	if (ball_y <= paddle_pos_top)
	{
		ball_speed_y = direction * (ball_speed_x * 3);
	}
	else if (ball_y >= paddle_pos_bottom)
	{
		ball_speed_y = direction * (-ball_speed_x * 3);
	}
	else if (ball_y > paddle_pos_top && ball_y < paddle_pos_top + paddle_height / 3)
	{
		ball_speed_y = direction * (ball_speed_x * 2);
	}
	else if (ball_y < paddle_pos_bottom && ball_y > paddle_pos_bottom - paddle_height / 3)
	{
		ball_speed_y = direction * (-ball_speed_x * 2);
	}
	else if (ball_y > paddle_pos_top + paddle_height / 3 && ball_y < paddle_pos_top + paddle_height / 2)
	{
		ball_speed_y = direction * (ball_speed_x);
	}
	else if (ball_y < paddle_pos_bottom - paddle_height / 3 && ball_y > paddle_pos_bottom - paddle_height / 2)
	{
		ball_speed_y = direction * (-ball_speed_x);
	}
	else if (ball_y == paddle_pos_top - paddle_height / 2)
	{
		ball_speed_y = 0;
	}
}

int ball_position_x()
{
	return ball_x;
}

int ball_position_y()
{
	return ball_y;
}