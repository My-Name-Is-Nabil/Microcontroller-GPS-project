#include "tm4c123gh6pm.h"
#include "stdint.h"

void UART0_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x01; //activate UART0
	SYSCTL_RCGCGPIO_R |= 0x01; //activate PORTA
	while ((SYSCTL_PRGPIO_R & 0x01) == 0);
	UART0_CTL_R &= ~0x301; //disable the UART
	//PC BaudRate = 9600 --> 16MHZ /(16*9600) = 104.1667
	UART0_IBRD_R = 104; //integer part = 104
	UART0_FBRD_R = 11; //fractional part = 0.1667*64 = 11
	UART0_LCRH_R = 0x70; //8-bit data, no parity, one stop, FIFo.s enabled
	UART0_CTL_R |= 0x301; //enable the UART, send, and receive
	//unlocking PORTA
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0xFF;
	GPIO_PORTA_AFSEL_R |= 0x03; //enable alternate function for PA0 & PA1
	GPIO_PORTA_DEN_R |= 0x03; //configure PA0 & PA1 as digital I/O
	GPIO_PORTA_PCTL_R |= 0x011; //configure PA0 & PA1 as Rx & Tx of UART0
	GPIO_PORTA_AMSEL_R &= ~0x03; //disable analog on PA0 & PA1
}
uint8_t UART0_Receive(void)
{
	uint8_t data;
	while ((UART0_FR_R & 0x10) != 0); //waiting for new input as long as FIFO is empty
	data = UART0_DR_R; //read the received data
	return data; //return the received data
}

void UART0_Send(uint8_t data)
{
	while ((UART0_FR_R & 0x20) != 0); //waiting for FIFO to NOT be full
	UART0_DR_R = data;
}

void UART0_DeInit(void)
{
	UART0_CTL_R &= ~0x01; //disable the UART
}



void UART2_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x04; //activate UART2
	SYSCTL_RCGCGPIO_R |= 0x08; //activate PORTD
	while ((SYSCTL_PRGPIO_R & 0x08) == 0);
	UART2_CTL_R &= ~0x301; //disable the UART
	//GPS BaudRate = 9600 --> 16MHZ /(16*9600) = 104.1667
	UART2_IBRD_R = 104; //integer part = 104
	UART2_FBRD_R = 11; //fractional part = 0.1667*64 = 11
	UART2_LCRH_R = 0x70; //8-bit data, no parity, one stop, FIFo.s enabled
	UART2_CTL_R |= 0x301; //enable the UART, send, and receive
	//unlocking PORTD
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R |= 0xFF;
	GPIO_PORTD_AFSEL_R |= 0xC0; //enable alternate function for PD6 & PD7
	GPIO_PORTD_DEN_R |= 0xC0; //configure PD6 & PD7 as digital I/O
	GPIO_PORTD_PCTL_R |= 0x11000000; //configure PD6 & PD7 as Rx & Tx of UART2
	GPIO_PORTD_AMSEL_R &= ~0xC0; //disable analog on PD6 & PD7
}

uint8_t UART2_Receive(void)
{
	uint8_t data;
	while ((UART2_FR_R & 0x10) != 0); //waiting for new input as long as FIFO is empty
	data = UART2_DR_R; //read the received data
	return data; //return the received data
}

void UART2_Send(uint8_t data)
{
	while ((UART2_FR_R & 0x20) != 0); //waiting for FIFO to NOT be full
	UART2_DR_R = data;
}

void UART2_DeInit(void)
{
	UART2_CTL_R &= ~0x01; //disable the UART
}
