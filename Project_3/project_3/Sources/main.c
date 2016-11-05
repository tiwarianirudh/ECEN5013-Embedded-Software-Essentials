/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#define PROFILER

void init_DMA1(void);

void main()
{
 init_DMA1();
}

void init_DMA1(void)
{
	unsigned char src[10] = {0,1,2,3,4,5,6,7,8,9};
	unsigned char dst[10] = {1,0,0,0,0,0,0,0,0,0};

	double system_clock= 0.047;
	double time_elapsed1;
	double cpu_ticks;

		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

		DMAMUX0_CHCFG0 |= 0X00;
		DMA_SAR0 = (uint32_t)src;
		DMA_DAR0 = (uint32_t)dst;

		DMA_DSR_BCR0 |= 0x20u;

		DMA_DCR0 |= DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1);
		DMA_DCR0 |= DMA_DCR_SINC_MASK | DMA_DCR_DINC_MASK;

		DMAMUX0_CHCFG0 |= 0x49u;
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
		initialize_counter();
		  counter_start();

		  DMA_DCR0 |= DMA_DCR_START_MASK;

		  counter_stop();

		  cpu_ticks = TPM0->CNT;
		  time_elapsed1= cpu_ticks*system_clock;


 }


#ifdef PROFILER
//initializing profiler
  void initialize_counter()
  {

  SIM->SCGC6 = 0x01000000;       /* enable clock for TPM0 */
  SIM->SOPT2 |= 0x01000000; 	/*MCGFLLCLK as timer counter clock */
  TPM0->SC = 0x0;				/* Disabling timer during cocnfiguration */
  TPM0->MOD = 0x0000FFFF;
  TPM0->CNT = 0x0;
  TPM0->SC = 0X00000080;
  }

  void counter_start()
  {
  TPM0->CNT = 0x0;
  TPM0->SC = 0x00000008;
  }

  void counter_stop()
  {
  TPM0->SC = 0x0;
  }



#endif
