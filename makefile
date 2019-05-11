#makefile

main: main.cpp Basic_Node.h Operation_Node.h Operation_Node.cpp Constant_Node.h Constant_Node.cpp Data_Node.h Data_Node.cpp Graph.h Graph.cpp  Placeholder_Node.h Placeholder_Node.cpp  Variable_Node.h Variable_Node.cpp
	g++ main.cpp Operation_Node.cpp  Constant_Node.cpp  Data_Node.cpp Graph.cpp   Placeholder_Node.cpp   Variable_Node.cpp -o main -std=c++14
	
clean: 
	rm *.o main
	
debug:
	g++ -DDEBUG -o main  main.cpp Basic_Node.h Operation_Node.h Operation_Node.cpp Constant_Node.h Constant_Node.cpp Data_Node.h Data_Node.cpp Graph.h Graph.cpp  Placeholder_Node.h Placeholder_Node.cpp  Variable_Node.h Variable_Node.cpp