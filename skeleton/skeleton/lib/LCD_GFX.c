/*
 * LCD_GFX.c
 *
 * Created: 9/20/2021 6:54:25 PM
 *  Author: You
 */

#include <stdlib.h>
#include "LCD_GFX.h"
#include "ST7735.h"

const int x_center = LCD_WIDTH/2;
const int y_center = LCD_HEIGHT/2;

/******************************************************************************
* Local Functions
******************************************************************************/



/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
}

/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if ((pixels>>j)&(1==1)){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/


/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color)
{
	int x = radius;
	int y = 0;
 	
	int RE = 1 - radius;
	while (x > y)
	{
		if (RE <= 0)
		{
			RE = RE + 2*y + 1;
		}
		else
		{
			x--;
			RE = RE + 2*y - 2*x + 1;
		}  
		for (int i = y + y0; i >= y0; i--)
		{
			LCD_drawPixel(x + x0, i, color); //oct1
			LCD_drawPixel(-x + x0, i, color); //oct4
		}
 		for (int j = -y + y0; j < y0; j++)
 		{
 			LCD_drawPixel(x + x0, j, color); //oct8
 			LCD_drawPixel(-x + x0, j, color); //oct5
 		}
		for (int k = x + y0; k >= y0; k--)
		{
 			LCD_drawPixel(y + x0, k, color); //oct2
 			LCD_drawPixel(-y + x0, k, color); //oct3
 		}
		for (int m = -x + y0; m < y0; m++)
 		{
 			LCD_drawPixel(y + x0, m, color); //oct7
 			LCD_drawPixel(-y + x0, m, color); //oct6
 		}
		y++;
	}
}

/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/

void LCD_drawLine(short x0, short y0, short x1, short y1, uint16_t c)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	int yi = 1;
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
		{
			if (dy > 0)
			{
				yi = -yi;
				dy = -dy;
			}
			int D = (2 * dy) - dx;
			int y = y0;
			
			for (int i = x0; i > x1; i--)
			{
				LCD_drawPixel(i, y, c);
				
				if (D > 0)
				{
					y -= yi;
					D -= (2 * (dy - dx));
				}
				else
				{
					D -= 2 * dy;
				}
			}
		}
		else
		{
			if (dy < 0)
			{
				yi = -yi;
				dy = -dy;
			}
			int D = (2 * dy) - dx;
			int y = y0;
				
			for (int i = x0; i < x1; i++)
			{
				LCD_drawPixel(i, y, c);
					
				if (D > 0)
				{
					y += yi;
					D += (2 * (dy - dx));
				}
				else
				{
					D += 2 * dy;
				}
			}
		}
	}
	else
	{
		if (y0 > y1)
		{
			if (dx > 0)
			{
				xi = -xi;
				dx = -dx;
			}
			int D = (2 * dx) - dy;
			int x = x0;
			
			for (int j = y0; j > y1; j--)
			{
				LCD_drawPixel(x, j, c);
				if (D > 0)
				{
					x -= xi;
					D -= (2 * (dx - dy));
				}
				else
				{
					D -= 2 * dx;
				}
			}
		}
		else
		{
			if (dx < 0)
			{
				xi = -xi;
				dx = -dx;
			}
			int D = (2 * dx) - dy;
			int x = x0;
			
			for (int j = y0; j < y1; j++)
			{
				LCD_drawPixel(x, j, c);
				if (D > 0)
				{
					x += xi;
					D += (2 * (dx - dy));
				}
				else
				{
					D += 2 * dx;
				}
			}
		}
	}
}

/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
{
	if (x0 > x1)
	{
		if (y0 > y1)
		{
			for (int i = y0; i >= y1; i--)
			{
				for (int j = x0; j >= x1; j--)
				{
					LCD_drawPixel(j, i, color);
				}
			}
		}
		else
		{
			for (int i = y0; i <= y1; i++)
			{
				for (int j = x0; j >= x1; j--)
				{
					LCD_drawPixel(j, i, color);
				}
			}
		}
	}
	else if (y0 > y1)
	{
		for (int i = y0; i >= y1; i--)
		{
			for (int j = x0; j <= x1; j++)
			{
				LCD_drawPixel(j, i, color);
			}
		}
	}
	else
	{
		for (int i = y0; i <= y1; i++)
		{
			for (int j = x0; j <= x1; j++)
			{
				LCD_drawPixel(j, i, color);
			}
		}
	}
}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color) 
{
	for (int i = 0; i < LCD_WIDTH; i++)
	{
		for (int j = 0; j < LCD_HEIGHT; j++)
		{
			LCD_drawPixel(i, j, color);
		}
	}
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
{
	int x0 = x;
	for (int i = 0; str[i] != NULL; i++)
	{
		if (str[i] == '\n')
		{
			y += 8;
			x = x0;
		}
		else if (str[i] == '\t')
		{
			x += 5;
		}
		else
		{
			LCD_drawChar(x, y, str[i], fg, bg);
			x += 5;
		}
	}
}