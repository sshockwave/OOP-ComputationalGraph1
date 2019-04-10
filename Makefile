CXX_FLAGS=-std=c++11 -g

cgraph=bin/Node.o bin/Expression.o bin/arithmetics.o bin/floattypes.o bin/Session.o bin/Graph.o

.PHONY: all clean cgraph

all: bin/main.o $(cgraph)
	$(CXX) $^ -o dist/main $(CXX_FLAGS)

clean:
	rm -rf bin/* dist/*

test:
	echo No tests specified.

bin/main.o: src/main.cpp src/cgraph.h
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

cgraph: $(cgraph)
src/cgraph.h: src/Expression.h src/arithmetics.h src/floattypes.h src/Session.h src/Graph.h
	touch $@

src/Node.cpp: src/Node.h
	touch $@
bin/Node.o: src/Node.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Expression.h: src/Node.h
	touch $@
src/Expression.cpp: src/Expression.h
	touch $@
bin/Expression.o: src/Expression.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/arithmetics.h: src/Expression.h
	touch $@
src/arithmetics.cpp: src/arithmetics.h src/Node.h
	touch $@
bin/arithmetics.o: src/arithmetics.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/floattypes.h: src/Expression.h
	touch $@
src/floattypes.cpp: src/floattypes.h
	touch $@
bin/floattypes.o: src/floattypes.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Session.h: src/Node.h src/Expression.h src/floattypes.h
	touch $@
src/Session.cpp: src/Session.h
	touch $@
bin/Session.o: src/Session.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)

src/Graph.h: src/Expression.h src/floattypes.h
	touch $@
src/Graph.cpp: src/Graph.h
	touch $@
bin/Graph.o: src/Graph.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS)
