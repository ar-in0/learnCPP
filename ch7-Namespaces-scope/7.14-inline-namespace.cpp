#include <iostream>

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    doSomething(); // old calls remain unaffected by inline namespace
    V1::doSomething(); // new calls to old version can use v1:: (inline namespace)
    V2::doSomething(); // new calls to v2 can use v2:: (regular namespace)

    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}