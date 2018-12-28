/*
 * mLib_spi.c
 *
 *  Created on: 28.12.2018
 *      Author: rafal
 */

#include "../inc/mLib_spi.h"
/*
 *
 * 		8 bit data format
 * 		clk / 4
 *
 */
void mLib_SpiInitalize(SPI_TypeDef *spi){
	/*	Software Slave Managment, set SSI , clk/div, master mode	*/
	spi->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_MSTR;
	spi->CR1 |= SPI_CR1_SPE;
}

void mLib_SpiTransmitByte(SPI_TypeDef *spi, uint8_t data){
	while(!(spi->SR & SPI_SR_TXE));
	spi->DR = data;
}

uint8_t mLib_SpiReceiveByte(SPI_TypeDef *spi){
	while(!spi->SR & SPI_SR_RXNE);
	return spi->DR;
}
