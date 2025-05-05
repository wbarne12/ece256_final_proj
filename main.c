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
void PORTPB6_Init(void);
void servoDeg1(int);
void servoDeg2(int);
void servoDeg3(int);
int joystick_to_deg(int);
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
	UARTprintf("ADC init complete.\n");
	PORTPB6_Init();
	UARTprintf("PB6 Init complete.\n");
	PORTPB7_Init();
	UARTprintf("PC7 Init complete.\n");
	PORTPD0_Init();
	UARTprintf("PD0 Init complete.\n");
	
	while (1) {
		UARTprintf("raw adc val: %d\n",ADC0_In());

		int angle1 = joystick_to_deg(ADC0_In());
		servoDeg1(angle1);
		servoDeg3(angle1);
		
		int angle2 = joystick_to_deg(ADC1_In());
		servoDeg2(angle2);
	} 
}

//takes in a value 0-4095 from the joystick and sets the servo to a corisponding angle
int	joystick_to_deg(int num) {
		int deg = ((180*num)/4095);
		//UARTprintf("angle deg: %d\n",deg);
		return deg;
}

//takes in an intiger degree angle and sets the servo to that angle for port PB6
void servoDeg1(int deg) {
			int i = (2000/180)*deg + 500;
		
			GPIO_PORTB_DATA_R |= 0x40;
			Delay_us(i);
			GPIO_PORTB_DATA_R &= ~0x40;
			Delay_us(20000-i);
}

//takes in an intiger degree angle and sets the servo to that angle for port PB7
void servoDeg2(int deg) {
			int i = (2000/180)*deg + 500;
		
			GPIO_PORTB_DATA_R |= 0x80;
			Delay_us(i);
			GPIO_PORTB_DATA_R &= ~0x80;
			Delay_us(20000-i);
}

//takes in an intiger degree angle and sets the servo to that angle for port PD0
void servoDeg3(int deg) {
			deg = 180 - deg;
			int i = (2000/180)*deg + 500;
			GPIO_PORTB_DATA_R |= 0x08;
			Delay_us(i);
			GPIO_PORTB_DATA_R &= ~0x08;
			Delay_us(20000-i);
}