#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "systick.h"
#include "GPS_read.h"
#include "displacement.h"
#include "UART.h"
#include "LED_Config.h"
#include "7-Segment-LED.h"
#define CPAC (*((volatile uint32_t *)0xE000ED88))

void SystemInit () {
CPAC |= 0X00F00000;
}
double get_reading(double* reading1, double* reading2, int* count){
	double current_distance = -1;	
	if(*count == 0){
			if (readGPSModule(reading1)){
				current_distance = 0;
				*count=*count+1;
		}
	}
		else if(*count == 1){
			if (readGPSModule(reading2)){
				current_distance = distance(reading1[0],reading1[1], reading2[0], reading2[1]);
				*count=*count+1;
			}
		}
		else{
			double temp1 = reading1[0],temp2 = reading1[1];
			reading1[0] = reading2[0];
			reading1[1] = reading2[1]; 
			if(readGPSModule(reading2))
				current_distance = distance(reading1[0], reading1[1], reading2[0], reading2[1]);
			else{
				reading2[0] = reading1[0]; reading2[1] = reading1[1];
				reading1[0] = temp1; reading1[1] = temp2;
			}
		}
		return current_distance;
}
int main(){

	
	double distance, reading1[2], reading2[2], current_distance = 0;
	int count = 0;
	SEVENSEGMENT_Init();
	SEVENSEGMENT_Write_Units(0);
	SEVENSEGMENT_Write_Tens(0);
	SEVENSEGMENT_Write_Hundreds(0);
	systick_Init();
	systick_delay(1000);
	UART2_Init();
	UART0_Init();
	RGBLED_Init();
	RGBLED_Write(0x02);
	while(1){
		distance = get_reading(reading1, reading2, &count);
		if (distance < 0){
			continue;
		}
		if (distance > 0.01)
			current_distance += distance;
		
		if (count > 1){
			//RGBLED_Write(0x04);
			sevensegment((uint32_t)current_distance);
		}
		if(current_distance >= 100){
			RGBLED_Write(0x04);
		} 
	}
	//return 0;
}