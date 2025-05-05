#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "systick.h"


void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0x05;
}

// Makes a delay of delay ms
// Assuming running at 16 MHz
void Delay_ms(uint32_t delay){
	uint32_t cycles = delay * 16000 - 1;
	// If delay time is too large, it will brick the board
	if (cycles > 0x00FFFFFF) {
		cycles = 0x00FFFFFF;
	}
	
	NVIC_ST_RELOAD_R = cycles;
 	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){} // Wait for count flag
}

// Makes a delay of delay microseconds
// Assuming running at 16 MHz
void Delay_us(uint32_t delay) {
	uint32_t cycles = delay * 16 - 1;
	if (cycles > 0x00FFFFFF) {
		cycles = 0x00FFFFFF;
	}
	
	NVIC_ST_RELOAD_R = cycles;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){}  
}
