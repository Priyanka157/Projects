//Configure general purpose timer for input capture
//Purpose of input capture: Detect the occurence of an event or count the number of times an event occured 
//Configure TIM2 CH1 to toggle PA5 as output pin (LED toggle)
//Capture the toggle rate of PA5 by reading the reading the value of toggle pin PA5 into the PA6 which is the input capture pin

//Needs circuit to check results

#include "stm32f4xx.h"                  // Device header

int timeStamp = 0;

int main(void)
{
	RCC->AHB1ENR |= 1;
	//Set PA5 as alternate function
	GPIOA->MODER = 0x800; 
	//Set pin to AF1 for TIM2 CH1
	GPIOA->AFR[0] |= 0x00100000;
	
	//Configure TIM2 to 1 Hz
	RCC->APB1ENR |= 1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	//Set output to toggle on match
	TIM2->CCMR1 = 0x30;
	//Set the match value
	TIM2->CCR1 = 0;
	
	//Enable CH1 compare mode
	TIM2->CCER |= 1;
	//Clear the counter
	TIM2->CNT = 0;
	//Enable the timer TIM2
	TIM2->CR1 = 1;
	
	//Input capture mode
	//Configure PA6 as Input of TIM3 CH1 
	//Set PA6 to alternate function
	GPIOA->MODER |= 0x2000;
	//Set pin to AF2 for TIM3 CH1
	GPIOA->AFR[0] |= 0x02000000;
	
	//Configure TIM3
	RCC->APB1ENR |= 2;
	//Divide by 16000
	TIM3->PSC = 16000-1;
	//Set to capture compare mode
	//Set CH1 to capture at every edge
	TIM3->CCMR1 = 0x41;	
	//Set CH1 to capture at the rising edge
	//Enable capture mode
	TIM3->CCER = 1;
	//Enable TIM3
	TIM3->CR1 = 1;
	
	while(1)
	{
		while(!(TIM3->SR & 2)) {}
		timeStamp = TIM3->CCR1;
	}	
}
