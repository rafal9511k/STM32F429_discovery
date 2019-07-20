/*
 * IL9341.h
 *
 *  Created on: 22.09.2017
 *      Author: rafal
 */

#ifndef IL9341_H_
#define IL9341_H_

#include "stm32f4xx.h"
#include "fonts.h"

/*	LCD Config	*/
#define CSX_pin				2
#define	DCX_pin				13
#define	RST_pin				12

#define	CSX_port			GPIOC
#define DCX_port			GPIOD
#define	RST_port			GPIOD

#define DISPLAY_WIDHT 		240
#define DISPLAY_HEIGTH		320

#define ILI9341_SPI			SPI5

void LCD_Initalize(void);
void ILI9341_SPI_Init(void);
void IL9341_GPIO_Init(void);
void ILI9341_SPI_GPIO_Init(void);
void ILI9341_SPI_Send_byte(uint8_t byte);
void ILI9341_Send_Cmd(uint8_t cmd);
void ILI9341_Send_Data(uint8_t data);
void ILI9341_Set_Cursor_Position(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_FillAll(uint16_t color);
void LCD_PutChar(char c, uint16_t x, uint16_t y, fontType_t *font, uint16_t color);
void LCD_PutString(char *str, uint16_t x, uint16_t y, fontType_t *font, uint16_t color);

void __ili9341_set_csx(void);
void __ili9341_set_dcx(void);
void __ili9341_set_rst(void);
void __ili9341_reset_csx(void);
void __ili9341_reset_dcx(void);
void __ili9341_reset_rst(void);


#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC					0x36
#define ILI9341_PIXEL_FORMAT		0x3A
#define ILI9341_WDB					0x51
#define ILI9341_WCD					0x53
#define ILI9341_RGB_INTERFACE		0xB0
#define ILI9341_FRC					0xB1
#define ILI9341_BPC					0xB5
#define ILI9341_DFC					0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC					0xF7




#endif /* IL9341_H_ */
