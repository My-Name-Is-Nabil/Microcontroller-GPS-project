#include "LED_Config.h"

#include "stdint.h"
#include "tm4c123gh6pm.h"

void RGBLED_Init(void) {
	// Enabling PORTF Clock, to use for turning ON/OFF the LED.
  SYSCTL_RCGCGPIO_R |= 0x00000020;
	
	// Checking if PORTF is enabled
  while ((SYSCTL_PRGPIO_R & 0x0000020) == 0){}
	
	// PORTF Initialization.
	// Unlock PORTF Commit register.
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
	// Allow changes to PF1 (Red LED).
  GPIO_PORTF_CR_R |= 0x06;
	// Disable analog function for PF1 (Red LED).
  GPIO_PORTF_AMSEL_R &= ~0x06;
	// GPIO clear bit PCTL.
  GPIO_PORTF_PCTL_R = 0;
	// Disable alternate function for PF1 (Red LED).
  GPIO_PORTF_AFSEL_R = 0;
	// Direction of PF1 is output.
  GPIO_PORTF_DIR_R |= 0x06;
	// Enable digital pins for PF1 (Red LED).
  GPIO_PORTF_DEN_R |= 0x06;
	// Initialize PF1 (Red LED) to be OFF.
  GPIO_PORTF_DATA_R &= ~0x06;
}

void RGBLED_Write(uint8_t data) {
	// Reset PF1 in the data register (Turning OFF the Red LED).
	GPIO_PORTF_DATA_R &= ~0x06;
  GPIO_PORTF_DATA_R |= data;
}

uint8_t RGBLED_Read(void) {
	// Checking if the Red LED (PF1) is ON or OFF.
	return GPIO_PORTF_DATA_R & 0x20;
}

