#include "inc/tm4c123gh6pm.h"
#include "GPIOinit.h"
#include <stdbool.h>
#include <stdint.h>

// Inits for input from the joystick
// Make use of ADC0 and ADC1
// ADC0 - PE4, ADC1 - PD2
void ADC_Init(void) {
	// Activate clock for Port E and D and allow time to stabilize
	SYSCTL_RCGCGPIO_R |= 0x18;
	while((SYSCTL_RCGCGPIO_R & 0x18)==0){}	
		
	// PE4
	GPIO_PORTE_DIR_R &= ~0x10;  // Make input
	GPIO_PORTE_AFSEL_R |= 0x10; // Enable alternate function
	GPIO_PORTE_DEN_R &= ~0x10;  // Disable digital I/O
	GPIO_PORTE_AMSEL_R |= 0x10; // Enable analog functionality
		
	// PD2
	GPIO_PORTD_DIR_R &= ~0x6;  // Make input
	GPIO_PORTD_AFSEL_R |= 0x6; // Enable alternate function
	GPIO_PORTD_DEN_R &= ~0x6;  // Disable digital I/O
	GPIO_PORTD_AMSEL_R |= 0x6; // Enable analog functionality
	  
	// Activate ADC0 and ADC1 and allow time to stabilize
	SYSCTL_RCGCADC_R |= 0x3;  
	while((SYSCTL_RCGCADC_R & 0x3) == 0){}
	
	// ADC0
  ADC0_PC_R = 0x3;							// Configure for 250k samples/sec
  ADC0_SSPRI_R = 0x0123;        // Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;      // Disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // Seq3 is software trigger
	ADC0_SSMUX3_R = 9;            // Select channel 9 corresponding to PE4.
  ADC0_SSCTL3_R = 0x06;         // Set IE0 and END0 (do NOT set TS0).
  ADC0_ACTSS_R |= 0x0008;       // Enable sample sequencer 3 before we sample.
		
	// ADC1
	ADC1_PC_R = 0x3;              // Configure for 250k samples/sec
	ADC1_SSPRI_R = 0x0123;				// Sequencer 3 is highest priority
	ADC1_ACTSS_R &= ~0x0008;			// Disable sample sequencer 3
	ADC1_EMUX_R &= ~0xF000;				// Seq3 is software trigger
	ADC1_SSMUX3_R = 5;						// Select channel 5 corresponding to PD2
	ADC1_SSCTL3_R = 0x06;					// Set IE0 and END0
	ADC1_ACTSS_R |= 0x0008;				// Enable sample sequencer 3 before samples.
}

uint32_t ADC0_In(void){
	uint32_t v=0;	
	
	ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  v = ADC0_SSFIFO3_R&0xFFF;   		 // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
		
	return v;
} 

// Works in same way asd above function but with ADC1
uint32_t ADC1_In(void) {
	uint32_t v = 0;
	
	ADC1_PSSI_R = 0x0008;
	while ((ADC1_RIS_R & 0x08) == 0) {}
	v = ADC1_SSFIFO3_R & 0xFFF;
	ADC1_ISC_R = 0x0008;
		
	return v;	
}

// Output PB6 for servo
void PORTPB6_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x02;
	while ((SYSCTL_RCGCGPIO_R & 0x02) == 0);
	
	GPIO_PORTB_DIR_R |= 0x40;
	GPIO_PORTB_DEN_R |= 0x40;
	GPIO_PORTB_AFSEL_R &= ~0x40;
	GPIO_PORTB_AMSEL_R &= ~0x40;
}

// Output PB7 for servo
void PORTPB7_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x02;
	while ((SYSCTL_RCGCGPIO_R & 0x02) == 0);
	
	GPIO_PORTB_DIR_R |= 0x80;
	GPIO_PORTB_DEN_R |= 0x80;
	GPIO_PORTB_AFSEL_R &= ~0x80;
	GPIO_PORTB_AMSEL_R &= ~0x80;
}
