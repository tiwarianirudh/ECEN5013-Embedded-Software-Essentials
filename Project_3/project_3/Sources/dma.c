/*
 * dma.c
 *
 *  Created on: Nov 4, 2016
 *      Author: aniru
 */
#include"MKL25Z4.h"
#include<dma.h>
#include<stdint.h>
#include<profiler.h>
//#define EIGHTBIT
#define WORDS
//#define MEMMOVE

/*void init_DMA1(void)
{

		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

		DMAMUX0_CHCFG0 |= 0X00;


		DMA_DSR_BCR0 |= 0x20u;

		DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1);
		DMA_DCR0 |= DMA_DCR_SINC_MASK | DMA_DCR_DINC_MASK;

		DMAMUX0_CHCFG0 |= 0x49u;
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;

 }*/

void dma8(uint8_t *src, uint8_t *dst, uint32_t len)
{
		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK; //Enable clock to dmamux
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;	// Enable clock for DMA

		DMAMUX0_CHCFG0 |= 0X00;	// Disabling DMA MUX channel

		DMA_SAR0 = (uint32_t)src;
		DMA_DAR0 = (uint32_t)dst;
		DMA_DSR_BCR0 |= len; //Set number of bytes to be transferred
		DMA_DCR0 |= DMA_DCR_SSIZE(1);
		DMA_DCR0 |= DMA_DCR_DSIZE(1);
	#ifdef MEMMOVE
		DMA_DCR0 |= DMA_DCR_SINC_MASK; //Incrementing source address after each successful transfer
	#endif

		DMA_DCR0 |= DMA_DCR_DINC_MASK; //Incrementing destination address after each successful transfer
		DMA_DCR0 |= DMA_DCR_EINT_MASK; //Enabling interrupt after successful operation
		//NVIC->ISER[0] = 0x1; //DMA Channel0 transfer complete

		//__enable_irq();
		//NVIC_EnableIRQ(DMA0_IRQn);
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(49);
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;


		initialize_counter();
		counter_start();
		DMA_DCR0 |= DMA_DCR_START_MASK;

}

void dma32(uint32_t * src, uint32_t * dst, uint32_t len )
{
		uint32_t len1 = len % 4; // to get the no. of bytes which cannot form a word to  be transferred
		len = len -len1;  //complete words in len

		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK; //Enabling clock for DMAMUX
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK; //Enabling clock for DMA

		DMAMUX0_CHCFG0 |= 0X00;	// Disabling DMA MUX channel

		DMA_SAR0 = (uint32_t)src;
		DMA_DAR0 = (uint32_t)dst;
		DMA_DSR_BCR0 |= len; //Set number of bytes for transfer


		if(len1==0)
		{
			DMA_DCR0 |= DMA_DCR_SSIZE(0);
			DMA_DCR0 |= DMA_DCR_DSIZE(0);
		#ifdef MEMMOVE
			DMA_DCR0 |= DMA_DCR_SINC_MASK;
		#endif

			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_EINT_MASK;
			//NVIC->ISER[0] = 0x1;

			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(49);
			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
			initialize_counter();
			counter_start();

			DMA_DCR0 |= DMA_DCR_START_MASK;
		}

		else
		{
			DMA_DCR0 |= DMA_DCR_SSIZE(0);
			DMA_DCR0 |= DMA_DCR_DSIZE(0);
		/* For Complete Words */
		#ifdef MEMMOVE
			DMA_DCR0 |= DMA_DCR_SINC_MASK;
		#endif

			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_EINT_MASK;

			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(49);
			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;

			initialize_counter();
			counter_start();

			DMA_DCR0 |= DMA_DCR_START_MASK;

		/* For Remaining Bytes which cannot form a Word */
			DMA_DSR_BCR0 = len1; // Setting length for remaining bytes to be transferred
			DMA_DCR0 |= DMA_DCR_SSIZE(1);
			DMA_DCR0 |= DMA_DCR_DSIZE(1);
		#ifdef MEMMOVE
			DMA_DCR0 |= DMA_DCR_SINC_MASK;
		#endif

			DMA_DCR0 |= DMA_DCR_DINC_MASK;
			DMA_DCR0 |= DMA_DCR_EINT_MASK;
			//NVIC->ISER[0] = 0x1;

			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(49);
			DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
			DMA_DCR0 |= DMA_DCR_START_MASK;
		}



}

void memmove_dma(void)
{
	#ifdef EIGHTBIT
		uint8_t src[5000];
		uint8_t dst[5000];
		uint32_t len=5000;

		dma8(src,dst,len);
		counter_stop();

	#endif
	#ifdef WORDS
		uint32_t src[1200];
		uint32_t dst[1250];
		uint32_t len=5000;

		dma32(src,dst,len);
		//counter_stop();

	#endif
}

void memzero_dma(void)
{
	#ifdef EIGHTBIT
		uint8_t arr1[1]={1};
		uint8_t memzero_1 = 0;
		uint8_t *a = &memzero_1;
		uint32_t len = 1;
		dma8(a,arr1,len);
		counter_stop();
	#endif

	#ifdef WORDS
		uint32_t arr1[1250];
		uint32_t memzero_1 = 0;
		uint32_t *a = &memzero_1;
		uint32_t len = 5000;
		dma8(a,arr1,len);
		//counter_stop();
	#endif
}

/*void DMA0_IRQHandler(void)
{
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;// Setting done bit after complete transfer to set interrupt off
	counter_stop();
}*/
