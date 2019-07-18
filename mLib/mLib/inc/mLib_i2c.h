/*
 * mLib_i2c.h
 *
 *  Created on: 20.03.2019
 *      Author: root
 */

#ifndef INC_MLIB_I2C_H_
#define INC_MLIB_I2C_H_

#include "stm32f4xx.h"

void mLib_I2cInitalize(I2C_TypeDef *i2c);
void mlib_I2cTransmitBytes(I2C_TypeDef *i2c, uint8_t address, uint8_t *data, uint32_t length);
uint8_t mLib_I2cRecieveBytes(I2C_TypeDef *i2c,uint8_t address, uint8_t *buffer, uint32_t length);

#endif /* INC_MLIB_I2C_H_ */
