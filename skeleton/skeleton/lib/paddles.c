/*
 * paddles.c
 *
 * Created: 06-Nov-21 16:05:18
 *  Author: maxwl
 */ 
#include "paddles.h"
#include "ball.h"

volatile int y = LCD_HEIGHT / 2 - paddle_height / 2;
volatile int cpu_y = 0;
volatile int control;

void joystick_init()
{
	PRR &= ~(1 << PRADC);
	
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
	
	ADMUX &= ~(1 << MUX0);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX3);
	
	ADCSRA |= (1 << ADATE);
	ADCSRB &= ~(1 << ADTS0);
	ADCSRB &= ~(1 << ADTS1);
	ADCSRB &= ~(1 << ADTS2);
	
	DIDR0 |= (1 << ADC0D);
	
	ADCSRA |= (1 << ADEN);
	
	ADCSRA |= (1 << ADSC);
	
	control = JOYSTICK;
}

void nodeMCU_init()
{
	DDRD &= ~(1 << DDD2); // UP
	DDRD &= ~(1 << DDD5); // DOWN
	DDRD &= ~(1 << DDD7); // SELECT
	
	control = NODE;
}

int get_speed(int ADC_value)
{
	int speed;
	if (ADC_value >= 490 && ADC_value <= 530)
	{
		speed = 0;
	}
	else if (ADC_value <= 921)
	{
		if (ADC_value <= 819)
		{
			if (ADC_value <= 717)
			{
				if (ADC_value <= 615)
				{
					if (ADC_value <= 513)
					{
						if (ADC_value <= 411)
						{
							if (ADC_value <= 309)
							{
								if (ADC_value <= 207)
								{
									if (ADC_value <= 105)
									{
										speed = VERY_FAST;
									}
									else
									{
										speed = FAST;
									}
								}
								else
								{
									speed = MEDIUM_FAST;
								}
							}
							else
							{
								speed = MEDIUM_SLOW;
							}
						}
						else
						{
							speed = SLOW;
						}
					}
					else
					{
						speed = -SLOW;
					}
				}
				else
				{
					speed = -MEDIUM_SLOW;
				}
			}
			else
			{
				speed = -MEDIUM_FAST;
			}
		}
		else
		{
			speed = -FAST;
		}
	}
	else
	{
		speed = -VERY_FAST;
	}
	return speed;
}

void update_paddle(int ADC_value)
{
	int move = 0;
	if (control == JOYSTICK)
	{
		move = get_speed(ADC_value);
	}
	else if (control == NODE)
	{
		if(!(PIND & (1 << PIND2)))
		{
			move = FAST;
		}
		else if(!(PIND & (1 << PIND5)))
		{
			move = -FAST;
		}
		else
		{
			move = 0;
		}
	}
				
	if (move != 0)
	{
		LCD_drawBlock(LCD_WIDTH - paddle_width - 1, y, LCD_WIDTH - 1, (y + paddle_height), BLACK);
	}
	else
	{
		LCD_drawBlock(LCD_WIDTH - paddle_width - 1, y, LCD_WIDTH - 1, (y + paddle_height), WHITE);
	}
				
	y += move;

	if (y > BOTTOM)
	{
		y = BOTTOM;
	}
	else if (y < TOP)
	{
		y = TOP;
	}
	LCD_drawBlock(LCD_WIDTH - paddle_width - 1, y, LCD_WIDTH - 1, (y + paddle_height), WHITE);
}

void update_cpu_paddle(int mode)
{
	int cpu_move = 0;
	int ball_position = ball_position_y();
	
	LCD_drawBlock(0, cpu_y, paddle_width, cpu_y + paddle_height, BLACK);
	
	if (ball_position > cpu_y + paddle_height / 2)
	{
		if (ball_position > cpu_y + paddle_height)
		{
			cpu_move = mode;
		}
		else
		{
			cpu_move = SLOW;
		}
	}
	else if (ball_position < cpu_y + paddle_height / 2)
	{
		if (ball_position < cpu_y)
		{
			cpu_move = -mode;
		}
		else
		{
			cpu_move = -SLOW;
		}
	}
	else
	{
		cpu_move = 0;
	}
	cpu_y += cpu_move;
	if (cpu_y > BOTTOM)
	{
		cpu_y = BOTTOM;
	}
	else if (cpu_y < TOP)
	{
		cpu_y = TOP;
	}
	LCD_drawBlock(0, cpu_y, paddle_width, cpu_y + paddle_height, WHITE);
}

int get_paddle_position()
{
	return y;
}

int get_cpu_paddle_position()
{
	return cpu_y;
}