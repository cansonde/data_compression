#include <Arduino.h>
#include "api.hpp"
const int sizes[25] = {8,16,15,15,12,4,9,9,9,7,8,32,32,32,10,9,8,8,8,8,8,8,8,8,16};
unsigned int values[25];
String ret;
int CRC()
{
    return 0;
} 
// | const 8b | frame nr 16b | gps x-15b (map 15b, 16-20)  y-15b, (map 15b, 48-52) h-12b (raw) , meta-4b   | 
// |-20, 43 9b temp *3 (map 9b, -20, 40) | 7b hum (raw) | map(2.5-4.5,8b) bat voltage | 32b particle counter * 3 sizes 
//| pressure  (raw 9b off +500)| 8b * 6 gyro | 8b RSSI  (raw offset-164) | 8b state | 10b airflow | 16b CRC  
unsigned char pack=0;
int packsize=0;

void updatepack(bool bit)
{
    if(packsize>=7)
    {
        pack+=bit;
        ret+=String(pack);
        //cerr<<bitset<8>(pack)<<"\n";
        pack=0;
        packsize=0;
        return;
    }
    pack+=bit;
    pack*=2u;
    packsize++;
}
void send()
{
    values[0]='S';//|const 8b|

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < sizes[i]; j++)
        {
            updatepack((values[i] & (1<<j)));
        }
    }
    if(packsize>0) ret+=String(pack);
}

void getframe(API &api)
{
    // for (int i = 1; i < 25; i++)   
    // cin>>values[i];
    values[1] = ???;//framenr TODO
    api.gps_update();
    values[2] = api.gps_latitute();
    values[3] = api.gps_longitude();
    values[4] = api.gps_altitude();
    values[5] = api.gps_number_of_satellites();   
    values[6] = api.tmp_dht();
    values[7] = api.tmp_ds18();
    values[8] = api.tmp_thermistor(); //TODO thermistor temp
    values[9] = api.hum_dht();
    values[10] = api.bat_vol(); //TODO battery voltage
    //TODO particles
    values[11] =
    values[12] = 
    values[13] =
    //<><><><><><
    values[14] = api.bar_bmp();
    //TODO gyro
    values[15] = 
    values[16] = 
    values[17] = 
    
    values[18] = 
    values[19] = 
    values[20] = 

    values[21] = api.dbi(); //TODO dbi
    values[22] = api.state(); //TODO state
    values[23] = api.airflow();//TODO airflow
    values[24] = CRC(); 



    send();
    // int frameNr, X_gps, Y_gps, h_gps, meta, tempDHT11, tempDS18B20,  tempThermistor, humidity,
    // batteryVoltage,  smallParticles,  mediumParticles,  bigParticles, pressure;
    // int Xgyro, Ygyro, Zgyro, Xacceleration, Yacceleration, Zacceleration, dbi,  state;
    // int airflow,crc=0;
}
