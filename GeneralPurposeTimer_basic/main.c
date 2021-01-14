//Timer to create a 1 second delay, that is, create a 1 Hz timer to toggle the LED
//General purpose Timer 2 (32-bit) is used which is connected to APB1 so its corresponding bit must be enabled

#include "stm32f4xx.h"                  // Device header

int main(void)
{
	//Initialize GPIO Port A for LED
	RCC->AHB1ENR |= 1;     
  //Initialize GPIO Port A pin 5 to Output mode	
	GPIOA->MODER |= 0x400;  
	
	//Timer configuration
	//Enable clock for APB1 bus
	RCC->APB1ENR |= 1;            
	
	//System clock runs at 16 MHz. To get 1 Hz divide by 16,000,000. 
	//Since prescaler is 16 bit the largest value it can hold is about 65,000 so division is done in 2 steps.
	//First divide by 1600, then use auto-reload to divide by 10,000
	//Divide 16,000,000 by 1600 = 10000 and -1 because count starts from 0
	TIM2->PSC = 1600-1;  
	//ARR- Autoreload register
	//10000 divided by 10000 = 1
	TIM2->ARR = 10000-1;
	//Clear the timer counter using CNT (Count) Register
	TIM2->CNT = 0;
	//Enable the timer by writing 1 to the timer control register
	TIM2->CR1 = 1;
	
	while(1)
	{
		while(!(TIM2->SR &1)) {}  //Wait to check if the timer flag is set
		TIM2->SR &=~1;
		GPIOA->ODR ^= 0x20;   //Toggles LED
	}
}	
