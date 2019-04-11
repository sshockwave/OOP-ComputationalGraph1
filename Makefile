CXX_FLAGS=-std=c++14 -g

cgraph=bin/Symbol.o bin/Node.o bin/Expression.o bin/arithmetics.o bin/sinks.o bin/Graph.o bin/Error.o

.PHONY: all clean cgraph

all: dist/main

clean:
	rm -rf bin/* dist/*

test:
	echo No tests specified.

bin/main.o: src/main.cpp src/cgraph.h
	$(CXX) -c $< -o $@ $(CXX_FLAGS)
dist/main: bin/main.o $(cgraph)
	$(CXX) $^ -o dist/main $(CXX_FLAGS)

cgraph: $(cgraph)
src/cgraph.h: src/Expression.h src/arithmetics.h src/Graph.h src/Error.h
	touch $@

src/Symbol.h:
	touch $@
src/Symbol.cpp: src/Symbol.h
	touch $@
bin/Symbol.o: src/Symbol.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Node.h: src/Symbol.h
	touch $@
src/Node.cpp: src/Node.h
	touch $@
bin/Node.o: src/Node.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Error.h:
	touch $@
src/Error.cpp: src/Error.h
	touch $@
bin/Error.o: src/Error.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Expression.h: src/Node.h
	touch $@
src/Expression.cpp: src/Expression.h src/Error.h
	touch $@
bin/Expression.o: src/Expression.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/arithmetics.h: src/Expression.h
	touch $@
src/arithmetics.cpp: src/arithmetics.h
	touch $@
bin/arithmetics.o: src/arithmetics.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/sinks.h: src/Expression.h
	touch $@
src/sinks.cpp: src/sinks.h src/Error.h
	touch $@
bin/sinks.o: src/sinks.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)
	
src/Graph.h: src/sinks.h
	touch $@
src/Graph.cpp: src/Graph.h
	touch $@
bin/Graph.o: src/Graph.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)
