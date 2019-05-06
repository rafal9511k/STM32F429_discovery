/*
 * mLib_i2c.c
 *
 *  Created on: 20.03.2019
 *      Author: root
 */

#include "../inc/mLib_i2c.h"

void mLib_I2cInitalize(I2C_TypeDef *i2c){
	i2c->CR1 |= I2C_CR1_PE | I2C_CR1_START;
	i2c->CR2 |= 29;
}

void mlib_I2cTransmitByte(I2C_TypeDef *i2c, uint8_t data){
	i2c->DR = data;
}
