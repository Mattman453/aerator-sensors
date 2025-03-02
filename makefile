all: aerator

aerator: accelerometer.o moisture.o strain_gauge.o temperature.o main.o
	gcc -lWiringPi accelerometer.o moisture.o strain_gauge.o temperature.o main.o -o main

main.o: accelerometer.hpp moisture.hpp strain_gauge.hpp temperature.hpp main.cpp
	gcc -lWiringPi -c main.cpp -o main.o

accelerometer.o: accelerometer.cpp accelerometer.hpp
	gcc -lWiringPi -c accelerometer.cpp -o accelerometer.o

moisture.o: moisture.cpp moisture.hpp
	gcc -lWiringPi -c moisture.cpp -o moisture.o

strain_guage.o: strain_gauge.cpp strain_gauge