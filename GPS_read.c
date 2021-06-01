#include "stdint.h"
#include "tm4c123gh6pm.h"
void SystemInit();
double readGPSModule(void){
    char c0,GPSValues[100],latitudeResult[10],longitudeResult[10],parseValue[12][20],*token,tarih[9],*saat,guncelSaat[9];
    double latitude=0.0,longitude=0.0,seconds=0.0,result1=0.0,minutes=0.0,result2=0.0,resultarr[2];
    const char comma[2] = ",";
    int index=0,degrees,i=0,j=0;


    while ((UART0_FR_R & 0x10) != 0);
    c0=UART0_Receive();

    //gelen data $GPRMC mi?
    if(c0=='$'){
        while ((UART0_FR_R & 0x10) != 0);
        char c1=UART0_Receive();
        if(c1=='G'){
            while ((UART0_FR_R & 0x10) != 0);
            char c2=UART0_Receive();
            if(c2=='P'){
                while ((UART0_FR_R & 0x10) != 0);
                char c3=UART0_Receive();
                if(c3=='R'){
                    while ((UART0_FR_R & 0x10) != 0);
                    char c4=UART0_Receive();
                    if(c4=='M'){
                        while ((UART0_FR_R & 0x10) != 0);
                        char c5=UART0_Receive();
                        if(c5=='C'){
                            while ((UART0_FR_R & 0x10) != 0);
                            char c6=UART0_Receive();
                            if(c6==','){
                                while ((UART0_FR_R & 0x10) != 0);
                                char c7=UART0_Receive();

                                //verileri GPSValues arrayine atama.son veri olan checksum a kadar oku(checksum:A*60 gibi)
                                while(c7!='*'){
                                    GPSValues[index]=c7;
                                    while ((UART0_FR_R & 0x10) != 0);
                                    c7=UART0_Receive();
                                    index++;}


                                //GPSValues arrayindeki verileri virgul e gore ayirma
                                index=0;
                                token = strtok(GPSValues, comma);
                                while( token != NULL ) {
                                    strcpy(parseValue[index], token);
                                    token = strtok(NULL, comma);
                                    index++;}


                                //parseValue[1] = A ise veri gecerli - V ise gecerli degil
                                if(strcmp(parseValue[1],"A")==0){
                                    latitude=atof(parseValue[2]);
                                    longitude=atof(parseValue[4]);


                                    //latitude hesaplama
                                    degrees=latitude/100;
                                    minutes=latitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result1=degrees+seconds;
                                    //sprintf(latitudeResult,"%f", result);


                                    //longitude hesaplama
                                    degrees=longitude/100;
                                    minutes=longitude-(double)(degrees*100);
                                    seconds=minutes/60.00;
                                    result2=degrees+seconds;
                                    //sprintf(longitudeResult, "%f", result);
                                    resultarr[0]=result1;
                                    resultarr[1]=result2;
                        }}}}}}}
                        return resultarr;
}
double toRadians(const double °ree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}
double distance(double lat1,double long1,double lat2,double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    double dlong = long2 - long1;
    double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                          pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}
