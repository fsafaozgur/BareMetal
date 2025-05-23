#include "usart_dma.h"


void Usart_init(void)
{
	/*********gpio_init*********/
	RCC->AHB2ENR |= (1u<<0);

	//pd5 pin for Tx
	GPIOA->MODER &= ~(3u<<4);	//Clear Moder bits
	GPIOA->MODER |= (2u<<4);	//Alternate Func
	GPIOA->OTYPER &= ~(1u<<2);   	//Push-Pull
	GPIOA->AFR[0] &= ~(0xF<<8); 	//Clear AFR bits
	GPIOA->AFR[0] |= (7u<<8);	//AF7 selected


	//pd6 pin for Rx
	GPIOA->MODER &= ~(3u<<6);	//Clear Moder bits
	GPIOA->MODER |= (2<<6);		//Alternate Func
	GPIOA->OTYPER &= ~(1u<<3);   	//Push-Pull
	GPIOA->AFR[0] &= ~(0xF<<12); 	//Clear AFR bits
	GPIOA->AFR[0] |= (7u<<12);	//AF7 selected


	/*********usart_init*********/
	RCC->APB1ENR1 |= (1u<<17);

	USART2->CR1 &= ~(1u<<12); 	//word length bit0
	USART2->CR1 &= ~(1u<<28);	//word length bit1

	USART2->CR1 &= ~(1u<<15);	//Oversampling16 selected
	USART2->CR1 &= ~(1u<<10);	//parity disabled

	//USART2->CR1 |= (1u<<5); 	//RXNEIE interrupt enabled
	//NVIC_EnableIRQ(USART2_IRQn);

	USART2->CR1 |= (1u<<3); 	//Transmitter enabled
	USART2->CR1 |= (1u<<2); 	//Receiver enabled
	USART2->CR2 &= ~(3u<<12);	//1 stop bit selected
	USART2->BRR = 0x208D;		//9600 Baud rate  selected (80000000 / 9600 = 0x208D)

	USART2->CR1 |= (1u<<0); 	//USART enabled

}

void DMA_init(void)
{

	//DMA configuration
	RCC->AHB1ENR |= (1u<<0);			//DMA clock enable
	USART2->CR3 |= (1u<<6);				//DMA enable for USART2
	DMA1_Channel6->CCR &= ~(3u<<10);		//MSIZE specified as 8 bit
	DMA1_Channel6->CCR &= ~(3u<<8);			//PSIZE specified as 8 bit
	DMA1_Channel6->CCR |= (1u<<7);			//Destination increment
	DMA1_Channel6->CCR &= ~(1u<<4);			//peripheral to memory
	DMA1_Channel6->CNDTR = 5;			//selected 5 bits to transfer
	DMA1_Channel6->CPAR = (uint32_t)&USART2->RDR;   //source address
	DMA1_Channel6->CMAR = (uint32_t)DMA_buffer;	//destination address

	DMA1_CSELR->CSELR &= ~(0xF << 20);		//clear channel6 selection bits
	DMA1_CSELR->CSELR |= (2u << 20);		//channel6 selection specified as "0010" to adjust as USART2_RX

	DMA1_Channel6->CCR |= (1u<<0);			//DMA enabled

}



void usart_send (char * str)
{
	while (*str)
	{
	  while ( !(USART2->ISR & (1u<<7)));
	  USART2->TDR = *str;
	  str++;
	  HAL_Delay(100);
	}

}