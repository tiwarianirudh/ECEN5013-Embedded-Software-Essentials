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
#include "log.h"
#include "timer.h"
#include "ADC.h"
#include "UART.h"
#include "LED.h"
#include "TSI.h"
#include "I2C.h"
#include "TSL2561.h"
#define TOUCH
#define LIGHT
#define TEMPERATURE

int main(void)
{
	uint16_t status,i;
	uint8_t color,bright;
	float lux;
	UART0_init();
	led_pwm_init();
	init_buff(&tx_buff,200);
	init_buff(&rx_buff,200);

	log0("Nothing in life is to be feared; it is only to be understood\n\r");
    log0("Welcome!\n\r");

#ifdef TEMPERATURE
    ADC_initialize();
    temp_out();
#endif

#ifdef TOUCH
    touch_init();
    log0("Place your finger on temeprature sensor to change brightness and color\n\r");
	while(1){
		status = scan_touch();
    	if (status<=110){
    	    color = BLUE;
    	    bright = status - 70;
    	}
    	else if (status>110 && status<=140){
    		color = CYAN;
    		bright = status - 100;
    	}
    	else if (status>140 && status<250){
    		color = MAGENTA;
    		bright = status - 145;
    	}
		LED_select(color,bright*30);
		log3("Touch data: ", status);
		log0("\n\r");
		delayMs(500);
	}
#endif

#ifdef LIGHT
	i2c_init();
	light_init();
	log0("Expose the light sensor to different lighting conditions");
	while(1){
		lux = get_lumin();
		log3("The lux value is",lux);
		log0("\n\r");
		LED_select(RED,lux*50);
		delayMs(500);

	}
#endif
    return 0;
}

