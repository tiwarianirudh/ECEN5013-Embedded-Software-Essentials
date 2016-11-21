//UART0 initialization and addressing
#include "MKL25Z4.h"
#include <stdint.h>
#include "uart.h"


void UART0_init(void)
{
	SIM->SCGC4 |= 0x0400;
	SIM->SCGC5 = 0x0200;
	SIM->SOPT2 |= 0x04000000;

	PORTA->PCR[1] = 0x0200;
	PORTA->PCR[2]= 0x0200;

	UART0_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	UART0_C1_REG(UART0_BASE_PTR)=0x00;

	UART0->BDH = 0x00;
	UART0->BDL = 0x17;

	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn,2);


	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
    UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
	UART0->C1 = 0x00;

}
/*void UART0_tx()
	{
		UART0->C2 = 0x08;

		SIM->SCGC5 = 0x0200;
		PORTA->PCR[2]= 0x0200;
	}

void UART0_rx()
{

	UART0->C2 = 0x24;
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn,1);
	SIM->SCGC5 |= 0x0200;
	PORTA->PCR[1] = 0x0200;

}*/

/*uint8_t rx_data()
{
	uint8_t c;
	while(!(UART0->S1 & 0x20))	{}
	c = UART0->D;
	return c;
}*/

void UART0_IRQHandler(void){
	__asm("cpsid i");
	if((UART0_S1 & UART_S1_TDRE_MASK) && !(Empty(&txbuffer))){
		remove_item(&txbuffer, &UART0_D);

		if(Empty(&txbuffer))
			UART0_C2 &= ~UART_C2_TIE_MASK;
	}

	if((UART0_S1 & UART_S1_RDRF_MASK) && !(Full(&rxbuffer))){
		add_item(&rxbuffer,(uint8_t)UART0_D);

		if(Full(&rxbuffer))
			UART0_C2 &= ~UART_C2_RIE_MASK;
	}
	__asm("cpsie i");
}



void send_char(char c)
	{
	while(!(UART0_S1 & 0x80)) {

	    }
        UART0->D = c;
	}

void send_string(char s[])
{
		int i=0;

		while (s[i] != 0x00)
		{
			send_char(s[i]);
			i++;
		}

}

void delayMs(int n)
{
	int i;
	int j;
	for (i=0;i<n;i++)
	for (j=0;j<n;j++)
	{
	}

}

