all: aerator

aerator: accelerometer.o moisture.o strain_gauge.o temperature.o main.o
	g++ -lwiringPi accelerometer.o moisture.o strain_gauge.o temperature.o main.o -o aerator

clean:
	rm accelerometer.o moisture.o strain_gauge.o temperature.o main.o aerator

main.o: accelerometer.hpp moisture.hpp strain_gauge.hpp temperature.hpp main.cpp
	g++ -Wpedantic -lwiringPi -c main.cpp -o main.o

accelerometer.o: accelerometer.cpp accelerometer.hpp
	g++ -Wpedantic -lwiringPi -c accelerometer.cpp -o accelerometer.o

moisture.o: moisture.cpp moisture.hpp
	g++ -Wpedantic -lwiringPi -c moisture.cpp -o moisture.o

strain_guage.o: strain_gauge.cpp strain_gauge.hpp
	g++ -Wpedantic -lwiringPi -c strain_gauge.cpp -o strain_gauge.o

temperature.o: temperature.cpp temperature.hpp
	g++ -Wpedantic -lwiringPi -c temperature.cpp -o temperature.o
