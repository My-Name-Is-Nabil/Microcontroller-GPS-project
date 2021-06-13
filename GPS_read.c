#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "systick.h"
#define M_PI 3.1415926

char wait_and_read(){
	 uint8_t data = UART2_Receive();
	 //systick_delay(1);
    //UART0_Send(data);
	 return data;
}
bool readGPSModule(double* resultarr){
    char c0,GPSValues[100],parseValue[14][20],*token;
    double latitude=0.0,longitude=0.0,seconds=0.0,result1=0.0,minutes=0.0,result2=0.0;
    const char comma[2] = ",";
    int index=0,degrees, i;


    c0=wait_and_read();

    if(c0=='$'){
        char c1 = wait_and_read();
        if(c1=='G'){
            char c2 = wait_and_read();
            if(c2=='P'){
                char c3 = wait_and_read();
                if(c3=='G'){
                    char c4 = wait_and_read();
                    if(c4=='G'){
                        char c5 = wait_and_read();
                        if(c5=='A'){
                            char c6 = wait_and_read();
                            if(c6==','){
                                char c7 = wait_and_read();

                                while(c7!='*'){
                                    GPSValues[index]=c7;
                                    c7 = wait_and_read();
                                    index++;
                                }
                                index=0;
                                token = strtok(GPSValues, comma);
                                while( token != NULL ) {
                                    strcpy(parseValue[index], token);
                                    token = strtok(NULL, comma);
                                    index++;
                                }
                                if (index < 7)
                                    return false;
                                latitude=atof(parseValue[1]);
                                longitude=atof(parseValue[3]);
                                for (i = 0; i < 20; i++){
                                    if ((parseValue[1][i] >= '0' && parseValue[1][i] <= '9') || parseValue[1][i] == '.'){
                                        UART0_Send(parseValue[1][i]);
                                    } else {
                                        break;
                                    }
                                }
                                UART0_Send('\n');
                                for (i = 0; i < 20; i++){
                                    if ((parseValue[3][i] >= '0' && parseValue[3][i] <= '9') || parseValue[3][i] == '.'){
                                        UART0_Send(parseValue[3][i]);
                                    } else {
                                        break;
                                    }
                                }
                                UART0_Send('\n');
                                degrees=latitude/100;
                                minutes=latitude-(double)(degrees*100);
                                seconds=minutes/60.00;
                                result1=degrees+seconds;


                                degrees=longitude/100;
                                minutes=longitude-(double)(degrees*100);
                                seconds=minutes/60.00;
                                result2=degrees+seconds;
                                resultarr[0]=result1;
                                resultarr[1]=result2;
                                return true;

                            }
                        }
                    }
                }
            }
        }
    }
		return false;
}
double toRadians(const double degree)
{
    double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
double distance(double lat1,double long1,double lat2,double long2)
{
    double dlong,dlat,ans,R;
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    dlong = long2 - long1;
    dlat = lat2 - lat1;
    ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    R = 6371;
    ans = ans * R;
    return ans*100;
}

