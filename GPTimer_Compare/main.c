//Configure timer to compare mode
//Configure Channel 1 of Timer 2 as compare mode to toggle an output every time the counter matches the value in CCR1 register
//CCR1 register checks the match value
//Output pin of Timer 2 Channel 1 is PA5, so set PA5 (connected to LED) to its alternate function
//Use compare mode to toggle the LED instead of LED outdut data register (ODR)
#include "stm32f4xx.h"                  // Device header

int main(void)
{
	//Enable the clock for GPIOA and the timer
	RCC->AHB1ENR |= 1;
	
	//Set PA5 to alternate function
	GPIOA->MODER |= 0x800; 
	
	//Set PA5 to AF1 (Alternate Function 1) and this corresponds to timer 2 channel 1 alternate function
	GPIOA->AFR[0] |= 0x00100000;  
	
	//Set 1 Hz frequency
	RCC->APB1ENR |= 1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	//Set output to toggle on match
	TIM2->CCMR1 = 0x30;
	//Set match mode
	TIM2->CCR1 = 0;	
	//Enable Channel 1 compare mode
	TIM2->CCER |= 1; 
	
	//Clear counter
	TIM2->CNT = 0;
	//Enable timer 2
	TIM2->CR1 = 1;
	
	while(1)
	{		
	}	
}
