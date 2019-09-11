/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "main.h"

#include "../LCD_ili9341_LTDC/inc/ltdc.h"
#include "../LCD_ili9341_LTDC/inc/RGB565_320x240.h"
#include "../LCD_ili9341_LTDC/inc/fonts.h"
#include "../LCD_ili9341_LTDC/inc/ili9341.h"
#include "../LCD_ili9341_LTDC/inc/frameBuffer.h"
#include "mLib_spi.h"

void SystemClock_Config(void);



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  RCC->APB2ENR |= RCC_APB2ENR_LTDCEN; 	// clk enable LTDC;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN
		  | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOFEN; // LTDC ports, spi5;
  RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;	// SPI5 enable CLK
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;	// DMA2D clk enable

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
  /*
   * 		LTDC GPIO INIT
   */
  GPIO_InitTypeDef ltdc_gpio;
  ltdc_gpio.Mode = GPIO_MODE_AF_PP;
  ltdc_gpio.Pull = GPIO_NOPULL;
  ltdc_gpio.Speed = GPIO_SPEED_FAST;
  ltdc_gpio.Alternate = GPIO_AF14_LTDC;
  /*
   * 	GPIOA
   */
  ltdc_gpio.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOA,&ltdc_gpio);
  /*
   * 	GPIOB
   */
  ltdc_gpio.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
		  GPIO_PIN_11 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOB,&ltdc_gpio);
  /*
   * 	GPIOC
   */
  ltdc_gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC,&ltdc_gpio);
  /*
   * 	GPIOD
   */
  ltdc_gpio.Pin = GPIO_PIN_3 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOD,&ltdc_gpio);
  /*
   * 	GPIOF
   */
  ltdc_gpio.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOF, &ltdc_gpio);
  /*
   * 	GPIOG
   */
  ltdc_gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11
		  | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &ltdc_gpio);
  mLib_SpiInitalize(SPI5);


  LCD_Initalize();
  LCD_LtdcInit((uint32_t)0,(uint32_t)RGB565_320x240_1);
  //LTDC_Layer1->CFBAR = (uint32_t)&RGB565_320x240_1;
//  LTDC_Layer1->DCCR = 0x55 << LTDC_LxDCCR_DCALPHA_Pos | 0xff << LTDC_LxDCCR_DCBLUE_Pos;

 // __lcd_rgb565_drawPixel(RGB565_320x240_1,0,63,0,100,300);
//  __lcd_rgb565_drawPixel(RGB565_320x240_1,2,0,31,0,0);
  ColorRGB565 color = {
	  0, 63, 19
  };
 // __frameBuffer_putChar(RGB565_320x240_1, 'a', &font_BigFont, 90, 90, &color);
 // frameBuffer_putString(RGB565_320x240_1, "ABCASD", &font_BigFont,30,50,&color);
 // frameBuffer_drawLine(RGB565_320x240_1,0,0,10,150,&color);
 // color.g = 0;
  //color.b = 25;
//  frameBuffer_drawLine(RGB565_320x240_1,10,80,100,100,&color);
//  frameBuffer_drawLine(RGB565_320x240_1,10,80,100,140,&color);
//  frameBuffer_drawLine(RGB565_320x240_1,10,80,100,300,&color);
  frameBuffer_drawCircle(RGB565_320x240_1,50,50,50,&color);
  // LTDC->SRCR = LTDC_SRCR_VBR;
  frameBufferDMA2D_fillRect(RGB565_320x240_1,0,0,239,319,&color);
  int i;
  int a;
  while (1){
	  i++;
	  a = -i;
  }
}


void SystemClock_Config(void)
{
	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	    /**Configure the main internal regulator output voltage
	    */
	  __HAL_RCC_PWR_CLK_ENABLE();

	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.HSICalibrationValue = 16;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	  RCC_OscInitStruct.PLL.PLLM = 8;
	  RCC_OscInitStruct.PLL.PLLN = 180;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  HAL_RCC_OscConfig(&RCC_OscInitStruct);

	    /**Activate the Over-Drive mode
	    */
	  HAL_PWREx_EnableOverDrive();

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

	  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	  PeriphClkInitStruct.PLLSAI.PLLSAIN = 60;
	  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
	  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
