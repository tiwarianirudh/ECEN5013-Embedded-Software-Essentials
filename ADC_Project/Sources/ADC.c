#include "ADC.h"

uint32_t sensor_voltage(void){
	 uint32_t result;
     //while(1){
	 ADC0->SC1[0] = 0;           /* start conversion on channel 0 */
	 while(!(ADC0->SC1[0] & 0x80)) { } /* wait for COCO */
	 result = ADC0->R[0];        /* read conversion result and clear COCO flag */
	 log3("\n\nThe voltage is (mV):",result*0.00005035);
	 log0("\r");
	 delayMs(500);
     return result;

}

void ADC_initialize(void)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	ADC0_CFG1 |= (ADC_CFG1_MODE(3) | ADC_CFG1_ADIV(2));
	ADC0_SC1A  = ADC_SC1_ADCH(31); //Disable module
}


void delayMs(int32_t n) {
    int32_t i;
    int32_t j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 3000; j++) {}
}

void temp_out()
{

        uint32_t raw=0, len=0;
        float Vtemp=0,Temp=0,Temp1=0,Temp2=0,Tempf=0;

while(1){

    raw = sensor_voltage(); //storing 16-bit temperature value
    Vtemp = raw * 0.00000005035;  //Convert the ADC reading into voltage
    if (Vtemp >= 0.7012)    //Check for Hot or Cold Slope
    {
        Temp1 =Temp_conv (Vtemp,1.646) ;
        Temp = 25 - Temp1 ;      //Cold Slope
        //Tempf = ((Temp - 32)/1.8) ;  //F to C conversion
    }
    else
    {
        Temp2 = Temp_conv (Vtemp,1.769);
        Temp = 25 - Temp2 ;   //Hot Slope)
        //Tempf = ((Temp - 32)/1.8);  //F to C conversion
    }
    	 log3("\n The temperature is (Celsius) :", Temp);
    	 log0("\r");
    	 delayMs(500);
}
}

float Temp_conv(float a, float m)
{
    float b = (a-0.7012)/m;
    return b;
    }
