#include "SysTick.h"
#include "PortE.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

void SysTick_Init(void){
	//Initialize Systick with interrupts every 1 ms
	//Initialize Systick
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 15999;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x05;
}

void SysTick_Wait(void) {
	NVIC_ST_RELOAD_R = 1600;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x000100000) == 0){
	}
}

void SysTick_Wait0_1ms(unsigned long period){
	unsigned long i;
	for (i = 0; i < period; i++){
		SysTick_Wait();
	}
}
	
	
