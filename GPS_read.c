#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#define M_PI 3.1415926
void SystemInit();
char wait_and_read(){
    while ((UART0_FR_R & 0x10) != 0);
    return UART0_Receive();
}
void readGPSModule(double* resultarr){
    char c0,GPSValues[100],parseValue[12][20],*token;
    double latitude=0.0,longitude=0.0,seconds=0.0,result1=0.0,minutes=0.0,result2=0.0;
    const char comma[2] = ",";
    int index=0,degrees;


    while ((UART0_FR_R & 0x10) != 0);
    c0=UART0_Receive();

    if(c0=='$'){
        char c1 = wait_and_read();
        if(c1=='G'){
            char c2 = wait_and_read();
            if(c2=='P'){
                char c3 = wait_and_read();
                if(c3=='R'){
                    char c4 = wait_and_read();
                    if(c4=='M'){
                        char c5 = wait_and_read();
                        if(c5=='C'){
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


                                if(strcmp(parseValue[1],"A")==0){
                                    latitude=atof(parseValue[2]);
                                    longitude=atof(parseValue[4]);


                                    degrees=latitude/100;
                                    minutes=latitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result1=degrees+seconds;
                                    //sprintf(latitudeResult,"%f", result);


                                    degrees=longitude/100;
                                    minutes=longitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result2=degrees+seconds;
                                    resultarr[0]=result1;
                                    resultarr[1]=result2;
                                }
                            }   
                        }
                    }
                }
            }
        }
    }
}
double toRadians(const double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
double distance(double lat1,double long1,double lat2,double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
		double dlong,dlat,ans,R;
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    dlong = long2 - long1;
    dlat = lat2 - lat1;

    ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    R = 6371;
    ans = ans * R;

    return ans;
}

