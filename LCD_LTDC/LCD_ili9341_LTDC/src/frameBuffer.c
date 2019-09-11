/*
 * frameBuffer.c
 *
 *  Created on: 19.08.2019
 *      Author: rafal
 */

#include "../LCD_ili9341_LTDC/inc/frameBuffer.h"



void frameBuffer_drawCircle(uint16_t *buffer, uint16_t x, uint16_t y, uint16_t radius, ColorRGB565 *color){
	/*
	 * 		Midpoint circle algorithm
	 */
	int RE = 0;
	int xr = radius;
	int yr = 0;
	int Xchange = 1 - (radius << 1);
	int Ychange = 1;

	do{
		__frameBuffer_drawPixel(buffer,x+xr,y+yr,color);
		__frameBuffer_drawPixel(buffer,x-xr,y-yr,color);
		__frameBuffer_drawPixel(buffer,x-xr,y+yr,color);
		__frameBuffer_drawPixel(buffer,x+xr,y-yr,color);
		__frameBuffer_drawPixel(buffer,x+yr,y+xr,color);
		__frameBuffer_drawPixel(buffer,x-yr,y-xr,color);
		__frameBuffer_drawPixel(buffer,x-yr,y+xr,color);
		__frameBuffer_drawPixel(buffer,x+yr,y-xr,color);
		yr++;
		RE += Ychange;
		Ychange += 2;

		if((RE << 1) + Xchange > 0){
			xr--;
			RE += Xchange;
			Xchange += 2;
		}
	}while(xr >= yr);

	/*
	 * 	Rectangle - CIRCLE
	int RE = 0;
	int xr = radius;
	int yr = 0;
	int Xchange = 1 - (radius << 2);
	int Ychange = 1;

	do{
		__frameBuffer_drawPixel(buffer,x+xr,y+yr,color);
		__frameBuffer_drawPixel(buffer,x-xr,y-yr,color);
		__frameBuffer_drawPixel(buffer,x-xr,y+yr,color);
		__frameBuffer_drawPixel(buffer,x+xr,y-yr,color);
		__frameBuffer_drawPixel(buffer,x+yr,y+xr,color);
		__frameBuffer_drawPixel(buffer,x-yr,y-xr,color);
		__frameBuffer_drawPixel(buffer,x-yr,y+xr,color);
		__frameBuffer_drawPixel(buffer,x+yr,y-xr,color);
		yr++;
		RE += Ychange;
		Ychange += 2;

		if((RE << 2) + Xchange > 0){
			xr--;
			RE += Xchange;
			Xchange += 2;
		}
	}while(xr >= yr);
	*/
}
void frameBuffer_drawLine(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color){
	/*
	 * 		Bresenhams's line algorithm for integers arithmetic
	 */
	if(abs(y2-y1) < abs(x2-x1)){
		if(x1 > x2){
			__frameBuffer_drawLineLow(buffer,x2,y2,x1,y1,color);
		}else{
			__frameBuffer_drawLineLow(buffer,x1,y1,x2,y2,color);
		}
	}else{
		if(y1 > y2){
			__frameBuffer_drawLineHigh(buffer,x2,y2,x1,y1,color);
		}else{
			__frameBuffer_drawLineHigh(buffer,x1,y1,x2,y2,color);
		}
	}


}
void __frameBuffer_drawLineLow(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color){
	int dy = y2 - y1;
	int dx = x2 - x1;
	int yi = 1;
	if(dy < 0){
		yi = -1;
		dy *= -1;
	}
	int D = 2*dy - dx;
	int y = y1;

	for(int x=x1; x<=x2; x++){
		__frameBuffer_drawPixel(buffer,x,y,color);
		if(D>0){
			y += yi;
			D -= 2*dx;
		}
		D += 2*dy;
	}
}

void __frameBuffer_drawLineHigh(uint16_t *buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ColorRGB565 *color){
	int dy = y2 - y1;
	int dx = x2 - x1;
	int xi = 1;
	if(dx<0){
		xi = -1;
		dx *= -1;
	}
	int D = 2*dx - dy;
	int x = x1;

	for(int y=y1; y<=y2; y++){
		__frameBuffer_drawPixel(buffer,x,y,color);
		if(D>0){
			x += xi;
			D -= 2*dy;
		}
		D +=2*dx;
	}
}


void __frameBuffer_drawPixel(uint16_t *buffer, int16_t x, uint16_t y, ColorRGB565 *color){
	uint16_t rgb565_r, rgb565_g, rgb565_b;
		if(color->r > 31)
			rgb565_r = 31;
		else
			rgb565_r = color->r;
		if(color->g > 63)
			rgb565_g = 63;
		else
			rgb565_g = color->g;
		if(color->b > 32)
			rgb565_b = 31;
		else
			rgb565_b = color->b;
		uint32_t pixel_position = (y*LCD_WIDTH + x);
		buffer += pixel_position;
		*buffer = (rgb565_r << 11 | rgb565_g << 5 | rgb565_b);
}

inline void __frameBuffer_putChar(uint16_t *buffer, char c, fontType_t *font, uint16_t x, uint16_t y, ColorRGB565 *color){
	/*	Bytes per line	*/
	uint8_t bytesHeight;
	uint8_t bytesWidth;
	bytesHeight = font->FontHeight / (sizeof(font->FontHeight)*8);
	bytesWidth = font->FontWidth / (sizeof(font->FontWidth)*8);
	if(font->FontHeight % (sizeof(font->FontHeight)*8) > 0){
		bytesHeight += 1;
	}
	if(font->FontWidth % (sizeof(font->FontWidth)*8) > 0){
		bytesWidth += 1;
	}
	uint8_t characterSpacing = bytesHeight * bytesWidth * 8;
	uint8_t columnSpaceing = bytesWidth;
	for(uint8_t k=0; k<bytesWidth; k++){
		for(uint8_t i=0; i<font->FontHeight; i++){
			for(uint8_t j=0; j<8; j++){
				if((*(font->FontData + ((characterSpacing)*(c-32))+(columnSpaceing*i)+k)) & 0x80 >> j){
					__frameBuffer_drawPixel(buffer,j+x+(k*8), i+y,color);
				}
			}
		}
	}
}

void frameBuffer_putString(uint16_t *buffer, char *str, fontType_t *font, uint16_t x, uint16_t y, ColorRGB565 *color){
	while(*str != '\0'){
		__frameBuffer_putChar(buffer,*str,font,x,y,color);
		str++;
		x += font->FontWidth;
	}
}

void frameBufferDMA2D_initalize(void){

}

void frameBufferDMA2D_fillRect(uint16_t *buffer, uint16_t x, uint16_t y, uint16_t a, uint16_t b, ColorRGB565 *color){
	DMA2D->CR |= (0x03 << DMA2D_CR_MODE_Pos);		// Register to memory
	DMA2D->OMAR = buffer + (x + y * LCD_WIDTH);		// output memory address
	DMA2D->OOR = LCD_WIDTH - a;							// line offset
	DMA2D->NLR = (a << DMA2D_NLR_PL_Pos) | (b << DMA2D_NLR_NL_Pos);
	DMA2D->OPFCCR = DMA2D_OPFCCR_CM_1;				// RGB565
	DMA2D->OCOLR = (color->r << 11) | (color->g << 5) | (color->b << 0);
	DMA2D->CR |= DMA2D_CR_START;

}
