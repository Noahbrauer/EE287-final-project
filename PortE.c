#include "PortE.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"

void PortE_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_DIR_R &= ~0x04;
	GPIO_PORTE_AFSEL_R |= 0x04;
	GPIO_PORTE_DEN_R &= ~0x04;
	GPIO_PORTE_AMSEL_R |= 0x04;
	SYSCTL_RCGC0_R |= 0x00010000;
	delay = SYSCTL_RCGC2_R;
	SYSCTL_RCGC0_R &= ~0x00000300;
	ADC0_SSPRI_R =0x0123;
	ADC0_ACTSS_R &= ~0x0008;
	ADC0_EMUX_R &= ~0xF000;
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;
	ADC0_SSCTL3_R = 0x0006;
	ADC0_ACTSS_R |= 0x0008;
}
