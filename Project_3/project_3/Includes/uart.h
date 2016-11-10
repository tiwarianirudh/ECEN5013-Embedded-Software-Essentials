//header file for UART
#ifndef __UART_H_
#define __UART_H_
#include "cbuff.h"

void UART0_init(void);
void send_char(char c);
void send_string(char s[]);
void delayMs(int n);

cb_t txbuffer,rxbuffer;


#endif
