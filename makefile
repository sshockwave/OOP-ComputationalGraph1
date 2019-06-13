CXX=g++
CXX_FLAGS=-std=c++14 -g

src=$(patsubst %.cpp,%,$(wildcard *.cpp))
lib=$(patsubst %,bin/%.o,$(src))
tests=$(patsubst test/%/test.sh,test/%/run,$(wildcard test/**/test.sh))

.PHONY: all test clean lib
all: lib $(patsubst test/%/test.sh,test/%/main,$(wildcard test/**/test.sh))
lib: $(lib)
test: $(tests)
clean:
	rm -rf bin/* dep/* test/**/*.tmp test/**/main test/**/*.log

test/%/main: test/%/main.cpp
test/%/run: test/stage1/test.sh test/%/main
	#@chmod +x test/%/test.sh
	test/$*/test.sh | tee test/$*/test.log
test/%/main: test/%/main.cpp $(lib)
	$(CXX) -o $@ $^ $(CXX_FLAGS) -I.

# Auto-generate dependencies
.PRECIOUS: dep/%.d
dep/%.d: %.cpp
	$(CXX) -o $@ $*.cpp -MM -MP -MT bin/$*.o\ dep/$*.d

# Import dependencies
-include $(patsubst %,dep/%.d,$(src))

bin/%.o: %.cpp dep/%.d
	$(CXX) -o $@ $< -c $(CXX_FLAGS)
