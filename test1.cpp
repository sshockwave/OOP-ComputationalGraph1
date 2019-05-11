#include <iostream>
#include <time.h>
#include "Graph/Graph.h"
#include "Parser/Parser.h"
using namespace std;

/*
== high efficiency test ==
to test high efficiency, 
there are a lot of ai (10001, set by SCALE),
but only a0 is Placeholder.
the other ais are:
ai = log(ai-1)
or,
ai = exp(ai-1).

there is 1 more Placeholder p, and 1 Variable v.
res1 = p + a10000
res2 = v + a10000

eval res1 and eval res2 with a0 unchanged,
there is significant difference in computing time.
*/

// the scale of ai
#define SCALE 10000
#define str to_string

// time counting
clock_t start, finish;
double delta;
// put whatever you want into this macro function, it will output used time
#define COUNT_TIME(line)                               \
    start = clock();                                   \
    line;                                              \
    finish = clock();                                  \
    delta = (double)(finish - start) / CLOCKS_PER_SEC; \
    cout << "@" << delta << "sec" << endl              \
         << endl;

int main()
{
    // assume there is only one graph
    Graph graph;
    Parser parser(graph);

    // define base nodes
    parser.setMod(1);
    cout << 3 << endl;
    vector<string> base = {"a0 P", "p P", "v V 4"};
    for (auto line : base)
    {
        cout << line << endl;
        parser.parse(line);
    }

    // define intermediate nodes
    parser.setMod(2);
    cout << SCALE + 2 << endl;
    cout << "ai+1 = EXP ai" << endl
         << "ai+2 = LOG ai+1" << endl;
    for (int i = 0; i < SCALE; i += 2)
    {
        string line1 = "a" + str(i + 1) + " = EXP a" + str(i);
        string line2 = "a" + str(i + 2) + " = LOG a" + str(i + 1);
        parser.parse(line1);
        parser.parse(line2);
    }
    string line1 = "res1 = p + a" + str(SCALE);
    string line2 = "res2 = v + a" + str(SCALE);
    cout << line1 << endl;
    cout << line2 << endl;
    parser.parse(line1);
    parser.parse(line2);

    // some commands
    parser.setMod(3);
    cout << 7 << endl;
    vector<string> cmd = {"EVAL res1 2 a0 2 p 1",
                          "EVAL res2 2 a0 2 p 1",
                          "EVAL res2 2 a0 2 p 2",
                          "EVAL res1 2 a0 2 p 2",
                          "EVAL res2 1 a0 3",
                          "SETCONSTANT v 666",
                          "EVAL res2 1 a0 3"};
    for (auto line : cmd)
    {
        cout << line << endl;
        COUNT_TIME(parser.parse(line););
    }

    return 0;
}
