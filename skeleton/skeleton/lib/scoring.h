/*
 * scoring.h
 *
 * Created: 06-Nov-21 21:16:16
 *  Author: maxwl
 */ 

#include "LCD_GFX.h"
#include "ST7735.h"
#include "ball.h"

#ifndef SCORING_H_
#define SCORING_H_

#define CHAR_HEIGHT 8
#define CHAR_WIDTH 5

void scoring_init();
void update_score(int score, int player);
void winner(int player);
// void player1_wins();
// void player2_wins();



#endif /* SCORING_H_ */