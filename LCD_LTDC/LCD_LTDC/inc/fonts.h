/*
 * fonts.h
 *
 *  Created on: 29.12.2018
 *      Author: rafal
 */

#ifndef INC_FONTS_H_
#define INC_FONTS_H_

#include "stm32f4xx.h"

typedef struct{
	uint8_t FontWidth;
	uint8_t FontHeight;
	uint8_t *FontData;
}fontType_t;

extern fontType_t font_SmallFont;
extern fontType_t font_BigFont;
extern fontType_t font_Ubuntu;

#endif /* INC_FONTS_H_ */
