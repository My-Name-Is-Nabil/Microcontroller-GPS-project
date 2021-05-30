#include "7-Segment-LED.h"
#include "stdint.h"
#include "tm4c123gh6pm.h"
void SystemInit();
void SEVENSEGMENT_Init(void) {
	volatile unsigned long delay;
	// enable PORTB, PORTA clock.
	// PORTB -> writing the digit on one of the 7-segments.
	// PORTA -> select one of the 7-segments, (PA4: to enable unit digit, PA5: to enable tenth digit, PA6: to enable hundredth digit).
  SYSCTL_RCGCGPIO_R |= 0x03;
	
  delay = SYSCTL_RCGCGPIO_R; // Delay.
	
	// PORTB Initialization.
	// Unlock PORTB commit Register.
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  GPIO_PORTB_CR_R |= 0xFF;
	// Disable analog function.
  GPIO_PORTB_AMSEL_R &= ~0xFF;
	// GPIO clear bit PCTL.
  GPIO_PORTB_PCTL_R &= ~0x0000FFF0;
	// No alternate function.
  GPIO_PORTB_AFSEL_R &= ~0xFF;
	// The whole PORTB Direction is output.
  GPIO_PORTB_DIR_R |= 0xFF;
	// Enable digital pins for the whole PORTB.
  GPIO_PORTB_DEN_R |= 0xFF;
	// Clear PORTB data register.
  GPIO_PORTB_DATA_R &= ~0xFF;
	
	// PORTA Initialization (using PA4, PA5, PA6, PA7).
	// Unlock PortA commit Register.
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
  GPIO_PORTA_CR_R |= 0xFF;
	// Disable analog function for PA4, PA5, PA6,PA7
  GPIO_PORTA_AMSEL_R &= ~0x70;
	// GPIO clear bit PCTL.
  GPIO_PORTA_PCTL_R &= ~0x0000FFF0;
	// No alternate function for PA4, PA5, PA6,PA7
  GPIO_PORTA_AFSEL_R &= ~0xF0;
	// The PA4, PA5, PA6 are output.
  GPIO_PORTA_DIR_R |= 0xF0;
	// Enable digital pins for PA4, PA5, PA6, PA7
  GPIO_PORTA_DEN_R |= 0xF0;
	// Clear PORTA data register for PA4, PA5, PA6,PA7
  GPIO_PORTA_DATA_R &= ~0xF0;
}

void SEVENSEGMENT_Write_Units(int data) {
	// Reset the data register in PORTB.
	GPIO_PORTB_DATA_R &= ~0xFF;
  GPIO_PORTB_DATA_R |= data;
}
void SEVENSEGMENT_Write_Tens(int data) {
	data=data<<4;
  GPIO_PORTB_DATA_R |= data;
}
void SEVENSEGMENT_Write_Hundreds(int data) {
	GPIO_PORTA_DATA_R &= ~0xFF;
	data=data<<4;
  GPIO_PORTA_DATA_R |= data;
}