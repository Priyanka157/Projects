//Program to blink user LED (LD2) in STM32F446RE (Nucleo Board)

#include "stm32f4xx.h"                  // Device header

//LED is connected to PA5 (Arduino pin convention: D13)
//GPIO Port A is connected to AHB1 bus
//Enable clock for this bus
//Set pin as an output:
//GPIOx_MODER (Mode Register): Direction register
//GPIOx_ODR (Output Data Register): Data register

void delayMS(int delay);
int main(void)
{
	//Enable GPIO A Clock => Enable clock of AHB1 bus
	//RCC (Reset and Clock Control register) AHB1 peripheral clock enable register (RCC_AHB1ENR) => GPIOAEN: Bit 0: must be set to 1
	//RCC is a structure and AHB1ENR is a member of that structure which can be accessed using ->
	//RCC->AHB1ENR = 1;     //This will diable other peripherals as other bits are set to 0. Even if these bits are changed later, that change will be overwritten by this statement.
	RCC->AHB1ENR |= 1;			//This sets only bit 0 to 1, rest bits remain unchanged.
	
	//Set PA5 mode as an output
	//Set Direction Register
	//MODER takes 2 bit as an input. 01: General purpose O/P mode. 
	//Address: 0000 0000 0000 00(PA9)00(PA8) 00(PA7)00(PA6) 01(PA5)00(PA4) 00(PA3)00(PA2) 00(PA1)00(PA0) : in short 0x400
	GPIOA->MODER |= 0x400;

	while(1) 
	{
		//Set Data Register
		//Set PA5 to high
		GPIOA->ODR = 0x20;    
		delayMS(100);
		//Set only PA5 to low
		GPIOA->ODR &=~0x20;   
		delayMS(100);
	}
}	

//Psedo-delay function
/*void delayMs(int delay)
{
	int i;
	for(; delay>0; delay--)
		for (i = 0; i<3195; i++);  //3195 experimentally derived value for 16 MHz processor, doesn't work for 8 MHz
}*/

void delayMS(int delay)
{
	//Delay of 1 ms
	//Reload with number of clock cycles/ms
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

