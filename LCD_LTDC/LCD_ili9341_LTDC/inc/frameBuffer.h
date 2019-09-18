/*
 * frameBuffer.h
 *
 *  Created on: 19.08.2019
 *      Author: rafal
 */

#ifndef INC_FRAMEBUFFER_H_
#define INC_FRAMEBUFFER_H_

#include "../inc/fonts.h"
#include "../inc/ltdc.h"
#include "stm32f429xx.h"
#include "stdlib.h"

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} ColorRGB565;


void frameBuffer_drawCircle(uint16_t *buffer, uint16_t x, uint16_t y, uint16_t radius, ColorRGB565 *color);
void frameBuffer_drawLine(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color);
void frameBuffer_putString(uint16_t *buffer, char *str, fontType_t *font, uint16_t x, uint16_t y, ColorRGB565 *color);
void __frameBuffer_putChar(uint16_t *buffer, char c, fontType_t *font, uint16_t x, uint16_t y, ColorRGB565 *color);
void __frameBuffer_drawPixel(uint16_t *buffer, int16_t x, uint16_t y, ColorRGB565 *color);
void __frameBuffer_drawLineLow(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color);
void __frameBuffer_drawLineHigh(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color);

void frameBufferDMA2D_initalize(void);
void frameBufferDMA2D_fillRect(uint16_t *buffer, uint16_t x, uint16_t y, uint16_t a, uint16_t b, ColorRGB565 *color);

#endif /* INC_FRAMEBUFFER_H_ */
