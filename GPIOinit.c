#include "inc/tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>

// Inits for input from the joystick
void ADC0_Init(void) {  
	SYSCTL_RCGCGPIO_R |= 0x10;    // 1) activate clock for Port E and allow time to stabilize
	while((SYSCTL_RCGCGPIO_R & 0x10)==0){}	
	SYSCTL_RCGCADC_R |= 0x01;		  // 2) activate clock for ADC0 and allow time to stabilize
	while ((SYSCTL_RCGCADC_R & 0x01)==0) {}
		
	GPIO_PORTE_AFSEL_R |= 0x0E;		// 3) Alt function on PE3, PE2, PE1
	GPIO_PORTE_AMSEL_R |= 0x0E;   // 4) Analog mode for PE3, PE2, PE1
	GPIO_PORTE_DEN_R &= 0x0E;     // 5) Disable digital IO for PE3-PE1
	
	ADC0_PC_R = 0x5;							// 6) 500k samples a second	
		
	// ADC0 SS3 (AIN0 - PE3)
	ADC0_ACTSS_R &= ~0x08;        // Disable SS3 during setup
	ADC0_EMUX_R &= ~0xF000;       // Seq3 is a software trigger
	ADC0_SSMUX3_R = 0;            // AIN0
	ADC0_SSCTL3_R = 0x06;    			// Set IE0 and EN0 (do not set TS0) HAHAHA it said TS lmao laughing
	ADC0_ACTSS_R |= 0x08; 				// Enable SS3
		
	// ADC0 SS2 (AIN1 - PE2)
	ADC0_ACTSS_R &= ~0x04;				// Disable SS2 during setup
	ADC0_EMUX_R &= ~0x0F00;				// Seq2 is software trigger
	ADC0_SSMUX2_R = 1;            // AIN1
	ADC0_SSCTL2_R = 0x06;    			// Set IE0 and EN0 (do not set TS0)
	ADC0_ACTSS_R |= 0x08;					// Enable SS2
		
	// ADC0 SS1 (AIN2 - PE1)
	ADC0_ACTSS_R &= ~0x02;				// Disable SS1 during setup
	ADC0_EMUX_R &= ~0x00F0; 			// Seq1 is software trigger
	ADC0_SSMUX1_R = 2;            // AIN2
	ADC0_SSCTL1_R = 0x06; 				// Set IE0 and EN0 (do not set TS0)
	ADC0_ACTSS_R |= 0x02;         // Enable SS1 
}

uint32_t AIN0_In(void) {
	uint32_t result;
	
	ADC0_PSSI_R = 0x08;
	while ((ADC0_RIS_R & 0x08) == 0) {}
	result = ADC0_SSFIFO3_R & 0xFFF;
	ADC0_ISC_R = 0x08;
		
	return result;
}

uint32_t AIN1_In(void) {
	uint32_t result;
	
	ADC0_PSSI_R = 0x04;
	while ((ADC0_RIS_R & 0x04) == 0) {}
	result = ADC0_SSFIFO2_R & 0xFFF;
	ADC0_ISC_R = 0x04;
		
	return result;
}

uint32_t AIN2_In(void) {
	uint32_t result;
	
	ADC0_PSSI_R = 0x02;
	while ((ADC0_RIS_R & 0x02) == 0) {}
	result = ADC0_SSFIFO1_R & 0xFFF;
	ADC0_ISC_R = 0x02;
		
	return result;
}