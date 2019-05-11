# compile options
CXXFLAGS:=-O2 -std=c++14

# target
ifndef TAR
	TAR:=main
# else # target is not main, the following option will ignore undefined referrence. just for semi-finished debugging
# 	TAR:=draft
# 	CXXFLAGS:= $(CXXFLAGS) -Wl,--unresolved-symbols=ignore-in-object-files
endif

# time test
# ifdef TIME
# 	CXXFLAGS:= $(CXXFLAGS) -D TIME_TEST
# endif

# find *.cpp, get *.o
SRCS:=$(wildcard Graph/*.cpp Parser/*.cpp) $(TAR).cpp
OBJS:=$(patsubst %.cpp, %.o, $(SRCS))
ALLSRCS:=$(wildcard Graph/*.cpp Parser/*.cpp *.cpp)
ALLOBJS:=$(patsubst %.cpp, %.o, $(ALLSRCS))
ALLEXES:=$(patsubst %.cpp, %, $(wildcard *.cpp))

all: build

# sub_build, then generate $(TAR)
build: $(TAR).cpp sub_build
	g++ $(CXXFLAGS) -c $(TAR).cpp
	g++ $(CXXFLAGS) $(OBJS) -o $(TAR)

# build in sub-directories (Graph/ and Parser/)
sub_build:
	make build -C Graph/
	make build -C Parser/

# clean old files, then sub_debug, then generate $(TAR)
debug: $(TAR).cpp clean sub_debug
	g++ -g $(CXXFLAGS) -c $(TAR).cpp
	g++ -g $(CXXFLAGS) $(OBJS) -o $(TAR)

# debug in sub-directories
sub_debug:
	make debug -C Graph/
	make debug -C Parser/

# clean and cleanall
.PHONY: clean cleanall
clean:
	-rm $(OBJS)

cleanall:
	-rm $(ALLOBJS) $(ALLEXES)
