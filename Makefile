CXX_FLAGS=-std=c++14 -g

.PHONY: all run test clean
all: dist/main
run:
	dist/main
test: dist/main test.sh
	@chmod +x test.sh
	./test.sh
clean:
	rm -rf bin dep dist test/*.out

src=$(patsubst src/%.cpp,%,$(wildcard src/*.cpp))

dist/main: $(patsubst %,bin/%.o,$(src))
	@mkdir -p $(@D)
	$(CXX) -o $@ $^ $(CXX_FLAGS)

# Auto-generate dependencies
.PRECIOUS: dep/%.d
dep/%.d: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) -o $@ src/$*.cpp -MM -MP -MT bin/$*.o\ dep/$*.d

# Import dependencies
-include $(patsubst %,dep/%.d,$(src))

bin/%.o: src/%.cpp dep/%.d
	@mkdir -p $(@D)
	$(CXX) -o $@ $< -c $(CXX_FLAGS)
