//Program to setup UART communication between computer and microcontroller
//Rx: USART2, Tx:Host computer
//To test this code, a program such as tera term is needed so that it can write using the computer serial port.
//Blink the LED based on the character that is read at UART. LED is on as long as a button is pressed on the keyboard.

#include "stm32f4xx.h"                  // Device header

void USART_Init(void);
char USART_read(void);
void LED_play(int value);
void delayMS(int delay);

int main(void)
{
	//Enable clock to Port A for LED
	RCC->AHB1ENR |= 1;
	
	//Set pin as output
	GPIOA->MODER |= 0x400;
	
	char ch;	
	USART_Init();
	
	while(1)
	{
		ch = USART_read();
		LED_play(ch);
	}	
}

void USART_Init(void)
{
	//Enable GPIO Port A clock
	RCC->AHB1ENR |= 1;
	//Enable clock to USART2 
	RCC->APB1ENR |= 0x20000;
	
	//Enable alternate function of GPIO
	GPIOA->AFR[0] |= 0x7000;
	
	//Enable alternate function at PA3
	GPIOA->MODER |= 0x80;
	
	//Configure USART
	//Baud rate: 115200 baudrate @16MHz
	USART2->BRR = 0x008B; 
	
	//Enables PA3 as Rx
	USART2->CR1 = 0x0004; 
	
	//Enable USART module
	USART2->CR1 |= 0x2000;	
}

char USART_read(void)
{
	//Wait until character arrives
	while(!(USART2->SR & 0x20)) {}
	return (char)USART2->DR;
}

void LED_play(int value)
{
	value %= 16;
	for(; value>0; value--)
	{
		//Turn on LED
		GPIOA->BSRR = 0x20;  
		delayMS(100);
		
		//Turn off LED
		GPIOA->BSRR = 0x200000;
		delayMS(100);
	}
	delayMS(400);
}

/*void delayMS(int delay)
{
	int i;
	for(; delay>0; delay--)
		for(i=0; i<3195; i++);
}*/

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

