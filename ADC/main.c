#include "adc.h" 
#include "stm32l476xx.h"

uint16_t value=0;

int main(void)
{

  adc_init();

  while (1)
  {


  }

}


void ADC1_2_IRQHandler(void)
{
    if (ADC1->ISR & (1 << 2)) // EOC
    {
        ADC1->ISR |= (1 << 2); // Clear flag
        value = ADC1->DR;      // Read value
    }
}

