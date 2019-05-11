#pragma once

#include <typeinfo>
#include <vector>
using namespace std;

#define GET_CHAR_DTYPE(data) typeid(data).name()[0]
#define GET_VALUE(stype, dtype, pointer) ((stype<dtype> *)pointer)->value
#define GET_VALUE_S_F(pointer) GET_VALUE(Scalar, float, pointer)
// to do
// #define FUNC_WITH_CASTED_BASE_POINTER(func, pointer) \
//     if (pointer->stype == 'S')                       \
//     {                                                \
//         if (pointer->dtype == 'f')                   \
//             func(GET_VALUE(Scalar, float, pointer))  \
//     }

/*
IMPORTANT: Value stores information of value, but doesn't stores value itself
           value is stored in derived classes. see Scalar for example.
*/

class Value
{
    // header
    char _stype;        // shape type, 'S'calar, 'A'rray (to do)
    vector<int> _shape; // shape of the value. for scalar, shape = 1
    char _dtype;        // data type, 'f'loat, 'i'nt, or 'b'ool if you want (to do)
public:
    Value(char stype, vector<int> shape, char dtype);
    const char &stype = _stype;
    const vector<int> &shape = _shape;
    const char &dtype = _dtype;

    virtual ~Value(){};
};

template <typename T>
class Scalar : public Value
{
public:
    T value; // in stage 1, T is float
    Scalar(T value) : Value('S', vector<int>(1, 1), GET_CHAR_DTYPE(value)), value(value) {}
    ~Scalar() {}
};

/* to do
template <typename T>
class Array : public Value
{
  public:
    vector<T> value;
    
    Array(vector<int> shape) : Value('A', shape, GET_CHAR_DTYPE(value)) {}
    Array(vector<int> shape, vector<T> value) : Value('A', shape, GET_CHAR_DTYPE(value)) {this->value = value;}
    ~Array();
};
*/