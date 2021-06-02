#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "7-Segment-LED.h"
void SystemInit();
void sevensegment(int distance)
{
	int x,y,z,y2;
	char x1,y1,z1;
	x=distance%10;
	y=((distance%100)-x)/10;
	y2=distance%100;
	z=(distance-y2)/100;

	SEVENSEGMENT_Write_Units(x);
	SEVENSEGMENT_Write_Tens(y);
	SEVENSEGMENT_Write_Hundreds(z);
}
