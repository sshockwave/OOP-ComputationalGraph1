#pragma once

#include <iostream>
#include <map>
#include "Node.h"
#include "Value.h"
#include "MathFunc.h"
using namespace std;

// defined in other files
class Node;
class Value;
class MathFunc;

class Graph
{
    map<string, Node*> nodes;
    vector<Value *> ans;
    int step = 0;
    void DFScompute(Node *work); //recursive compute

public:
    Graph(){};
    void newNode(string name, char ntype, float initValue);     // same as below
    void newNode(string name, char ntype, Value *initValue);    // new base nodes
    void newNode(string name, vector<string> fathers, MathFunc *func, bool printFlag=0); // new intermediate nodes
    void editNode(string name, float newValue);         // same as below
    void editNode(string name, Value *newValue);        // editNode and update timeStep, updateFlag
    void eval(string target, vector<string> inName, vector<Value*> inValue); // eval and output
    Value *getAns(int step); // step starts from 0
    void noAnsStep(){step++; ans.push_back(nullptr);}

    friend class Node;
};
