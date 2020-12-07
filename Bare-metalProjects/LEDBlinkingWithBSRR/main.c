//Program to blink user LED (LD2) in STM32F446RE (Nucleo Board) using BSSR (Bit Set/Reset Register)

#include "stm32f4xx.h"                  // Device header

void delayMS (int delay);
int main (void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	while (1)
	{
		GPIOA->BSRR = 0x20;   //Sets PA5 high
		delayMS(100);
		
		GPIOA->BSRR = 0x200000;  //Sets PA5 low
		delayMS(100);
	}	
}

void delayMS(int delay)
{
	//Delay of 1 ms
	//Reload with number of clcok cycles/ms
	SysTick->LOAD = 8000-1;
	
	//Clear the current value register
	SysTick->VAL = 0;
	
	//Enable SysTick
	SysTick->CTRL = 5;
	
	for (int i = 0; i<delay; i++)
	{
		//Wait until the COUNT flag is set
		while ((SysTick->CTRL & 0x10000) == 0) {}
	}	
	SysTick->CTRL = 0;
}	


/*void delayMS(int delay)
{
	int i;
	for(; delay>0; delay--)
		for(i=0; i<3195; i++);
}	*/
