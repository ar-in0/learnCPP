#include <iostream>
#include <string>
// Determines whether an expression is an lvalue or an rvalue:

// T& is an lvalue reference, so this overload will be preferred for lvalues
// T& = lvalue is by defintion from the cpp standard
template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
// again, T&& is rvalue from the cpp standard
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// A helper macro (#expr prints whatever is passed in for expr as text)
// compiler will pick the correct overloaded function based on the type of expr
// passed to it.
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }

int getint() { return 5; }

int main()
{
    PRINTVCAT(5);        // rvalue
    PRINTVCAT(getint()); // rvalue
    int x { 5 };
    PRINTVCAT(x);        // lvalue
    PRINTVCAT(std::string {"Hello"}); // rvalue
    PRINTVCAT("Hello");  // lvalue
// increment x and return x itself
// int y = 8
// int b = ++y // b = 9, y = 9

    PRINTVCAT(++x);      // lvalue
                         //
    // increment the value of x and return the OLD value
    // x++ is a temp value - a copy of the old value
    // made before incrementing the old value
    // ex.
    // int x = 5;
    // int a = x++ // a = 5, x = 6
    PRINTVCAT(x++);      // rvalue
}
