#include "PortE.h"
#include "SysTick.h"
#include "ADC0.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "Uart.h"

#define PE0 (*((volatile unsigned long*) 0x40024004))
#define PF4 (*((volatile unsigned long*) 0x40025040))

int main(){
	volatile double TempValue;
	volatile double IRvalue;
	volatile double CelsiusTemperature;
	volatile double FahrenheitTemperature;
	volatile double TempVout;
	volatile double IRvout;
	uint32_t Ctemp, Ftemp;

	SysTick_Init();
	InitConsole();
	printString("EE287 Final Project\n");
	printString("*****************************************************\n");
	printString("Analog Input: Smoke Detector and Temperature Sensing circuit\n");
	PortE_Init();
	PortF_Init();
	printString("Initialization Complete...\n");

		
	while(1){
		TempValue = ADC0_InSeq3_Temp();
		TempVout = ((TempValue)/4095)*3.3;
		CelsiusTemperature = ((1.5151*TempVout)/0.0225)-61.1111;
		FahrenheitTemperature = CelsiusTemperature *9/5 +32;
		Ctemp = (uint32_t) CelsiusTemperature;
		Ftemp = (uint32_t) FahrenheitTemperature;

		IRvalue = ADC0_InSeq3_IR();
		IRvout = ((IRvalue)/4095)*3.3;

		if (IRvout < 2.6 || FahrenheitTemperature > 90){
			PE0 = 0x01;
			while (PF4 == 0x10) {
			}
			PE0 = 0x00;
		}
		
		PrintTemps(Ctemp, Ftemp);
		SysTick_Wait0_1ms(10);
		
	}
}

