/*
 * mLib_spi.h
 *
 *  Created on: 28.12.2018
 *      Author: rafal
 */

#ifndef INC_MLIB_SPI_H_
#define INC_MLIB_SPI_H_

#include "stm32f4xx.h"

void mLib_SpiInitalize(SPI_TypeDef *spi);
void mLib_SpiTransmitByte(SPI_TypeDef *spi, uint8_t data);
uint8_t mLib_SpiReceiveByte(SPI_TypeDef *spi);

#endif /* INC_MLIB_SPI_H_ */
