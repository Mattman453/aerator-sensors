#include "temperature.hpp"

using namespace std;

string setupTemperature() {
    system("modprobe w1-gpio");
    system("modprobe w1-therm");

    system("ls /sys/bus/w1/devices/ > List.txt");

//    sleep(5);

    ifstream f("List.txt");
    string filename;
    getline(f, filename);
    f.close();
    filename = "/sys/bus/w1/devices/" + filename + "/w1_slave";
    return filename;
}

long getTemperature(string filename) {
    ifstream f(filename);
    string line;

    getline(f, line);
//    cout << line << endl;
    getline(f, line);
//    cout << line << endl;
    long loc = line.find("=");
    line = line.substr(loc + 1);
//    cout << line << endl;
    long temp = stoi(line);
//    cout << temp << endl;

    return (temp / 1000.0) * (9.0/5.0) + 32.0;
}