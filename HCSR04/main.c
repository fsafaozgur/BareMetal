#include "hcsr04.h" 
#include "stm32l476xx.h"

uint16_t distance=0;

int main(void)
{

  HCSR04_Init();

  while (1)
  {
		GPIOA->ODR |= (1<<1);				//trigger pin set
		wait_us(750);							//10us 
		GPIOA->ODR &= ~(1<<1);			//trigger pin reset

		distance = read_distance();	//read distance
		
		wait_us(3000);							//wait 
  }

}


