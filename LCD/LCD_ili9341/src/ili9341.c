/*
 * IL9341.c
 *
 *  Created on: 22.09.2017
 *      Author: rafal
 */
#include "stm32f4xx.h"
#include "../inc/ili9341.h"
#include "../inc/mLib_spi.h"
#include "../inc/fonts.h"


void LCD_Initalize(void){
//	ILI9341_SPI_GPIO_Init();
//	ILI9341_SPI_Init();
	IL9341_GPIO_Init();
//	GPIO_SetBits(RST_port, RST_pin);
//	GPIO_SetBits(CSX_port, CSX_pin);
//	GPIO_SetBits(DCX_port, DCX_pin);
	ILI9341_Send_Cmd(ILI9341_RESET);
	for(int i = 0; i<0xff; i++){
		i++;
	}
	ILI9341_Send_Cmd(ILI9341_POWERA);
	ILI9341_Send_Data(0x39);
	ILI9341_Send_Data(0x2c);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x43);
	ILI9341_Send_Data(0x82);
	ILI9341_Send_Cmd(ILI9341_POWERB);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0xa2);
	ILI9341_Send_Data(0xf0);
	ILI9341_Send_Cmd(ILI9341_DTCA);
	ILI9341_Send_Data(0x85);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x78);
	ILI9341_Send_Cmd(ILI9341_DTCB);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Cmd(ILI9341_POWER_SEQ);
	ILI9341_Send_Data(0x64);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x12);
	ILI9341_Send_Data(0x81);
	ILI9341_Send_Cmd(ILI9341_PRC);
	ILI9341_Send_Data(0x20);
	ILI9341_Send_Cmd(ILI9341_POWER1);
	ILI9341_Send_Data(0x23);
	ILI9341_Send_Cmd(ILI9341_POWER2);
	ILI9341_Send_Data(0x10);
	ILI9341_Send_Cmd(ILI9341_VCOM1);
	ILI9341_Send_Data(0x3e);
	ILI9341_Send_Data(0x28);
	ILI9341_Send_Cmd(ILI9341_VCOM2);
	ILI9341_Send_Data(0x86);
	ILI9341_Send_Cmd(ILI9341_MAC);
	ILI9341_Send_Data(0x48);
	ILI9341_Send_Cmd(ILI9341_PIXEL_FORMAT);
	ILI9341_Send_Data(0x55);
	ILI9341_Send_Cmd(ILI9341_FRC);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x18);
	ILI9341_Send_Cmd(ILI9341_DFC);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x82);
	ILI9341_Send_Data(0x27);
	ILI9341_Send_Cmd(ILI9341_3GAMMA_EN);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Cmd(ILI9341_COLUMN_ADDR);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0xef);
	ILI9341_Send_Cmd(ILI9341_PAGE_ADDR);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x01);
	ILI9341_Send_Data(0x3f);
	ILI9341_Send_Cmd(ILI9341_GAMMA);
	ILI9341_Send_Data(0x01);



	ILI9341_Send_Cmd(ILI9341_PGAMMA);
	ILI9341_Send_Data(0x0f);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0x2b);
	ILI9341_Send_Data(0x0c);
	ILI9341_Send_Data(0x0e);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x09);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Cmd(ILI9341_NGAMMA);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x0e);
	ILI9341_Send_Data(0x14);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x11);
	ILI9341_Send_Data(0x07);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0xc1);
	ILI9341_Send_Data(0x48);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x0f);
	ILI9341_Send_Data(0x0c);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0x36);
	ILI9341_Send_Data(0x0f);
	ILI9341_Send_Cmd(ILI9341_SLEEP_OUT);
	for(int i = 0; i<0xff; i++){
		i++;
	}
	ILI9341_Send_Cmd(ILI9341_DISPLAY_ON);
	ILI9341_Send_Cmd(ILI9341_GRAM);
}
void ILI9341_SPI_Init(void){
	/*
	ILI9341_SPI_GPIO_Init();
	SPI_InitTypeDef spi_init;
	spi_init.SPI_Mode = SPI_Mode_Master;
	spi_init.SPI_DataSize = SPI_DataSize_8b;
	spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	spi_init.SPI_CPHA = SPI_CPHA_1Edge;
	spi_init.SPI_CPOL = SPI_CPOL_Low;
	spi_init.SPI_NSS = SPI_NSS_Soft;
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI5EN, ENABLE);
	SPI_Init(SPI5, &spi_init);
	SPI_Cmd(SPI5, ENABLE);
	*/

}

void IL9341_GPIO_Init(void){
	CSX_port->MODER |= 0x01 << (CSX_pin*2);
	CSX_port->BSRRL = 0x01 << CSX_pin;
	DCX_port->MODER |= 0x01 << (DCX_pin*2);
	DCX_port->BSRRL = 0x01 << DCX_pin;
	RST_port->MODER |= 0x01 << (RST_pin*2);
	RST_port->BSRRL = 0x01 << RST_pin;
	/*
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD , ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	gpio.GPIO_Pin = CSX_pin;
	GPIO_Init(CSX_port, &gpio);
	gpio.GPIO_Pin = DCX_pin;
	GPIO_Init(DCX_port, &gpio);
	gpio.GPIO_Pin = RST_pin;
	GPIO_Init(RST_port, &gpio);
	*/
}
void ILI9341_SPI_GPIO_Init(void){
	/*
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOFEN, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9;
	GPIO_Init(GPIOF, &gpio_init);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7, GPIO_AF_SPI1);
	*/
}
void ILI9341_SPI_Send_byte(uint8_t byte){
//	while((SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) != SET) | (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_BSY) == SET)){
//	}
/*
	SPI_I2S_SendData(SPI5, byte);
	while((SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_TXE) != SET) | (SPI_I2S_GetFlagStatus(SPI5, SPI_I2S_FLAG_BSY) == SET)){
	}
*/
	mLib_SpiTransmitReceiveByte(ILI9341_SPI, byte);

}
void ILI9341_Send_Cmd(uint8_t cmd){
	/*
	GPIO_ResetBits(DCX_port, DCX_pin);
	GPIO_ResetBits(CSX_port, CSX_pin);
	ILI9341_SPI_Send_byte(cmd);
	GPIO_SetBits(CSX_port, CSX_pin);
	*/
	__ili9341_reset_dcx();
	__ili9341_reset_csx();
	ILI9341_SPI_Send_byte(cmd);
	__ili9341_reset_csx();
}
void ILI9341_Send_Data(uint8_t data){
	/*
	GPIO_SetBits(DCX_port, DCX_pin);
	GPIO_ResetBits(CSX_port, CSX_pin);
	ILI9341_SPI_Send_byte(data);
	GPIO_SetBits(CSX_port, CSX_pin);
	*/
	__ili9341_set_dcx();
	__ili9341_reset_csx();
	ILI9341_SPI_Send_byte(data);
	__ili9341_set_csx();
}
void ILI9341_Set_Cursor_Position(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	ILI9341_Send_Cmd(ILI9341_COLUMN_ADDR);
	ILI9341_Send_Data(x1>>8);
	ILI9341_Send_Data(x1 & 0xff);
	ILI9341_Send_Data(x2>>8);
	ILI9341_Send_Data(x2 & 0xff);
	ILI9341_Send_Cmd(ILI9341_PAGE_ADDR);
	ILI9341_Send_Data(y1>>8);
	ILI9341_Send_Data(y1 & 0xff);
	ILI9341_Send_Data(y2>>8);
	ILI9341_Send_Data(y2 & 0xff);
}
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color){
	ILI9341_Set_Cursor_Position(x, y, x, y);
	ILI9341_Send_Cmd(ILI9341_GRAM);
	ILI9341_Send_Data(color>>8);
	ILI9341_Send_Data(color & 0xff);
}
void LCD_FillAll(uint16_t color){
	ILI9341_Set_Cursor_Position(0, 0, DISPLAY_WIDHT-1, DISPLAY_HEIGTH -1);
	ILI9341_Send_Cmd(ILI9341_GRAM);
	for(int i=0; i< DISPLAY_HEIGTH*DISPLAY_WIDHT; i++){
		ILI9341_Send_Data(color>>8);
		ILI9341_Send_Data(color & 0xff);
	}
}
void LCD_PutChar(char c, uint16_t x, uint16_t y, fontType_t *font, uint16_t color){
	/*
	for(int i=0; i<font->FontHeight; i++){
		for(int j=0; j<font->FontWidth; j++){
			if((*(font->FontData+(font->FontHeight*(c-32))+i)) & 0x8000>>j){
				LCD_DrawPixel(j+x, i+y, color);
			}

		}
	}
	*/
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
					LCD_DrawPixel(j+x+(k*8), i+y, color);
				}
			}
		}
	}
}


void LCD_PutString(char *str, uint16_t x, uint16_t y, fontType_t *font, uint16_t color){
	while(*str != '\0'){
		LCD_PutChar(*str, x, y, font, color);
		str++;
		x+=font->FontWidth;

	}
}

inline void __ili9341_set_csx(void){
	CSX_port->BSRRL = 0x01 << CSX_pin;
}
inline void __ili9341_set_dcx(void){
	DCX_port->BSRRL = 0x01 << DCX_pin;
}
inline void __ili9341_set_rst(void){
	RST_port->BSRRL = 0x01 << RST_pin;
}
inline  void __ili9341_reset_csx(void){
	CSX_port->BSRRH = 0x01 << CSX_pin;
}
inline void __ili9341_reset_dcx(void){
	DCX_port->BSRRH = 0x01 << DCX_pin;
}
inline void __ili9341_reset_rst(void){
	RST_port->BSRRH = 0x01 << RST_pin;
}
