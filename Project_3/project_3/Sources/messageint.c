/*
 * messageint.c
 *
 *  Created on: Nov 4, 2016
 *      Author: Mukund Madhusudan Atre
 */
#include "MKL25Z4.h"
#include <stdint.h>
#include <string.h>
#include "messageint.h"
#include "uart.h"
#include "pwm.h"
#include "cbuff.h"


void Decode_CI_Msg(CI_Msg_t *pkt)
{
	  if (pkt->command == RED_LED)
	  {
		    if (pkt->data[0] == LOW)
		    {
	          LEDFunction(RED, 150);
		    }
		    else if (pkt->data[0] == MEDIUM)
		    {
	          LEDFunction(RED, 600);
		    }
		    else if (pkt->data[0] == HIGH)
		    {
	          LEDFunction(RED, 900);
		    }

	  }

	  else if (pkt->command == GREEN_LED)
	  {
		    if (pkt->data[0] == LOW)
		    {
	        LEDFunction(GREEN, 150);
		    }
		    else if (pkt->data[0] == MEDIUM)
		    {
	        LEDFunction(GREEN, 600);
		    }
		    else if (pkt->data[0] == HIGH)
		    {
	        LEDFunction(GREEN, 900);
		    }

	  }

	  else if (pkt->command == BLUE_LED)
	  {
	    if (pkt->data[0] == LOW)
		{
	      LEDFunction(BLUE, 150);
		}
		else if (pkt->data[0] == MEDIUM)
		{
	      LEDFunction(BLUE, 600);
		}
		else if (pkt->data[0] == HIGH)
		{
	      LEDFunction(BLUE, 900);
		}
	  }

}

void message_map(CI_Msg_t *pkt)
{
    remove_item(&rxbuffer,&(pkt->command));
    remove_item(&rxbuffer,&(pkt->length));
	uint8_t i;

	if(pkt->length != 0)
	{
		for(i=0;i<(pkt->length);i++)
		{
			remove_item(&rxbuffer, &(pkt->data[i]));
		}
	}

	remove_item(&rxbuffer, &(pkt->checksum));

}
