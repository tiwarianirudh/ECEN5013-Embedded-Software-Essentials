/*
 * spi.h
 *
<<<<<<< HEAD
 *  Created on: Nov 3, 2016
 *      Author: mmsat
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_

void SPI0_init(void);
void SPI0_tx(unsigned char data);
=======
 *  Created on: Nov 9, 2016
 *      Author: aniru
 */

#ifndef SPI
#define SPI

#include "MKL25Z4.h"

void SPI_init(void);
uint8_t spi_datatransfer(uint8_t spi_data);
void cs_low(void);
void cs_high(void);
>>>>>>> 77841ff9f62611b1982f0e272250d2d7396c48ae

#endif
