/*
 * ltdc.c
 *
 *  Created on: 18.07.2019
 *      Author: rafal
 */

#include "../inc/ltdc.h"

void LCD_LtdcInit(uint32_t *layer1_adds, uint32_t *layer2_adds){



	/*
	  LTDC->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);             // signal polarities
	  LTDC->SSCR = 9 << LTDC_SSCR_HSW_Pos | 1 << LTDC_SSCR_VSH_Pos;                                  // HSYNC and VSYNC length
	  LTDC->BPCR = 29 << LTDC_BPCR_AHBP_Pos | 3 << LTDC_BPCR_AVBP_Pos;                               // horizontal and vertical accumulated back porch
	  LTDC->AWCR = 269 << LTDC_AWCR_AAW_Pos | 323 << LTDC_AWCR_AAH_Pos;                              // accumulated active width and height
	  LTDC->TWCR = 279 << LTDC_TWCR_TOTALW_Pos | 327 << LTDC_TWCR_TOTALH_Pos;                        // accumulated total width and height
	  LTDC->BCCR = 0xFF << LTDC_BCCR_BCGREEN_Pos;                                                    // green background color


	  LTDC_Layer1->WHPCR = 269 << LTDC_LxWHPCR_WHSPPOS_Pos | 30 << LTDC_LxWHPCR_WHSTPOS_Pos;          // window horizontal start/stop positions
	  LTDC_Layer1->WVPCR = 323 << LTDC_LxWVPCR_WVSPPOS_Pos | 4 << LTDC_LxWVPCR_WVSTPOS_Pos;           // window vertical start/stop positions
	  LTDC_Layer1->PFCR = 0x02;   // RGB565 pixel format
	  LTDC_Layer1->DCCR = 0xFF << LTDC_LxDCCR_DCALPHA_Pos | 0xFF << LTDC_LxDCCR_DCGREEN_Pos;          // layer default color
	  LTDC_Layer1->CFBAR = (uint32_t)layer1_adds;                                                           // frame buffer start address
	  LTDC_Layer1->CFBLR = (240 * 2) << LTDC_LxCFBLR_CFBP_Pos | (240 * 2 + 3) << LTDC_LxCFBLR_CFBLL_Pos;  // frame buffer line length and pitch
	  LTDC_Layer1->CFBLNR = 320;                                                                      // frame buffer line number
	  LTDC_Layer1->CACR = 255;                                                                        // constant alpha
	  LTDC_Layer1->CR |= LTDC_LxCR_LEN;                                                               // enable layer1

	  LTDC->SRCR = LTDC_SRCR_IMR;                                                                     // immediate shadow registers reload

	  LTDC->GCR |= LTDC_GCR_LTDCEN;
	  */
	LTDC->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);
	LTDC->SSCR = (LCD_HSYNC-1) << LTDC_SSCR_HSW_Pos | (LCD_VSYNC-1) << LTDC_SSCR_VSH_Pos;	// HSYNC | VSYNC
	LTDC->BPCR = (LCD_HSYNC+LCD_HBP-1) << LTDC_BPCR_AHBP_Pos | (LCD_VSYNC+LCD_VBP-1) << LTDC_BPCR_AVBP_Pos; 	// Horizontal | Vertical back porch
	LTDC->AWCR = (LCD_HSYNC+LCD_HBP+LCD_WIDTH-1) << LTDC_AWCR_AAW_Pos | (LCD_VSYNC+LCD_VBP+LCD_HEIGHT-1) << LTDC_AWCR_AAH_Pos;	// Active Width | Height
	LTDC->TWCR = (LCD_HSYNC+LCD_HBP+LCD_WIDTH+LCD_HFP-1) << LTDC_TWCR_TOTALW_Pos |
			(LCD_VSYNC+LCD_VFP+LCD_HEIGHT+LCD_VBP) << LTDC_TWCR_TOTALH_Pos;	// Total width \ height


	LTDC_Layer1->WHPCR = (LCD_HSYNC+LCD_HBP) << LTDC_LxWHPCR_WHSTPOS_Pos | (LCD_HSYNC+LCD_HBP+LCD_WIDTH-1) << LTDC_LxWHPCR_WHSPPOS_Pos;
	LTDC_Layer1->WVPCR = (LCD_VSYNC+LCD_VBP) << LTDC_LxWVPCR_WVSTPOS_Pos | (LCD_VSYNC+LCD_VBP+LCD_HEIGHT-1) << LTDC_LxWVPCR_WVSPPOS_Pos;
	LTDC_Layer1->PFCR = 0x02;		// RGB565
	LTDC_Layer1->DCCR = 0xff << LTDC_LxDCCR_DCALPHA_Pos | 0xff << LTDC_LxDCCR_DCRED_Pos;
	LTDC_Layer1->CFBAR = (uint32_t)layer1_adds;
	LTDC_Layer1->CFBLR = (LCD_WIDTH*2) << LTDC_LxCFBLR_CFBP_Pos | (LCD_WIDTH*2+3) << LTDC_LxCFBLR_CFBLL_Pos;	// Number of bytes per line | +3
	LTDC_Layer1->CFBLNR = LCD_HEIGHT << LTDC_LxCFBLNR_CFBLNBR_Pos;		// line number
	LTDC_Layer1->CACR = 0xff;		// constant alpha
	LTDC_Layer1->CR |= LTDC_LxCR_LEN;	// layer 1 enable

	LTDC_Layer2->WHPCR |= (LCD_HSYNC+LCD_HBP) << LTDC_LxWHPCR_WHSTPOS_Pos | (LCD_HSYNC+LCD_HBP+LCD_WIDTH-1) << LTDC_LxWHPCR_WHSPPOS_Pos;
	LTDC_Layer2->WVPCR |= (LCD_VSYNC+LCD_VBP) << LTDC_LxWVPCR_WVSTPOS_Pos | (LCD_VSYNC+LCD_VBP+LCD_HEIGHT-1) << LTDC_LxWVPCR_WVSPPOS_Pos;
	LTDC_Layer2->PFCR |= 0x02;		// RGB565
	LTDC_Layer2->DCCR = 0xff << LTDC_LxDCCR_DCALPHA_Pos | 0xff << LTDC_LxDCCR_DCRED_Pos;
	LTDC_Layer2->CFBAR = layer2_adds;
	LTDC_Layer2->CFBLR |= (LCD_WIDTH*2) << LTDC_LxCFBLR_CFBP_Pos | (LCD_WIDTH*2+3) << LTDC_LxCFBLR_CFBLL_Pos;	// Number of bytes per line | +3
	LTDC_Layer2->CFBLNR |= LCD_HEIGHT << LTDC_LxCFBLNR_CFBLNBR_Pos;		// line number
	LTDC_Layer2->CACR = 0xff;		// constant alpha
	LTDC_Layer2->CR |= LTDC_LxCR_LEN;	// layer 2 enable

	LTDC->SRCR = LTDC_SRCR_VBR;			// reload shadow registers
	LTDC->GCR |= LTDC_GCR_LTDCEN;		// LTDC enable

}

inline void __lcd_rgb565_drawPixel(uint16_t *buffer, uint8_t r, uint8_t g, uint8_t b, uint16_t x, uint16_t y){
	uint16_t rgb565_r, rgb565_g, rgb565_b;
	if(r > 31)
		rgb565_r = 31;
	else
		rgb565_r = r;
	if(g > 63)
		rgb565_g = 63;
	else
		rgb565_g = g;
	if(b > 32)
		rgb565_b = 31;
	else
		rgb565_b = b;
	uint32_t pixel_position = (y*LCD_WIDTH + x);
	buffer += pixel_position;
	*buffer = (rgb565_r << 11 | rgb565_g << 5 | rgb565_b);
}

inline void LCD_PutChar(char c,uint16_t *buffer, uint16_t x, uint16_t y, fontType_t *font, uint8_t r, uint8_t g, uint8_t b){
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
					__lcd_rgb565_drawPixel(buffer,r,g,b,j+x+(k*8), i+y);
				}
			}
		}
	}
}
void LCD_PutString(char *str,uint16_t *buffer,  uint16_t x, uint16_t y, fontType_t *font, uint8_t r, uint8_t g, uint8_t b){
	while(*str != '\0'){
		LCD_PutChar(*str, buffer, x, y, font, r, g, b);
		str++;
		x+=font->FontWidth;

	}
}
