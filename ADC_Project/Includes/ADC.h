#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

#include "MKL25Z4.h"
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "UART.h"
#include "log.h"
#include "circbuff.h"

uint32_t sensor_voltage(void);
void delayMs(int32_t n);
void ADC_initialize(void);
float Temp_conv (float a, float m);
void temp_out();


#endif /* INCLUDES_ADC_H_ */
