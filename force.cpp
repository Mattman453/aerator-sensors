#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "force.hpp"

using namespace std;

long getForce(long tare, long scale) {
    string command = "../hx711/hx711 " + to_string(tare) + " > forceData.txt";
    system(command.c_str());

    ifstream file("forceData.txt");
    string out;
    getline(file, out);

    return stol(out) / scale;
}
