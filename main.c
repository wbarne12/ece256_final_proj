#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "lab7.h"
#include "systick.h"
#include "GPIOinit.h"

void SysTick_Init(void);
void Delay_1ms(void);
void InitConsole(void);
void ADC_Init(void);
void Delay_ms(uint32_t delay);
uint32_t ADC0_In(void);
uint32_t ADC1_In(void);

// **********************************************
// JOYSTICK X AXIS IS ADC0/PE4
// JOYSTICK Y AXIS IS ADC1/PD2
//***********************************************

// Returns a value in MICRO seconds
uint32_t rawADC_to_us(uint32_t raw) {
	uint32_t scaled = raw * 1000u;
	uint32_t fraction = (scaled + 2074u) / 4095u;
	return fraction + 1000u;
}

int main(void) {
	InitConsole();
	UARTprintf("UART init complete.\n");
	SysTick_Init();
	UARTprintf("Systick init complete.\n");
	ADC_Init();
	UARTprintf("ADC init complete\n");
	UARTprintf("All inits complete, ready to go!\n");
	
	while (1) {
		UARTprintf("Input x ADC0: %d\n", rawADC_to_us(ADC0_In()));
		UARTprintf("Input y ADC1: %d\n", rawADC_to_us(ADC1_In()));
		// 1 second delay
		for (int i = 0; i < 100; i++) {
			Delay_ms(10);
		}
	} 
}