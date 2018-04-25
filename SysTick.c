#include "SysTick.h"
#include "PortE.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

unsigned long ADC0_InSeq3(void){
	unsigned long result;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R&0x08) == 0){};
	result = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R = 0x0008;
	return result;
}


void SysTick_Init(void){
	//Initialize Systick with interrupts every 1 ms
	//Initialize Systick
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 15999;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | (0x40000000);
	NVIC_ST_CTRL_R = 0x07;
}