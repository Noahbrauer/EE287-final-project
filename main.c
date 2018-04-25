#include "PortE.h"
#include "SysTick.h"
#include "stdint.h"
#include "stdbool.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"

void PrintTemps (uint32_t TempC, uint32_t TempF);
uint32_t clkscalevalue = 6;
void InitConsole(void);

int main(){
	volatile double ADCvalue;
	volatile double CelsiusTemperature;
	volatile double FahrenheitTemperature;
	volatile double Vout;
	uint32_t Ctemp, Ftemp;
	unsigned int delay;
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
	InitConsole();
	UARTprintf("EE287 Final Project\n");
	UARTprintf("*****************************************************\n");
	UARTprintf("Analog Input: Temperature Sensor Circuit\n");
	PortE_Init();
	UARTprintf("Initialization Complete...\n");
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_DIR_R |= 0x04;
	GPIO_PORTF_AFSEL_R &= ~0x04;
	GPIO_PORTF_DEN_R |= 0x04;
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFF0FF) + 0x00000000;
	GPIO_PORTF_AMSEL_R = 0;
	while(1){
		ADCvalue = ADC0_InSeq3();
		Vout = ((ADCvalue)/4095)*3.3;
		CelsiusTemperature = (Vout/0.0225)-61.1111;
		FahrenheitTemperature = CelsiusTemperature*1.8 + 32;
		Ctemp = (uint32_t) CelsiusTemperature;
		Ftemp = (uint32_t) FahrenheitTemperature;
		PrintTemps(Ctemp, Ftemp);
		SysCtlDelay(SysCtlClockGet() / clkscalevalue);
	}
}

void PrintTemps (uint32_t TempC, uint32_t TempF)
{
	UARTprintf("Temperature = %3d*C\n", TempC);	
	UARTprintf("Temperature = %3d*F\n", TempF);	
	UARTprintf("---------------------\n");
}

void InitConsole(void)
{
    // Enable GPIO port A which is used for UART0 pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for UART0 functions on port A0 and A1.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
   

		// Select the alternate (UART) function for these pins.   
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for console I/O. 9600 BAUD
    UARTStdioConfig(0, 9600, 16000000);
		
		 SYSCTL_RCGC1_R |= 0x00000002;
		
}

void UARTprintf(const char *pcString, ...)
{
    va_list vaArgP;

    //
    // Start the varargs processing.
    //
    va_start(vaArgP, pcString);

    UARTvprintf(pcString, vaArgP);

    //
    // We're finished with the varargs now.
    //
    va_end(vaArgP);
}