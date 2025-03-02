all: aerator

aerator: accelerometer.o moisture.o strain_gauge.o temperature.o main.o
	gcc -lWiringPi accelerometer.o moisture.o strain_gauge.o temperature.o main.o -o aerator

clean:
	rm accelerometer.o moisture.o strain_gauge.o temperature.o main.o aerator

main.o: accelerometer.hpp moisture.hpp strain_gauge.hpp temperature.hpp main.cpp
	gcc -Wpedantic -lWiringPi -c main.cpp -o main.o

accelerometer.o: accelerometer.cpp accelerometer.hpp
	gcc -Wpedantic -lWiringPi -c accelerometer.cpp -o accelerometer.o

moisture.o: moisture.cpp moisture.hpp
	gcc -Wpedantic -lWiringPi -c moisture.cpp -o moisture.o

strain_guage.o: strain_gauge.cpp strain_gauge.hpp
	gcc -Wpedantic -lWiringPi -c strain_gauge.cpp -o strain_gauge.o

temperature.o: temperature.cpp temperature.hpp
	gcc -Wpedantic -lWiringPi -c temperature.cpp -o temperature.o
