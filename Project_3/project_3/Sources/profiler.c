/*
 * profiler.c
 *
 *  Created on: Nov 4, 2016
 *      Author: aniru
 */
//initializing profiler
#include "profiler.h"
#include "MKL25Z4.h"
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
