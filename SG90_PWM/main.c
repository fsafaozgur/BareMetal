#include "pwm.h" 
#include "stm32l476xx.h"

int main(void)
{

  PWM_GPIO_Init();
  PWM_Init();

  while (1)
  {
		
	for(int i=500; i<2000; i=i+100)
	{
		TIM2->CCR1 = i;
		delay_ms(200);		//using increment in 1ms configured SysTick_Handler 
	}

  }

}


