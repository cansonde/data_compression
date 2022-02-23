#include<bits/stdc++.h>
using namespace std;
const int n=24;
int tab[n];
int main()
{
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        cin>>tab[i];
    }
    for (int i = 0; i < n; i++)
    {
        if(i==0)    tab[i]++;
        else if(i==9)   tab[i]=abs(-rand()%10+tab[i]);
        else if(i==14 && tab[i]>500)    tab[i]-=rand()%10;  
        else if(i>=10 && i<=12)  tab[i]+=rand()%100;
        else if(i==4)    tab[i]+=rand()%3-1;
        else
            tab[i]=abs(tab[i]+((rand()%20)-9));
    }
    for (int i = 0; i < n; i++)
    {
        cout<<tab[i]<<"\n";
    }
    
    // | const 8b | frame nr 16b | gps x-15b (map 15b, 16-20)  y-15b, (map 15b, 48-52) h-12b (raw) , meta-4b   | 
    // |-20, 43 9b temp *3 (map 9b, -20, 40) | 7b hum (raw) | map(2.5-4.5,8b) bat voltage | 32b particle counter * 3 sizes 
    //| pressure  (raw 9b off +500)| 8b * 6 gyro | 8b RSSI  (raw offset-164) | 8b state | 10b airflow | 16b CRC  
}