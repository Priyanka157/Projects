//Program to blink user LED (LD2) in STM32F446RE (Nucleo Board) using input from User Button
//User Button is connected to PC13
//LED is connected to PA5
//Port A and Port C is connected to AHB1 bus
//Working: When the button is pressed, LED turns on and remains on
//User Button is high by default, when pressed changes to low

#include "stm32f4xx.h"                  // Device header

int main (void)
{
	//Eable clock to both Port A and Port C
	RCC->AHB1ENR |= 4;	//Enables Port C
	RCC->AHB1ENR |= 1;  //Enables Port A
	
	//Mode register must be set to input and output
	GPIOA->MODER |= 0x400;  //Sets Output
	//GPIOA->MODER |= 0x00;   //Sets Input
	//By default a pin's mode is input so can skip it
	
	while (1)
	{
		//Read input from User Button
		//GPIOx_IDR (Input Data Register)=> It reads an input
		if(GPIOC->IDR & 0x2000)  //if true (PC13 is high), button is not pressed
		{
			//Why address as 0x002 and not 0x200000?
			//Functionality with following address: The LED turns on when the button is pressed, and remains on even when the button is released
			//This can be any address. Works with 0x1 and 0x003 as well.
			GPIOA->BSRR = 0x002;   //Turn off LED  //0x002 = 0x2
			//Functionality with following address: The LED turns on as long as the button is pressed, then turns off when the button is released
			//GPIOA->BSRR = 0x200000;   
		}
		else
		{
			GPIOA->BSRR = 0x20;  //Turn on LED 
		}	
	}
}	
