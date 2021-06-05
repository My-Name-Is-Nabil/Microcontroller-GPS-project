#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "systick.h"
#include "GPS_read.h"
#include "displacement.h"
#include "UART.h"
#include "LED_Config.h"
#include "7-Segment-LED.h"

void SystemInit(){}
double get_reading(double* reading1, double* reading2, int* count){
	double current_distance;	
	if(*count == 0){
			readGPSModule(reading1);
			*count++;
		}
		else if(*count == 1){
			readGPSModule(reading2);
			current_distance = distance(reading1[0],reading1[1], reading2[0], reading2[1]);
			*count++;
		}
		else{
			reading1[0] = reading2[0];
			reading1[1] = reading2[1]; 
			readGPSModule(reading2);
			current_distance = distance(reading1[0], reading1[1], reading2[0], reading2[1]);
		}
		return current_distance;
}
int main(){
	double reading1[2], reading2[2], current_distance = 0;
	int count = 0;
	SEVENSEGMENT_Init();
	SEVENSEGMENT_Write_Units(0);
	SEVENSEGMENT_Write_Tens(0);
	SEVENSEGMENT_Write_Hundreds(0);
	UART2_Init();	
	RGBLED_Init();
	RGBLED_Write(0x02);
	while(1){
		current_distance += get_reading(reading1, reading2, &count);
		if (count != 0){
			sevensegment((int)current_distance);
		}
		if(current_distance >= 100){
			RGBLED_Write(0x04);
		} 
	}
	return 0;
}