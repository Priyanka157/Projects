//USART2 configured as Tx and Rx

#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void USART2_Init(void);
int USART_write(int ch);
int USART_read(void);

int main(void)
{
	int n;
	char str[100];
	
	USART2_Init();
	
	printf("Hello from the other side \r \n");
	fprintf(stdout, "Test for stdout \r \n");
	fprintf(stderr, "Test for stderr \r \n");
	
	while(1)
	{
		printf("How old are you?");
		scanf("%d", &n);
		printf("Your age is : %d \r \n", n);
		printf("Enter your first name : ");
		gets(str);
		printf("I like your style: ");
		puts(str);
		printf("\r \n");
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
	//AFR[0] => AFRL (low register)
	GPIOA->AFR[0] |= 0x7700;
	
	//Set PA2 to alternate function
	//GPIO MODER: 10: For alternate function 
	//GPIOA->MODER |= 0x0020; 
	//Enable alternate function at PA3
	//GPIOA->MODER |= 0x80;
	//Combined together
	GPIOA->MODER |= 0xA0;
	
	//Configure USART 
	//First initialize and then enable the module
	//Baud rate register (USART_BRR)	
	//Baud rate: 9600 @16MHz
	USART2->BRR = 0x683; 
	
	//Control register 1 (USART_CR1): Bit 2 RE: Receiver enable(1)/ disable(0), Bit 3 TE: Transmitter enable(1)/ disable(0)
	//USART2->CR1 = 0x0008; 	
	//Enables PA3 as Rx
	//USART2->CR1 = 0x0004;
	//Combine together
	USART2->CR1 = 0x000C;
	
	//Enable USART module: Bit 13 UE: USART enable(1)/ disable(0)
	USART2->CR1 |= 0x2000;
}

//USART as a Tx 
int USART_write(int ch)
{
	//While the Tx buffer is empty, wait
	//USART_SR: Status Register: Bit 7 TXE: Transmit data register empty-Data transferred(1)/not transferred(0)
	//Loop is executed when the data is transferred
	while(!(USART2->SR & 0x0080)) {}
	USART2->DR = (ch & 0xFF);
	return ch;
}

//USART as a Rx
int USART_read(void)
{
	//Wait until character arrives
	while(!(USART2->SR & 0x20)) {}
	return (int)USART2->DR;
}

//Interface between embedded code and C standard I/O library
struct __FILE1{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

//Create fgetc() that echos the character received when Enter is hit and appends a new line
int fgetc(FILE *f)
{
	int c;
	c = USART_read();
	// \r inserts a carriage return in the text
	if(c == '\r')  
	{
		USART_write(c);
		c = '\n';
	}
	USART_write(c);
	
	return c;	
}

int fputc(int c, FILE *f)
{
	return USART_write(c);
}
