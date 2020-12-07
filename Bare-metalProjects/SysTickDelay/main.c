//Delay function using SysTick Timer


#include "stm32f4xx.h"                  // Device header
void SysTick_delayMS(int delay);
int main(void)
{
	//Initialize LED
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
		
	while(1)
	{
		SysTick_delayMS(300);
		GPIOA->ODR ^= 0x20;
	}	
}	

void SysTick_delayMS(int delay)
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
