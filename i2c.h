/*
 * i2c.h
 *
 *  Created on: Sep 25, 2020
 *      Author: Joe Krachey, dagrawal23, jdhunt
 */

#ifndef I2C_H_
#define I2C_H_

#include "msp.h"
#include <stdint.h>

/**********************************************************************************************
 * Initialize I2C
 **********************************************************************************************/
void i2c_init(void);

/**********************************************************************************************
 * Read 16 bits of data from subordinate device
 **********************************************************************************************/
uint16_t i2c_read_16(uint8_t subordinate_address, uint8_t reg_address);

/**********************************************************************************************
 * Write 16 bits of data to subordinate devic
 **********************************************************************************************/
void i2c_write_16(uint8_t subordinate_address, uint8_t reg_address, uint16_t data);



#endif /* I2C_H_ */
