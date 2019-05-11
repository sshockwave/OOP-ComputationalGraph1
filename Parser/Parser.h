#pragma once

#include <iostream>
#include "../Graph/Graph.h"
#include "../Graph/MathFunc.h"
using namespace std;

class Parser
{
    Graph &graph;
    int mod; // mod = 1, 2, 3
    vector<MathFunc *> mathFuncs;

    string tmp_line;           // stores result from getline
    vector<string> tmp_tokens; // stores tokens from tmp_line
    void parse();              // called by operator>>

public:
    Parser(Graph &graph);
    void parse(const string &line);
    void split(const string &line, vector<string> &tokens); // get tokens
    void setMod(int mod);
    void cmdBase();
    void cmdInter();
    void cmdEval();
    void cmdSetCon();
    void cmdSetAns();
    friend istream &operator>>(istream &input, Parser &parser);
};
