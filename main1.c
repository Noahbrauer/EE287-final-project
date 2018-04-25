#include "PortE.h"
#include "SysTick.h"
#include "ADC0.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"

#define PE0 (*((volatile unsigned long*) 0x40024004))
#define PF4 (*((volatile unsigned long*) 0x40025040))
	
int main(){
	volatile double TempValue;
	volatile double IRvalue;
	volatile double CelsiusTemperature;
	volatile double FahrenheitTemperature;
	volatile double TempVout;
	volatile double IRvout;
	
	PortE_Init();
	PortF_Init();
	ADC0_Seq3Init();
	SysTick_Init();
		
	while(1){
		TempValue = ADC0_InSeq3_Temp();
		TempVout = ((TempValue)/4095)*3.3;
		CelsiusTemperature = ((1.5151*TempVout)/0.0225)-61.1111;
		FahrenheitTemperature = CelsiusTemperature *9/5 +32;
		
		IRvalue = ADC0_InSeq3_IR();
		IRvout = ((IRvalue)/4095)*3.3;
		
		if (IRvout < 2.6 || FahrenheitTemperature > 90){
			PE0 = 0x01;
			while (PF4 == 0x10) {
			}
			PE0 = 0x00;
		}
		
		SysTick_Wait100ms(10);
		
	}
}
