#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "7-Segment-LED.h"
void sevensegment(int distance)
{
	int x,y,z;
	x = distance%10;
	distance /= 10;
	y = distance%10;
	distance /= 10;
	z = distance%10;

	SEVENSEGMENT_Write_Units(x);
	SEVENSEGMENT_Write_Tens(y);
	SEVENSEGMENT_Write_Hundreds(z);
}
