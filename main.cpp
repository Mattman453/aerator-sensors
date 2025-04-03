#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <wiringPiSPI.h>
#include <string>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <math.h>
#include "temperature.hpp"
#include "force.hpp"
#include "SPI.hpp"

using namespace std;

//#define M_PI 3.141592653589793238462643

enum status {
    READY, NOT_READY, STANDBY
};

static const long CHANNEL = 1;

long convertValueToMoisturePercentage(long data) {
    long output = data/614.4 * 100.0;
    output = 100.0 - output;
    return output;
}

long getMoisturePercentage(unsigned char *data) {
    return convertValueToMoisturePercentage(getSPIOutput(data));
}

double convertInchToMeter(double number) {
    return number / 39.3700787;
}

double getArea() {
    double outerRadius = convertInchToMeter(15.0/16.0);
    double innerRadius = convertInchToMeter(13.0/16.0);
    double outerCircleArea = 2 * M_PI * outerRadius;
    double innerCircleArea = 2 * M_PI * innerRadius;
    double area = outerCircleArea - innerCircleArea;
    return area * 2.0;
}

status isReady(long moisture, long force, long temperature, bool isWarm) {
    /*
     * Warm Season Readiness:
     * -Temperature:    65-75 Fahrenheit
     * -Pressure:       -10 to -33 kPa
     * -Moisture:       50-70%
     *
     * Cool Season Readiness:
     * -Temperature:    50-65 Fahrenheit
     * -Pressure:       -10 to -33kPa
     * -Moisture:       50-70%
     *
     * Area:
     * 15/16 inch outer radius
     * 13/16 inch inner radius
     * 2 prongs
     */
    double area = getArea();
    double pressure = abs(force / area / 1000.0);

    if (moisture <= 50.0) {
        return NOT_READY;
    }

    if (moisture >= 70.0) {
        return NOT_READY;
    }

    if (pressure <= 10.0) {
        return NOT_READY;
    }

    if (pressure >= 33.0) {
        return NOT_READY;
    }

    if (isWarm) {
        if (temperature <= 65.0) {
            return NOT_READY;
        }

        if (temperature >= 75.0) {
            return NOT_READY;
        }
    }
    else {
        if (temperature <= 50.0) {
            return NOT_READY;
        }

        if (temperature >= 65.0) {
            return NOT_READY;
        }
    }

    return READY;
}

int main() {
    long fd;
    status readyToAerate;

//    cout << "Initializing" << endl;
    
    fd = wiringPiSPISetup(CHANNEL, 100000) ;
    
//    cout << "Init result: " << fd << endl;

    string temperatureFilename = setupTemperature();
//    cout << temperatureFilename << endl;
    
    while (true) {
        unsigned char spiData[3];
        long moisture = 0;
        long force = 0;
        long temperature = 0;

        setChannel(spiData, MOISTURE);
        wiringPiSPIDataRW(CHANNEL, spiData, 3);
        moisture = getMoisturePercentage(spiData);
        cout << "Moisture: " << moisture << "%" << endl;
//        this_thread::sleep_for(chrono::milliseconds(1000));

        temperature = getTemperature(temperatureFilename);
        cout << "Temperature: " << temperature  << "°F"<< endl;
//        this_thread::sleep_for(chrono::milliseconds(1000));
        
        readyToAerate = isReady(moisture, force, temperature, true);

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    return 0;
}
