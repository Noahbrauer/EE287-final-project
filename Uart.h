#ifndef _Uart_h
#define _Uart_h

void InitConsole(void);
void PrintTemps (uint32_t TempC, uint32_t TempF);
unsigned char readChar (void);
void printChar (unsigned char c);
void printString (char* string);

#endif
