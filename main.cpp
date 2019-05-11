#include <iostream>
#include <time.h>
#include "Graph/Graph.h"
#include "Parser/Parser.h"
using namespace std;

int main()
{
    // assume there is only one graph
    Graph graph;
    Parser parser(graph);

    // define base nodes
    parser.setMod(1);
    int baseNum;
    cin >> baseNum;
    for (int i = 0; i < baseNum; i++)
    {
        cin >> parser;
    }

    // define intermediate nodes
    parser.setMod(2);
    int interNum;
    cin >> interNum;
    for (int i = 0; i < interNum; i++)
    {
        cin >> parser;
    }

    // some commands
    parser.setMod(3);
    int cmdNum;
    cin >> cmdNum;
    for (int i = 0; i < cmdNum; i++)
    {
        cin >> parser;
    }

    return 0;
}
