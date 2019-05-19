CXX=g++
CXX_FLAGS=-std=c++14 -g

.PHONY: all run test clean
all: main
run:
	./main
test: main test.sh
	@chmod +x test.sh
	./test.sh
clean:
	rm -rf bin/* dep/* test/**/*.tmp main

src=$(patsubst %.cpp,%,$(wildcard *.cpp))

main: $(patsubst %,bin/%.o,$(src))
	$(CXX) -o $@ $^ $(CXX_FLAGS)

# Auto-generate dependencies
.PRECIOUS: dep/%.d
dep/%.d: %.cpp
	$(CXX) -o $@ $*.cpp -MM -MP -MT bin/$*.o\ dep/$*.d

# Import dependencies
-include $(patsubst %,dep/%.d,$(src))

bin/%.o: %.cpp dep/%.d
	$(CXX) -o $@ $< -c $(CXX_FLAGS)
