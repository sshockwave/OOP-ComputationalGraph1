#include "MathFunc.h"
#include <iostream>
#include <cmath>

// some macro functions
#define _SIGMOID(x) 1 / (1 + exp(-x))
#define _TANH(x) (exp(x) - exp(-x)) / (exp(x) + exp(-x))

// GET_VALUE_S_F defined in Value.h
// #define GET_VALUE_S_F(pointer) ((Scalar<float> *)pointer)->value

// one parameter functions
#define _ONE_PARA_COMPUTE(func) \
    GET_VALUE_S_F(out) = func(GET_VALUE_S_F(in[0]));
#define _ONE_PARA_MATCH(keyword)                    \
    if (tokens.size() == 4 && tokens[2] == keyword) \
    {                                               \
        graph.newNode(tokens[0],                    \
                      vector<string>(1, tokens[3]), \
                      this);                        \
        return 1;                                   \
    }                                               \
    return 0;

// two parameter functions
#define _TWO_PARA_COMPUTE(op) \
    GET_VALUE_S_F(out) =      \
        GET_VALUE_S_F(in[0]) op GET_VALUE_S_F(in[1]);
#define _TWO_PARA_MATCH(keyword)                    \
    if (tokens.size() == 5 && tokens[3] == keyword) \
    {                                               \
        vector<string> fathers;                     \
        fathers.push_back(tokens[2]);               \
        fathers.push_back(tokens[4]);               \
        graph.newNode(tokens[0], fathers, this);    \
        return 1;                                   \
    }                                               \
    return 0;

// derived function template
#define ONE_PARA_FUNC(classname, func, keyword)             \
    COMPUTE_DERIVED(classname) { _ONE_PARA_COMPUTE(func); } \
    MATCH_DERIVED(classname) { _ONE_PARA_MATCH(keyword); }

#define TWO_PARA_FUNC(classname, op, keyword)             \
    COMPUTE_DERIVED(classname) { _TWO_PARA_COMPUTE(op); } \
    MATCH_DERIVED(classname) { _TWO_PARA_MATCH(keyword); }

// normal derived classes
ONE_PARA_FUNC(Exp, exp, "EXP");
ONE_PARA_FUNC(Sigmoid, _SIGMOID, "SIGMOID");
ONE_PARA_FUNC(Sin, sin, "SIN");
ONE_PARA_FUNC(Tanh, _TANH, "TANH");
ONE_PARA_FUNC(Minus, -, "-");
TWO_PARA_FUNC(Plus, +, "+");
TWO_PARA_FUNC(Sub, -, "-");
TWO_PARA_FUNC(Mult, *, "*");
TWO_PARA_FUNC(Smaller, <, "<");
TWO_PARA_FUNC(SmallerEqual, <=, "<=");
TWO_PARA_FUNC(Equal, ==, "==");
TWO_PARA_FUNC(LargerEqual, >=, ">=");
TWO_PARA_FUNC(Larger, >, ">");

// special derived classes
// Log------------------------------------------------------------------
COMPUTE_DERIVED(Log)
{
    if (GET_VALUE_S_F(in[0]) <= 0)
        throw "ERROR: LOG operator's input must be positive";
    _ONE_PARA_COMPUTE(log);
}
MATCH_DERIVED(Log){_ONE_PARA_MATCH("LOG")}
// Div------------------------------------------------------------------
COMPUTE_DERIVED(Div)
{
    if (GET_VALUE_S_F(in[1]) == 0)
        throw "ERROR: Division by zero";
    _TWO_PARA_COMPUTE(/);
}
MATCH_DERIVED(Div){_TWO_PARA_MATCH("/")};
// Print----------------------------------------------------------------
COMPUTE_DERIVED(Print) { _ONE_PARA_COMPUTE(); }
MATCH_DERIVED(Print)
{
    if (tokens.size() == 4 && tokens[2] == "PRINT")
    {
        graph.newNode(tokens[0], vector<string>(1, tokens[3]), this,
                      true); // true means printFlag is on
        return 1;
    }
    return 0;
};
// Cond-----------------------------------------------------------------
COMPUTE_DERIVED(Cond) { GET_VALUE_S_F(out) = GET_VALUE_S_F(in[0]) > 0 ? GET_VALUE_S_F(in[1]) : GET_VALUE_S_F(in[2]); }
MATCH_DERIVED(Cond)
{
    if (tokens.size() == 6 && tokens[2] == "COND")
    {
        vector<string> fathers;
        fathers.push_back(tokens[3]);
        fathers.push_back(tokens[4]);
        fathers.push_back(tokens[5]);
        graph.newNode(tokens[0], fathers, this);
        return 1;
    }
    return 0;
}