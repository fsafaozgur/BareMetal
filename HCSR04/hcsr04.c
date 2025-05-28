#include "hcsr04.h"


void HCSR04_Init(void)
{
	//trigger configuration
	RCC->AHB2ENR |= 1u;
	
	GPIOA->MODER &= ~(3u << 2);
	GPIOA->MODER |= (1u<<2);
	GPIOA ->OTYPER &= ~ (1u<<1);
	GPIOA->OSPEEDR &= ~(3u << 2);
	GPIOA->PUPDR &= ~(3u << 2);
	
	//echo configuration
	GPIOA->MODER &= ~(3u << 4);
	GPIOA->OSPEEDR &= ~(3u << 4);
	GPIOA->PUPDR &= ~(3u << 4);
	
	//timer configuration
	RCC->APB1ENR1 |= (1<<4);
	TIM6->PSC = 79;
	TIM6->ARR = 10;
	TIM6->CNT = 0;
}


uint16_t read_distance(void)
{
	uint16_t time = 0;

	while ( !((GPIOA->IDR) & (1<<2)) );

	while ( ((GPIOA->IDR) & (1<<2)) )
	{
		time++;
		wait_us(1);
	}

	return time;
}



void wait_us(uint16_t delay)
{
	uint16_t current = TIM6->CNT;
    	TIM6->CR1 |= 1;
	while ((TIM6->CNT - current) < delay);
	TIM6->CR1 &= ~(1<<0);
	TIM6->CNT = 0;
}

