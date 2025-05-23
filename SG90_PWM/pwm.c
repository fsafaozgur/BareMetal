#include "pwm.h"


void PWM_GPIO_Init(void)
{
	RCC->AHB2ENR |= (1 << 0);
	GPIOA->MODER &= ~(3 << 0);   						// Clear MODER0[1:0]
	GPIOA->MODER |=  (2 << 0);   						// Set to Alternate Function (10)
	GPIOA->OTYPER &= ~ (1 << 0);
	GPIOA->OSPEEDR &= ~ (3 << 0);
	GPIOA->PUPDR &= ~ (3 << 0);
	GPIOA->AFR[0] &= ~(0xF << (0 * 4));     // Clear bits
	GPIOA->AFR[0] |=  (1   << (0 * 4));     // AF1 for TIM2_CH1
}


void PWM_Init(void)
{
	RCC->APB1ENR1 |= (1 << 0);
	TIM2->PSC = 79;
	TIM2->ARR = 19999;						// 50 Hz freq
	TIM2->CCMR1 &= ~(7 << 4);     // Clear OC1M bits
	TIM2->CCMR1 |=  (6 << 4);     // Set PWM mode 1 (OC1M = 110)
	TIM2->CCMR1 |=  (1 << 3);     // Enable preload for CCR1
	TIM2->CCER |= (1 << 0);
	TIM2->CR1 |= (1 << 0);  			// Enable counter (CEN bit)
}
