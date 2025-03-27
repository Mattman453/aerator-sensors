#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <wiringPiSPI.h>
#include <string>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "temperature.hpp"
#include "force.hpp"

using namespace std;

static const long CHANNEL = 1;

static const long pressure = 1;
static const long moisture= 0;
static const long force = 2;

static const double LSBSIZE = 5.0/1024;

void setChannel(unsigned char *data, long channel) {
    data[0] = (0x01 << 7) | (0x01 << 6);
    data[1] = 0;
    data[2] = 0;
    data[0] = data[0] + (channel << 3);
}

long convertValueToMoistureVoltage(long data) {
    long output = data/614.4 * 100.0;
    return output;
}

long getSPIOutput(unsigned char *data) {
    long output = ((data[0] & 3) << 8) + data[1];
    return output;
}

int main() {
    long fd;
    
//    cout << "Initializing" << endl;
    
    fd = wiringPiSPISetup(CHANNEL, 100000) ;
    
//    cout << "Init result: " << fd << endl;

    string temperatureFilename = setupTemperature();
//    cout << temperatureFilename << endl;
//    long temperature = getTemperature(temperatureFilename);
    
    while (true) {
        unsigned char spiData[3];
        long output[4] = {0,0,0,0};
        
        /*for (long i = 0; i < 8; i++) {
            setChannel(spiData, i);
            //cout << to_string(spiData[0]) << endl;
            //this_thread::sleep_for(chrono::nanoseconds(100000000));
        }*/
        
//        setChannel(spiData, pressure);
//        wiringPiSPIDataRW(CHANNEL, spiData, 3);
//        output[0] = getSPIOutput(spiData);
//        sleep(1);

//        setChannel(spiData, force);
//        wiringPiSPIDataRW(CHANNEL, spiData, 3);
//        output[1] = getSPIOutput(spiData);
//        sleep(1);

        setChannel(spiData, moisture);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        output[2] = getSPIOutput(spiData);
        output[2] = convertValueToMoistureVoltage(output[2]);
        cout << "Moisture: " << output[2] << "%" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        output[3] = getTemperature(temperatureFilename);
        cout << "Temperature: " << output[3] << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        
//        sleep(1);
    }
    
    return 0;
}
