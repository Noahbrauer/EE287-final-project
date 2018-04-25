#include "ADC0.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

unsigned long ADC0_InSeq3_Temp(void){
	unsigned long result;
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R&0x08) == 0){};
	result = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R = 0x0008;
	return result;
}

unsigned long ADC0_InSeq3_IR(void){
	unsigned long result;
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+2;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R&0x08) == 0){};
	result = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R = 0x0008;
	return result;
}
