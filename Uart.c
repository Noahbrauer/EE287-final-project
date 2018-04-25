#include "SysTick.h"
#include "stdint.h"
#include "Uart.h"
#include "tm4c123gh6pm.h"
#include "stdio.h"
#include "string.h"

const int STRING_SIZE = 200;
const int BUFFER_SIZE = 100;

void InitConsole(void)
{
  SYSCTL_RCGC1_R |= 0x0001; 	// activate UART0
	SYSCTL_RCGC2_R |= 0x0001; 	// activate port A
	UART0_CTL_R &= ~0x0001;		// disable UART
	UART0_IBRD_R = 104;			// IBRD=int(16000000/(16*9600)) = int(104.166)
	UART0_FBRD_R = 11;			// FBRD=int(0.166*64+0.5) = 11
	UART0_LCRH_R = 0x0070;		// 8-bit length, enable FIFO
	UART0_CTL_R = 0x301;		// Enable RXE, TXE and UART
	GPIO_PORTA_PCTL_R=(GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
	GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog on PA1-0
	GPIO_PORTA_AFSEL_R |= 0x03; // alt funct on PA1-0
	GPIO_PORTA_DEN_R |= 0x03; // digital I/O on PA1-0	
}

void PrintTemps(uint32_t TempC, uint32_t TempF)
{
	char TempCstr[STRING_SIZE] = "Temperature = ";
	char buffer[BUFFER_SIZE];
	sprintf(buffer, "%3d*C\r\n", TempC);
	strcat(TempCstr, buffer);

	char TempFstr[STRING_SIZE] = "Temperature = ";
	sprintf(buffer, "%3d*C\r\n", TempF);
	strcat(TempFstr, buffer);

	printString(TempCstr);	
	printString(TempFstr);	
	printString("---------------------\r\n");
}

//Wait for new input
//Return ASCII code
unsigned char readChar(void){
	while((UART0_FR_R & 0x0010) != 0);	// wait until RXFE is 0
	return ((unsigned char)(UART0_DR_R&0xFF));
}

// Wait for buffer to be not full,
// then output
void printChar(unsigned char data) {
	while((UART0_FR_R&0x0020) != 0){};		
	// wait until TXFF is 0
		UART0_DR_R = data;
}

void printString(char* string){
	while(*string){
		printChar(*(string++));
	}
}
