all: aerator

aerator: main.o temperature.o force.o
	g++ main.o temperature.o force.o -l wiringPi -o aerator

clean:
	rm main.o temperature.o aerator
	
main.o: main.cpp temperature.hpp
	g++ -c main.cpp -o main.o -Wpedantic

temperature.o: temperature.cpp temperature.hpp
	g++ -c temperature.cpp -o temperature.o -Wpedantic

force.o: force.cpp force.hpp
	g++ -c force.cpp -o force.o -Wpedantic
