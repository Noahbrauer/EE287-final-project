#ifndef _SysTick_h
#define _SysTick_h

void SysTick_Init(void);
void SysTick_Wait(unsigned long period);
void SysTick_Wait0_1ms(unsigned long period);

#endif
