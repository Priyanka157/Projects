//Generate a delay of 100ms using SYSTick timer. LED used to deisplay the delay.

#include "stm32f4xx.h"                  // Device header

int main(void)
{
	//Enable clock for Port A
	RCC->AHB1ENR |= 1;
	
	//Set PA5 as output
	GPIOA->MODER |= 0x400;
	
	//Configure SYSTick
	//For delay of 200ms at 8 MHz
	//SysTick->LOAD = 1600000-1;
	
	//For delay of 100ms at 8 MHz
	SysTick->LOAD = 800000-1;
	SysTick->VAL = 0;
	
	//Enable SysTick
	SysTick->CTRL = 5;
	
	//Toggle LED
	while(1)
	{
		//Check if count flag is set
		if(SysTick->CTRL & 0x10000)
		{
			GPIOA->ODR ^= 0x20; //Toggle LED
		}
	}
}
