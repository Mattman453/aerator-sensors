#include <iostream>
#include <unistd.h>
#include <wiringPiSPI.h>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

static const int CHANNEL = 1;

static const int pressure = 0;
static const int moisture = 1;
static const int force = 2;

static const float LSBSIZE = 5.0/1024;

void setChannel(unsigned char *data, int channel) {
    data[0] = (0x01 << 7) | (0x01 << 6);
    data[1] = 0;
    data[2] = 0;
    data[0] = data[0] + (channel << 3);
}

int getOutput(unsigned char *data) {
    int output = ((data[0] & 3) << 8) + data[1];
    return output;
}

int main() {
    int fd;
    
    cout << "Initializing" << endl;
    
    fd = wiringPiSPISetup(CHANNEL, 200000) ;
    
    cout << "Init result: " << fd << endl;
    
    while (true) {
        unsigned char spiData[3];
        int output[3] = {0,0,0};
        
        /*for (int i = 0; i < 8; i++) {
            setChannel(spiData, i);
            //cout << to_string(spiData[0]) << endl;
            //this_thread::sleep_for(chrono::nanoseconds(100000000));
        }*/
        
        setChannel(spiData, pressure);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        output[0] = getOutput(spiData);
        
        setChannel(spiData, force);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        output[2] = getOutput(spiData);
        
        setChannel(spiData, moisture);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        output[1] = getOutput(spiData);
        
        sleep(1);
    }
    
    return 0;
}
