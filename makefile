all: aerator

aerator: main.o
	g++ main.o -l wiringPi -o aerator

clean:
	rm main.o aerator
	
main.o: main.cpp
	g++ -c main.cpp -o main.o
