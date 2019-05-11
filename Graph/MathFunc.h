#pragma once

#include <iostream>
#include <vector>
#include "Value.h"
#include "Graph.h"
using namespace std;

/*
MathFunc only contains name, compute and match. 
every class needs only one object since they are mainly aimed to provide compute function, not values.
*/

// defined in other files
class Graph;
class Value;

// some macro functions
#define VIRTUAL_COMPUTE void compute(vector<Value *> in, Value *out)
#define COMPUTE_DERIVED(DERIVED_CLASS) void DERIVED_CLASS::compute(vector<Value *> in, Value *out)
#define VIRTUAL_MATCH bool match(Graph &graph, const vector<string> &tokens)
#define MATCH_DERIVED(DERIVED_CLASS) bool DERIVED_CLASS::match(Graph &graph, const vector<string> &tokens)

// template of derived class
#define DERIVE_FROM_MATHFUNC(DERIVED_CLASS)            \
    class DERIVED_CLASS : public MathFunc              \
    {                                                  \
    public:                                            \
        DERIVED_CLASS(string name) : MathFunc(name) {} \
        VIRTUAL_COMPUTE;                               \
        VIRTUAL_MATCH;                                 \
    };                                                 \
    static DERIVED_CLASS __##DERIVED_CLASS##__(#DERIVED_CLASS);
// after derived, every derived class creates its own static object

class MathFunc
{
    string _name; // stores name, private

public:
    const string &name = _name; // read-only, public
    MathFunc(string name) : _name(name) {}
    // MathFunc should be pure virtual
    virtual VIRTUAL_COMPUTE = 0;
    virtual VIRTUAL_MATCH = 0;
};

// some derived class
DERIVE_FROM_MATHFUNC(Print)
DERIVE_FROM_MATHFUNC(Exp)
DERIVE_FROM_MATHFUNC(Sigmoid)
DERIVE_FROM_MATHFUNC(Log)
DERIVE_FROM_MATHFUNC(Sin)
DERIVE_FROM_MATHFUNC(Tanh)
DERIVE_FROM_MATHFUNC(Minus)
DERIVE_FROM_MATHFUNC(Plus)
DERIVE_FROM_MATHFUNC(Sub)
DERIVE_FROM_MATHFUNC(Mult)
DERIVE_FROM_MATHFUNC(Div)
DERIVE_FROM_MATHFUNC(Smaller)
DERIVE_FROM_MATHFUNC(SmallerEqual)
DERIVE_FROM_MATHFUNC(Equal)
DERIVE_FROM_MATHFUNC(LargerEqual)
DERIVE_FROM_MATHFUNC(Larger)
DERIVE_FROM_MATHFUNC(Cond)
