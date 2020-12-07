//Output not generated

//Program to setup UART communication between computer and microcontroller
//Tx: USART2, Rx:Host computer
//To test this code, a program such as tera term is needed so that it can read from the computer serial port.

//USART registers:
//Data register (USART_DR)
//Control register 2 (USART_CR2): Bit 9 CPHA: Cloack phase, Bit 10 CPOL: Clock polarity, Bit 12, 13 STOP: Define stop bits
//Control register 3 (USART_CR3): Enable flow control, Bit 4 NACK: Read and write negative acknowledgement

#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);
void USART_write(int ch);
void delayMS(int delay);

int main(void)
{
	USART2_Init();
	while(1)
	{
		USART_write('H');
		USART_write('I');
		USART_write('\r');  //Character return
		USART_write('\n');  //New line
		
		delayMS(10);
	}
}

void USART2_Init(void)
{
	//USART2 is connected to APB1 bus
	//RCC_APB1ENR: Bit 17 for USART2
	//Enable clock of bus for USART2	
	RCC->APB1ENR |= 0x20000;
	
	//USART2 Tx is connected to PA2, Rx to PA3
	//Enable clock of Port A
	RCC->AHB1ENR |= 1;
	
	//UART is a special purpose I/O so alternate function must be enabled
	//AF7 of AFRL => USART2 (AF bit 7)  ... Why not AFRH? It also has USART2
	//AFR[0] => AFRL (low register)
	//AFR[1] => AFRH (high register)
	//...How is the following address determined?
	GPIOA->AFR[0] = 0x0700;
	
	//Set PA2 to alternate function
	//GPIO MODER: 10: For alternate function 
	GPIOA->MODER |= 0x0020; 
	
	//Configure USART 
	//First initialize and then enable the module
	//Baud rate register (USART_BRR)	
	//Baud rate: 9600 @16MHz
	USART2->BRR = 0x0683; //0x008B; 
	
	//Control register 1 (USART_CR1): Bit 2 RE: Receiver enable(1)/ disable(0), Bit 3 TE: Transmitter enable(1)/ disable(0)
	USART2->CR1 = 0x0008; 
	
	//Enable USART module: Bit 13 UE: USART enable(1)/ disable(0)
	USART2->CR1 |= 0x2000;
}

void USART_write(int ch)
{
	//While the Tx buffer is empty, wait
	//USART_SR: Status Register: Bit 7 TXE: Transmit data register empty-Data transferred(1)/not transferred(0)
	//Loop is executed when the data is transferred
	while(!(USART2->SR & 0x0080))
	{
		USART2->DR = (ch & 0xFF);
	}
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
	SysTick->LOAD |= 8000-1;
	
	//Clear the current value register
	SysTick->VAL |= 0;
	
	//Enable SysTick
	SysTick->CTRL = 5;
	
	for (int i = 0; i<delay; i++)
	{
		//Wait until the COUNT flag is set
		while ((SysTick->CTRL & 0x10000) == 0) {}
	}	
	SysTick->CTRL = 0;
}

