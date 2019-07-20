/*
 * ltdc.h
 *
 *  Created on: 18.07.2019
 *      Author: rafal
 */

#ifndef LTDC_H_
#define LTDC_H_

#include "stm32f4xx.h"
#include "ili9341.h"



#define LCD_HSYNC	10
#define LCD_HFP 	10		// Horizontal front porch
#define	LCD_HBP		20		// Horizontal back porch
#define LCD_VSYNC	2
#define LCD_VFP 	2		// Vertical front porch
#define	LCD_VBP	 	2		// Vertical back porch
#define LCD_WIDTH	240
#define LCD_HEIGHT	320
#define LCD_PIXELS	LCD_WIDTH*LCD_HEIGHT




void LCD_LtdcInit(uint16_t *layer1_adds);


#endif /* LTDC_H_ */
