CXX_FLAGS=-std=c++14 -g

.PHONY: all run test clean
all: dist/main
run:
	dist/main
test:
	echo No tests specified.
clean:
	rm -rf bin/* dep/* dist/*

src=$(patsubst src/%.cpp,%,$(wildcard src/*.cpp))

dist/main: $(patsubst %,bin/%.o,$(src))
	$(CXX) -o $@ $^ $(CXX_FLAGS)

# Auto-generate dependencies
.PRECIOUS: dep/%.d
dep/%.d: src/%.cpp
	$(CXX) -o $@ src/$*.cpp -MM -MT bin/$*.o\ dep/$*.d

# Import dependencies
-include $(patsubst %,dep/%.d,$(src))

bin/%.o: src/%.cpp dep/%.d
	$(CXX) -o $@ $< -c $(CXX_FLAGS)
