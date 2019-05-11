CXXFLAGS:=-O2 -std=c++14
SRC:=$(wildcard *.cpp)

all: build

build: $(SRC)
	g++ $(CXXFLAGS) -c $(SRC)

debug: clean $(SRC)
	g++ -g $(CXXFLAGS) -c $(SRC)

.PHONY: clean
clean:
	-rm *.o
