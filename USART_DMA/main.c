#include "usart_dma.h" 
#include "stm32l476xx.h"

#define BUFFER_SIZE (5)

uint8_t buffer[BUFFER_SIZE];
uint8_t DMA_buffer[10];
uint8_t buffer_index=0;

int main(void)
{

  Usart_init();
  DMA_init();

  while (1)
  {

  }

}

