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
#define LCD_HSYNC	10
#define LCD_HFP 	10		// Horizontal front porch
#define	LCD_HBP		20		// Horizontal back porch
#define LCD_VSYNC	2
#define LCD_VFP 	2		// Vertical front porch
#define	LCD_VBP	 	2		// Vertical back porch
#define LCD_WIDTH	240
#define LCD_HEIGHT	320
#define LCD_PIXELS	LCD_WIDTH*LCD_HEIGHT


void SystemClock_Config(void);
void LCD_LtdcInit(uint16_t *layer1_adds);


int main(void)
{
  HAL_Init();
  SystemClock_Config();
  RCC->APB2ENR |= RCC_APB2ENR_LTDCEN; 	// clk enable LTDC;


  while (1){
  }
}
void LCD_LtdcInit(uint16_t *layer1_adds){
	LTDC->SSCR |= LCD_HSYNC-1 << LTDC_SSCR_HSW_Pos | LCD_VSYNC-1 << LTDC_SSCR_VSH_Pos;	// HSYNC | VSYNC
	LTDC->BPCR |= LCD_HSYNC+LCD_HBP-1 << LTDC_BPCR_AHBP_Pos | LCD_VSYNC+LCD_VBP-1 << LTDC_BPCR_AVBP_Pos; 	// Horizontal | Vertical back porch
	LTDC->AWCR |= LCD_HSYNC+LCD_HBP+LCD_WIDTH-1 << LTDC_AWCR_AAW_Pos | LCD_VSYNC+LCD_VBP+LCD_HEIGHT-1 << LTDC_AWCR_AAH_Pos;	// Active Width | Height
	LTDC->TWCR |= LCD_HSYNC+LCD_HBP+LCD_WIDTH+LCD_HFP-1 << LTDC_TWCR_TOTALW_Pos |
			LCD_VSYNC+LCD_VFP+LCD_HEIGHT+LCD_VBP << LTDC_TWCR_TOTALH_Pos;	// Total width \ height

	LTDC_Layer1->WHPCR |= LCD_HSYNC+LCD_HBP << LTDC_LxWHPCR_WHSPPOS_Pos | LCD_HSYNC+LCD_HBP+LCD_WIDTH-1 << LTDC_LxWHPCR_WHSTPOS_Pos;
	LTDC_Layer1->WVPCR |= LCD_VSYNC+LCD_VBP << LTDC_LxWVPCR_WVSPPOS_Pos | LCD_VSYNC+LCD_VBP+LCD_HEIGHT-1 << LTDC_LxWVPCR_WVSTPOS_Pos;
	LTDC_Layer1->PFCR |= 0x02;		// RGB565
	LTDC_Layer1->CFBAR = layer1_adds;
	LTDC_Layer1->CFBLR |= LCD_WIDTH*2 << LTDC_LxCFBLR_CFBP_Pos | LCD_WIDTH*2+3 << LTDC_LxCFBLR_CFBLL_Pos;	// Number of bytes per line | +3
	LTDC_Layer1->CFBLNR |= LCD_HEIGHT << LTDC_LxCFBLNR_CFBLNBR_Pos;		// line number

	LTDC->GCR |= LTDC_GCR_LTDCEN;		// LTDC enable
	LTDC_Layer1->CR |= LTDC_LxCR_LEN;	// layer 1 enable
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
