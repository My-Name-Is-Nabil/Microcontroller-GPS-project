#include "tm4c123gh6pm.h"
#include "stdint.h"

void UART0_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x01; //activate UART0
	SYSCTL_RCGCGPIO_R |= 0x01; //activate PORTA
	UART0_CTL_R &= ~0x01; //disable the UART
	//BaudRate = 9600 --> 80MHZ /(16*9600) = 520.8333
	UART0_IBRD_R = 520; //integer part = 520
	UART0_FBRD_R = 53; //fractional part = 0.8333*64 = 53
	UART0_LCRH_R = 0x70; //8-bit data, no parity, one stop, FIFo.s enabled
	UART0_CTL_R |= 0x01; //enable the UART
	GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlocking PORTA
	GPIO_PORTA_CR_R |= 0xFF;
	GPIO_PORTA_AFSEL_R |= 0x03; //enable alternate function for PA0 & PA1
	GPIO_PORTA_DEN_R |= 0x03; //configure PA0 & PA1 as digital I/O
	GPIO_PORTA_PCTL_R |= 0x011; //configure PA0 & PA1 as Tx & Rx of UART0
	GPIO_PORTA_AMSEL_R &= ~0x03; //disable analog on PA0 & PA1
}

uint8_t UART0_Receive(void)
{
	while ((UART0_FR_R & 0x10) != 0); //waiting for new input as long as FIFO is empty
	return UART0_DR_R; //read the received data
}

void UART0_Send(uint8_t data)
{
	while ((UART0_FR_R & 0x20) != 0); //waiting for FIFO to NOT be full
	UART0_DR_R = data;
}