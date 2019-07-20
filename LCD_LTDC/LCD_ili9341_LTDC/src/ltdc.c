/*
 * ltdc.c
 *
 *  Created on: 18.07.2019
 *      Author: rafal
 */

#include "ltdc.h"

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


