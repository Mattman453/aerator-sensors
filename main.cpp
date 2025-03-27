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
#include "SPI.hpp"

using namespace std;

static const long CHANNEL = 1;

long convertValueToMoisturePercentage(long data) {
    long output = data/614.4 * 100.0;
    return output;
}

long getMoisturePercentage() {
    return convertValueToMoisturePercentage(getSPIOutput(MOISTURE));
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

        setChannel(spiData, MOISTURE);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        output[2] = getMoisturePercentage();
        cout << "Moisture: " << output[2] << "%" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        output[3] = getTemperature(temperatureFilename);
        cout << "Temperature: " << output[3] << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        
//        sleep(1);
    }
    
    return 0;
}
