/*草稿*/

#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

#define GET_DTYPE(x) typeid(x).name()[0]
#define CAST_DERIVED(x, type) static_cast<Derived<type> *>(x)

class Base
{
};

template <class T>
class Derived : public Base
{
public:
    char dtype;
    T value;
    Derived(T value) : dtype(GET_DTYPE(value)), value(value) {}
};

int main()
{
    // const type_info &type = typeid(int);
    Base *p = new Derived<int>(11);
    Base *b = new Derived<float>(2.2);
    
    cout << CAST_DERIVED(p, int)->value + CAST_DERIVED(b, float)->value;
    cout << ((Derived<int> *)p)->value;
    return 0;
}
