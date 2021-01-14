//Using Input Capture to measure the frequency and period of a signal
//Toggle LED by using Timer 2 Channel 1 and the frequency and period of toggle using input capture
//Signal cominug out at PA5 is captured at PA6
//Circuit : Connect PA5 and PA6 using jumper wires.

#include "stm32f4xx.h"                  // Device header

int period;
float frequency;

int main(void)
{
	
	int last_value = 0;
	int current_value = 0;
	
	RCC->AHB1ENR |= 1;
	//Select alternate function mode
	GPIOA->MODER |= 0x800;     
	//Set pin to AF1 for TIM2 CH1
	GPIOA->AFR[0] |= 0x00100000;
	
	//Initialize clock
	RCC->APB1ENR |= 1;
	//1 Hz timer
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	TIM2->CCMR1 = 0x30;
	TIM2->CCR1 = 0;
	TIM2->CCER |= 1;
	TIM2->CNT = 0;
	TIM2->CR1 = 1;
	
	GPIOA->MODER |= 0x2000;
	//Set pin to AF2 for TIM3 CH1
	GPIOA->AFR[0] |= 0x020000000;
	
	RCC->APB1ENR |= 2;
	//Divide by 16,000
	TIM3->PSC = 16000-1;
	TIM3->CCMR1 = 0x41;
	TIM3->CCER = 0x0B;
	TIM3->CR1 = 1;
	
	while(1)
	{
		//Waits until edge is captured
		while (!(TIM3->SR & 2)) {}
		current_value = TIM3->CCMR1;
		period = current_value - last_value;
		last_value = current_value;
		frequency = 1000.0f/period;
		last_value = current_value;
	}	
}
