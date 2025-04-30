#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"

// In this file you should insert your code from the previous lab


// Initialize UART0
// Assumes 16 MHz clock, creates 9600 baud rate
void InitConsole(void){
		SYSCTL_RCGC1_R |= 0x1; // Enable UART0
		SYSCTL_RCGC2_R |= 0x1; // Enable PortA clk
		UART0_CTL_R &= ~0x1;   // Disable UART0
	
		// Setting buad rate
		UART0_IBRD_R = 104;
		UART0_FBRD_R =  11;
	
		UART0_LCRH_R = 0x70; // 8 bits of data, no parity, one stop bit, FIFO
	
		// Set up PA0 and PA1 for UART
		GPIO_PORTA_AFSEL_R |= 0x3;
		GPIO_PORTA_PCTL_R &= (GPIO_PORTA_PCTL_R & ~0xFF) | 0x11;
		GPIO_PORTA_AMSEL_R &= ~0x3;
		GPIO_PORTA_DEN_R |= 0x3; 
	
		UART0_CTL_R |= 0x1;  // Enable UART0
		
		UARTStdioConfig(0, 9600, 16000000);
}

// Should block until the user presses a key and then returns that value
// Returns a newline until it has been correctly implemented
unsigned char myGetChar(void){
		while ((UART0_FR_R & 0x10) != 0);
		return (unsigned char)(UART0_DR_R & 0xFF);
}
