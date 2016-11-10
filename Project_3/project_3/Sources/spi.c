/*
 * spi.c
 *
<<<<<<< HEAD
 *  Created on: Nov 3, 2016
 *      Author: Mukund Madhusudan Atre
 */

#include "MKL25Z4.h"
#include <stdint.h>
#include "spi.h"


void SPI0_init(void)
{
  SIM->SCGC5 |= 0x1000;			/*	enable	clock	to	Port	D	*/
  PORTD->PCR[1]	= 0x200;		/*	make	PTD1	pin	as	SPI	SCK	*/
  PORTD->PCR[2]	= 0x200;		/*	make	PTD2	pin	as	SPI	MOSI	*/
  PORTD->PCR[0]	= 0x100;		/*	make	PTD0	pin	as	GPIO	*/
  PTD->PDDR	|= 0x01;			/*	make	PTD0	as	output	pin	for	/SS	*/
  PTD->PSOR	= 0x01;				/*	make	PTD0	idle	high	*/
  SIM->SCGC4 |=	0x400000;		/*	enable	clock	to	SPI0	*/
  SPI0->C1 = 0x10;			    /*	disable	SPI	and	make	SPI0	master	*/
  SPI0->BR = 0x60;			    /*	set	Baud	rate	to	1	MHz	*/
  SPI0->C1 |= 0x40;			    /*	Enable	SPI	module	*/

}


void SPI0_tx(unsigned char data)	{
 volatile char dummy; PTD->PCOR = 1;    /*	assert	/SS	*/
 while(!(SPI0->S	&	0x20))	{

 }                                      /*	wait	until	tx	ready	*/
 SPI0->D	=	data;					/*	send	data	byte	*/
 while(!(SPI0->S	&	0x80))
 {
 }                                      /*	wait	until	tx	complete	*/
 dummy	=	SPI0->D;                    /*	clear	SPRF	*/
 PTD->PSOR	=	1;	                    /*	deassert	/SS	*/

}
=======
 *  Created on: Nov 9, 2016
 *      Author: aniru
 */
#include "SPI.h"

void SPI_init(void)
{

	//Turning ON clock for the C module
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//Enable Clock for SPI0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	PORTC_PCR4 = PORT_PCR_MUX(0x01);
	GPIOC_PDDR = (1<<4);				//PortC PIN4 as output
	GPIOC_PSOR = (1<<4);				//SS high initially
	PORTC_PCR5 = PORT_PCR_MUX(0x02);    //PTC5 to mux 2 [SCK]
	PORTC_PCR6 = PORT_PCR_MUX(0x02);    //PTC6 to mux 2 [MOSI]
	PORTC_PCR7 = PORT_PCR_MUX(0x02);    //PTC7 to mux 2 [MISO]

	SPI0_C1 = SPI_C1_MSTR_MASK;		//Enabling SPI as master

	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01)); //Setting Bitrate 1Mbps

	SPI0_C1 |= SPI_C1_SPE_MASK;    //SPI0 Enable
}

uint8_t spi_datatransfer(uint8_t spi_data)
{
	while(!(SPI_S_SPTEF_MASK & SPI0_S));
	SPI0_D = spi_data;    //Write char to SPI
	while(!(SPI_S_SPRF_MASK & SPI0_S));
	return SPI0_D;
}

void cs_low(void)
{
	GPIOC_PCOR = (1<<4);
}

void cs_high(void)
{
	GPIOC_PSOR = (1<<4);
}


>>>>>>> 77841ff9f62611b1982f0e272250d2d7396c48ae
