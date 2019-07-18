/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-12-28

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "../mLib/inc/mLib_spi.h"
#include "../mLib/inc/mLib_i2c.h"


/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
#define GYRO_CS_HIGH	GPIOC->BSRRL = 2;
#define GYRO_CS_LOW		GPIOC->BSRRH = 2;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
   int i = 0;

  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /* TODO - Add your application code here */

  /*
   * 	SPI5 clock enable
   */
  RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
  /*
   * 	I2C2 clock enable
   */
  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
  /*
   * 	GPIO clock enable
   */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;



  /*	SPI5 GPIO Initalize
   * 	SCK 	<->	 	PF7
   * 	MISO 	<-> 	PF8
   * 	MOSI	<->		PF9
   *
   * 	SPI5	<->		AF5
   */
  GPIOF->MODER |= GPIO_MODER_MODER7_1 | GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;
  GPIOF->AFR[0] |= 5 << 28;						// PF7
  GPIOF->AFR[1] |= 5 << 0 | 5 << 4;				// PF8, PF9
  mLib_SpiInitalize(SPI5);

  /*
   * 		Gyro SPI chip select pin init
   * 		CS	<-> PC1
   */
  GPIOC->MODER |= GPIO_MODER_MODER1_0;

  uint8_t spi_receive[2];
  GYRO_CS_LOW;
  spi_receive[0] = mLib_SpiTransmitReceiveByte(SPI5, 0x8f);
  spi_receive[1] = mLib_SpiTransmitReceiveByte(SPI5, 0x22);
  GYRO_CS_HIGH;

  /*
   * 	I2C2 GPIO Init
   * 	SDA		<->		PF0
   * 	SCL		<->		PF1
   *
   * 	I2C2 	<->		AF4
   */
  GPIOF->MODER |= GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1;

  GPIOF->OTYPER |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_1;
  GPIOF->PUPDR |= GPIO_PUPDR_PUPDR0_0 | GPIO_PUPDR_PUPDR1_0;
  GPIOF->AFR[0] |= 4 << 0 | 4 << 4;

  uint8_t i2c_testData[] = {0x00};
  uint8_t i2c_buffer[16];
  mLib_I2cInitalize(I2C2);
  mlib_I2cTransmitBytes(I2C2, 0x0e, i2c_testData, 1);
  mLib_I2cRecieveBytes(I2C2, 0x0e, i2c_buffer, 16);

  /* Infinite loop */
  while (1)
  {
	i++;
  }
}
