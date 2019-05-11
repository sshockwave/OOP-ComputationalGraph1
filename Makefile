all: main

main: main.o point.o pc.o
	g++ main.o point.o pc.o -o main -O2 -std=c++11

main.o: main.cpp point.cpp pc.cpp
	g++ -c main.cpp -o main.o -O2 -std=c++11

point.o: pc.cpp point.cpp
	g++ -c pc.cpp -o point.o -O2 -std=c++11

point.o: point.cpp
	g++ -c point.cpp -o point.o -O2 -std=c++11

clean: 
	rm -fR *.o main