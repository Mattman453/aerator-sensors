all: aerator

aerator: main.cpp
	g++ main.cpp -l wiringPi -o aerator

clean:
	rm main.o aerator
