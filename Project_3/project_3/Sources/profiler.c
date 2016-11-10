/*
 * profiler.c
 *
 *  Created on: Nov 4, 2016
 *      Author: Anirudh Tiwari
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

  __enable_irq(); //Global Interrupt
  NVIC_EnableIRQ(TPM0_IRQn); //NVIC interrupt Enable
  NVIC_SetPriority(TPM0_IRQn,1);
  TPM0_SC |= TPM_SC_TOIE_MASK; //Timer Overflow interrupt

  }

  void counter_start()
  {
  TPM0->CNT = 0x0;
  TPM0->SC = 0x00000008;

  }

  void counter_stop()
  {
    double system_clock= 0.047;
  	double time_elapsed1;
	double cpu_ticks;

	TPM0->SC = 0x0;
	cpu_ticks = TPM0->CNT;
	time_elapsed1= cpu_ticks*system_clock;
  }

  /*void TPM0_IRQHandler()
  {
  	if(TPM0_SC & TPM_SC_TOF_MASK)
  	{
  		TPM0_SC |= TPM_SC_TOF_MASK;
  		count++;
  	}
  }*/
