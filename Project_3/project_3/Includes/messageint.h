/*
 * messageint.h
 *
 *  Created on: Nov 4, 2016
 *      Author: Mukund Madhusudan Atre
 */

#ifndef INCLUDES_MESSAGEINT_H_
#define INCLUDES_MESSAGEINT_H_
#define MAX_DATA_SIZE 2
#include <stdint.h>


void Decode_CI_Msg();
void message_map();
typedef struct CI_Msg{
	uint8_t command;
	uint8_t length;
	uint8_t data[MAX_DATA_SIZE];
	uint8_t checksum;
} CI_Msg_t;

CI_Msg_t *pkt;


typedef enum ledcolor{
	RED_LED = 0x01,
	GREEN_LED = 0x02,
	BLUE_LED = 0x03,
}color_t;

typedef enum ledbright{
	LOW = 0x0A,
	MEDIUM = 0x0B,
	HIGH = 0x0C,
}brightness_t;
#endif
