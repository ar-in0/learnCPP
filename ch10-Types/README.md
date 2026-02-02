# Chapter 10: Type Conversion, Type Aliases, Type Deduction
Implicit Type Conversion aka automatic type conversion aka coercion  
Type of a identifier tells the compiler how to interpret the bytes in RAM that represent its value
- Most type conversions in c++ are implicit. These are specified by C++ Standard, called "Standard Conversions"
- If a conversion is allowed by the standard, the compiler creates a new binary value for that identifier, corresponding to the new type

Standard sets a **minimum size** for each fundamental type, but actual size is compiler+architecture dependent.
- Wide data-type: More bits used to store its value
- Narrow data-type: Less bits used to store its value

https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/ : Integral promotion rules

Numeric Promotions (narrow->wide type): Safe because value-preserving
Numeric Conversion: May be unsafe dep on the types

Narriowing conversion: Going from a wide->narrow type. Potentially unsafe because the upper range of values of the wider type
cannot be represented by the narrow type. 
- If range of values of wider type can be guranteed compatible, narrowing cconversion is ok
- Make narrowing conversions explicit with `static_cast`

Constexpr and narrowing conversions: Compiler knows the exact value of the ident with that type, and can
decide at compile time whether the "narrow" type can hold it. If yes, the conversion is allowed. If no,
compilation error

``` C++
int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```

- Use `#include <typeinfo> typeid(<obj>).name` to get resulting type of the object (helpful to see the implicit conversion).

Type Alias: More convininet name for an existing type. Declared with `using Distance = float`. Distance is an identifier, so has same scope rules.
- To use accross program, add all type aliases to a common header file

``` C++
typedef int (*FcnType)(double, char); // FcnType hard to find
using FcnType = int(*)(double, char); // FcnType easier to find
using VectPairSI = std::vector<std::pair<std::string, int>>;
```

Trailing Return Types:

``` C++
auto add(int x, int y) -> int
{
  return (x + y);
}

#include <type_traits> // for std::common_type

std::common_type_t<int, double> compare(int, double);         // harder to read (where is the name of the function in this mess?)
auto compare(int, double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)

// align function names
auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
auto printSomething() -> void;
auto generateSubstring(const std::string &s, int start, int len) -> std::string;
```

`
