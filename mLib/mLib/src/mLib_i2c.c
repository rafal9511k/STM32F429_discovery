/*
 * mLib_i2c.c
 *
 *  Created on: 20.03.2019
 *      Author: root
 */

#include "../inc/mLib_i2c.h"

void mLib_I2cInitalize(I2C_TypeDef *i2c){
	i2c->CR1 |= I2C_CR1_SWRST;		// reset
	i2c->CR1 &= ~I2C_CR1_SWRST;		// clear reset
	i2c->CR1 &= ~I2C_CR1_PE;		// diable module
	i2c->CR2 |= 15;					// Pclk
	i2c->CCR |= 72;					// ccr reg
	i2c->TRISE = 16;				// Trise
	i2c->CR1 |= I2C_CR1_PE;


}

void mlib_I2cTransmitBytes(I2C_TypeDef *i2c, uint8_t address, uint8_t *data, uint32_t length){
//	i2c->DR = data;
	i2c->CR1 |= I2C_CR1_START;
	while(!(i2c->SR1 & I2C_SR1_SB));	// wait until START bit is set
	i2c->DR = address<<1;
	while(!(i2c->SR1 & I2C_SR1_ADDR));	// wait until ADDR is set
	i2c->SR2;
	for(uint32_t i=0;i<length;i++){
		i2c->DR = *(data+i);
		while(!(i2c->SR1 & I2C_SR1_TXE));
	}
	i2c->CR1 |= I2C_CR1_STOP;
	while(!(i2c->SR2 & I2C_SR2_BUSY));
	/*
	i2c->CR1 |= I2C_CR1_START;
	while(!(i2c->SR1 & I2C_SR1_SB));	// wait until START bit is set
	i2c->DR = data | 0x01;
	while(!(i2c->SR1 & I2C_SR1_ADDR));	// wait until TxE is set
	i2c->SR2;
	*/

}

uint8_t mLib_I2cRecieveBytes(I2C_TypeDef *i2c,uint8_t address, uint8_t *buffer, uint32_t length){
	i2c->CR1 |= I2C_CR1_START;
	while(!(i2c->SR1 & I2C_SR1_SB));	// wait until START bit is set
	i2c->DR = address<<1 | 0x01;
	while(!(i2c->SR1 & I2C_SR1_ADDR));	// wait until ADDR is set
	i2c->SR2;
	i2c->CR1 |= I2C_CR1_ACK;			// AK
	for(uint32_t i=0;i<length-1;i++){
		while(!(i2c->SR1 & I2C_SR1_RXNE));	// wait until RXNE is sets
		*buffer++ = i2c->DR;
	}
	i2c->CR1 &= ~I2C_CR1_ACK;			// NAK
	while(!(i2c->SR1 & I2C_SR1_RXNE));	// wait until RXNE is sets
	*buffer++ = i2c->DR;
	i2c->CR1 |= I2C_CR1_STOP; 			// STOP bit
}
