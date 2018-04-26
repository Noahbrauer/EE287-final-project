#include "PortE.h"
#include "SysTick.h"
#include "ADC0.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "Uart.h"
#include "stdio.h"
#include "string.h"

#define PE0 (*((volatile unsigned long*) 0x40024004))
#define PF0 (*((volatile unsigned long*) 0x40025004))
#define PF4 (*((volatile unsigned long*) 0x40025040))

int main(){
	volatile double TempValue;
	volatile double IRvalue;
	volatile double CelsiusTemperature;
	volatile double FahrenheitTemperature;
	volatile double TempVout;
	volatile double IRvout;
	uint32_t Ctemp, Ftemp;
	char smokeStatus[30] = "Interference detected!\r\n";
	
	SysTick_Init();
	InitConsole();
	SysTick_Wait0_1ms(100);
	printString("EE287 Final Project\r\n");
	printString("*****************************************************\r\n");
	printString("Analog Input: Smoke Detector and Temperature Sensing circuit\r\n");
	PortE_Init();
	PortF_Init();
	printString("Initialization Complete...\r\n");
	
	while(1){
		TempValue = ADC0_InSeq3_Temp();
		TempVout = ((TempValue)/4095)*3.3;
		CelsiusTemperature = ((1.5151*TempVout)/0.0225)-61.1111;
		FahrenheitTemperature = CelsiusTemperature *9/5 +32;
		Ctemp = (uint32_t) CelsiusTemperature;
		Ftemp = (uint32_t) FahrenheitTemperature;

		IRvalue = ADC0_InSeq3_IR();
		IRvout = ((IRvalue)/4095)*3.3;
		
		PrintTemps(Ctemp, Ftemp);

		if (IRvout < 2.9 || FahrenheitTemperature > 90){
			printString(smokeStatus);
			PE0 = 0x01;
			while (PF4 == 0x10) {
				PF0 = 0x01;
				SysTick_Wait0_1ms(2);
				PF0 = 0x00;
				SysTick_Wait0_1ms(2);
			}
			PE0 = 0x00;
		}
		
		SysTick_Wait0_1ms(10000);
		
	}
}

