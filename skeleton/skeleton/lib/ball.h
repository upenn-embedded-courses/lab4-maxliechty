/*
 * ball.h
 *
 * Created: 13-Nov-21 17:04:09
 *  Author: maxwl
 */ 
#include "LCD_GFX.h"
#include "ST7735.h"

#ifndef BALL_H_
#define BALL_H_

#define RADIUS	2

#define PLAYER	1
#define CPU		0

#define LEFT	-1
#define RIGHT	1

void ball_init();
void launch_ball();
void update_ball();
void update_speed(int paddle_pos_top, int paddle_pos_bottom, int direction);
void score(int scorer);
int ball_position_x();
int ball_position_y();

#endif /* BALL_H_ */