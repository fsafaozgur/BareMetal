#include "adc.h"


void adc_init(void)
{

    RCC->AHB2ENR |= (1u << 2);    	// Enable GPIOC clock
    GPIOC->MODER &= ~(3u << 0);  	// Clear PC0 mode
    GPIOC->MODER |=  (3u << 0);  	// Analog mode
    GPIOC->PUPDR &= ~(3u << 0);  	// No pull

    
    RCC->AHB2ENR |= (1u << 13);		// Enable ADC1 clock	

    // Ensure ADC is disabled
    if (ADC1->CR & (1u << 0)) {
        ADC1->CR |= (1u << 1);           // ADDIS is set to force stop
        while (ADC1->CR & (1u << 0));    // Wait until disabled
    }

/*
    // Calibration
    ADC1->CR &= ~(1u << 29);    	// Single-ended mode
    ADC1->CR |= (1u << 31);     	// ADCAL
    while (ADC1->CR & (1u << 31)); 	// Wait calibration end
*/

    
    ADC123_COMMON->CCR &= ~(0xFu << 18); //clear reg
    ADC123_COMMON->CCR |= (1u<<20);	 // ADC clock divided by 8 - Common Configuration


    // ADC Configuration
    ADC1->CFGR |= (1u << 13); 		// continuous mode
    ADC1->CFGR &= ~(3u << 3); 		// 12-bit resolution
    ADC1->CFGR &= ~(1u << 5); 		// align right

    ADC1->SMPR1 &= ~(7u << 3); 		// clear sampling time
    ADC1->SMPR1 |=  (2u << 3); 		// 56 cycles

    //ADC1->SQR1 &= ~(0x1F << 6); 	// Clear SQ1
    //ADC1->SQR1 |=  (1u << 6);  	// Channel 10 (PC0)
    //ADC1->SQR1 &= ~(15u << 0);  	// Only 1 conversion


    
    ADC1->SQR1 &= ~(0x1F << 6);  	// Clear SQ1
    ADC1->SQR1 |= (1u<<6);		//channel 1 is assigned to conversion1

    ADC1->SQR1 &= ~(0xFu<<0);	//only 1 conversion



    ADC1->IER |= (1u << 2); 		// End of conversion interrupt

    // NVIC
    __NVIC_SetPriority(ADC1_2_IRQn, 0);
    __NVIC_EnableIRQ(ADC1_2_IRQn);

    // Enable ADC
    ADC1->CR |= (1u << 0);      	// ADEN
    while (!(ADC1->ISR & (1u << 0)));   // Wait for ADRDY
    ADC1->CR |= (1<<2);			//Start conversion

}
