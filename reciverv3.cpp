#include<bits/stdc++.h>
#include <curl/curl.h>
//#include<cpr/cpr.h>
#define FRAME_SIZE 42
using namespace std;
int sizes[24] = {8,16,15,15,12,4,9,9,9,9,7,8,32,32,9,8,8,8,8,8,8,8,16};
char buff[FRAME_SIZE];
string input;
unsigned int values[25];
int main(){
    
    int rrsi;
    cin>>rrsi;
    cin>>input;
    input.push_back(0);
    for (int i = 0; i < (input.size())/2; i+=2)
    {
        buff[i/2] = input[i]<<4 + input[i+1];
    }
    
    //for (int i = 0; i < 42; i++)    cout<<int(buff[i])<<" ";
    cout<<"\n";
    int pointer=0;
    for (int i = 0; i < 25; i++)
    {
        for (int j = sizes[i]-1; j >=0; j--)
        {
            values[i]+=((( buff[pointer/8]) & (1<<(7-(pointer%8)))) > 0 ) << (sizes[i]-j-1);
            //cout<<i<<" "<<pointer/8<<" "<<j<<" "<<" "<<(((( buff[pointer/8]) & (1<<((abs(8-pointer))%8))) > 0 ) << (sizes[i]-j-1))<<"\n";
            pointer++;
        }
        //cout<<values[i]<<"\n\n";
    }
    
    string toJSON[24] = {"const","frame", "gps_x","gps_y","gps_h","gps_meta","tmp_1","tmp_2","tmp_3","tmp_4"
    "hum","bat","part_1","part_2","press","gyro_x","gyro_y","gyro_h",
    "acc_x","acc_y","acc_h","state","valid"};
    // "id": 1,
    //   "frame": 1,
    //   "gps_x": "13230",
    //   "gps_y": "43894",
    //   "gps_h": "550",
    //   "gps_meta": "fix",
    //   "tmp_1": 100,
    //   "tmp_2": 151,
    //   "tmp_3": 148,
    //   "hum": 199,
    //   "bat": 3702,
    //   "part_1": 100,
    //   "part_2": 100,
    //   "part_3": 200,
    //   "part_flow": 13,
    //   "press": "32903",
    //   "gyro": "0,32,3,23,2.3,32,23,8.3",
    //   "dbi": -133,
    //   "state": 0,
    //   "valid": true
    string POSTdata;
    //cout<<"{\n";
    POSTdata+="{\n";
    for (int i = 1; i < 24; i++) //bez const wypisuje
    {
        //cout<<'"'<<toJSON[i-1]<<'"'<<": "<<'"'<< values[i]<<'"'<<",\n";
        //cout<<'"'<<toJSON[i]<<'"'<<": "<< values[i]<<",\n";
        POSTdata+='"'+toJSON[i]+'"'+": " +to_string(values[i])+",\n";
    }
    POSTdata+='"rrsi: "'+rrsi+",\n";
    //cout<<"}\n";
    POSTdata+="}\n";
    // cpr::Response r = cpr::Post(cpr::Url{"dd.piotro.eu:1417/submit"},
    //                cpr::Body{POSTdata},
    //                cpr::Header{{"Content-Type", "text/plain"},{"X-Auth", "cDR1Zm1rImprZGYzbWRmaTlqZmNrMzRrZQo"}});
    // cout<<r.text;


    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, "Accept:");
        chunk = curl_slist_append(chunk, "X-Auth: cDR1Zm1rImprZGYzbWRmaTlqZmNrMzRrZQo");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_URL, "dd.piotro.eu:1417/submit");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)     fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));          
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

}