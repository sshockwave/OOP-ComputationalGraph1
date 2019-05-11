#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "Graph.h"
#include "Value.h"
#include "MathFunc.h" // MathFunc.h and Node.h are included in Graph.h
using namespace std;

// defined in other files
class Graph;
class MathFunc;

/*
Node::value stores the value. see Value.h
*/

class Node
{
    Graph &graph;
    const string name;      // "a", "x", "res", etc
    const char ntype;       // 'V'ariable, 'P'laceholder, 'C'onstant, 'I'termediate
    Value *value;           // derived to Scalar<float> for now
    
    MathFunc *func;         // func->compute can override as Sin, Log, etc
    vector<Node*>fathers;   // directly dependent nodes
    set<Node*>ancestors;    // originally depedent nodes (Placeholder or Variable)
    vector<Node*>children;  // directly induced nodes
    set<Node*>descendants;   // ancestor's children and grandchildren
    set<Node*>prints;       // fathers and grandfathers with Print

    bool updateFlag = 1;    // determines whether to compute
    
public:
    Node(Graph &graph, string name, char ntype, MathFunc *func); // *func = nullptr means the node is P, V, C
    ~Node();
    void setValue(Value *value);
    void addFather(Node *father);
    void addAncestor(Node *ancestor);
    
    friend class Graph; // intuitive
};
