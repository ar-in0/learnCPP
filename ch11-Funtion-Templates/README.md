# Chapter 11: Function Overloading, Function Templates
Function overloading: Define multiple functions with the same name, in the same scope. Each such function is called an "overloaded function/overload"
Useful when the method should work with different sets of input parameter types,
where a single definition would cause a narrowing conversion
- Overload resolution: Given an invoked overloaded function (i.e. code calls an overload), compiler aims to match to the most appropriate overload definition
The process of matching function calls to a specific overloaded function is called overload resolution.

Overload Differentiation:
- #params, type of params, const/volatile member functions(`int foo();, int foo() const;`), ref-qualifiers (`&, && in params).
- const differentiates params only when they are passed to the function by reference or by pointer address.
- Note that return type cannot be used to differentiate overloaded functions
https://www.learncpp.com/cpp-tutorial/chapter-11-summary-and-quiz/

Overload Resolution
1. Find exact match of function parameter types (and of course function name). 
a. With trivial conversion (lvalue->rvalue, const->non-const, non-ref to ref, etc.). If not found, (b).
b. **Numeric promotion. If not found, (c)**. Observe that the overload that needs a promotion to match takes priority over one that needs conversion
c. Numeric Conversion (char -> double, etc.). If not found, (d)
d. User-Defined Conversions. If not found, (e)
e. Functions with ellipses params. If not found, return no match found, compile error. 

At any stage if there are multiple paths, compilation halts with ambiguous call error

`=delete` specifier: Used when we explicitly want a function to be non-callable. (see ch14.14, ch11.7)

https://www.learncpp.com/cpp-tutorial/default-arguments/ : default args

Function Templates: System to simplify the process of creating overloads (i.e. so that we adhere to D.R.Y)
- A template defintion describes a function in a type-agostic manner, using placeholder types (aka type template params). Can generate a family of functions or classes
differentiated by the set of types.
- For functions, the initial template is called the **primary template**, and the generated functions are called **instantiated functions**

``` c++
template <typename T> // this is the template parameter declaration defining T as a type template parameter. class T is equivalent to typename T (historical)
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}

// Function template instantiation
return max<int>(1,2);
```

Function template instantiation

``` c++
template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```
Template Argument Deduction:
- Can use regular function call syntax ex. max(1,2) rather than max<int>(1,2). Normal syntax 
will instnatiate the required function template if reuqired, but if a normal method is defined, 
that definition will be chosen.
- Unlike overloaded function resolution, template argument deduction **does not** perform any type conversions or promotions.

- Function template arguments need not all be generic `T`. (i.e. non template parameters are allowed)
- Can dissalow certain template arguments using the `=delete` specifier

``` c++
template <typename T>
T addOne(T x)
{
    return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* addOne(const char* x) = delete;

int main()
{
    std::cout << addOne("Hello, world!") << '\n'; // compile error

    return 0;
}
```

Static non-const variable in function template defintion:
- New static identifier will be instantiated for every template instantiation, i.e. resetting
static state, and each will last for program lifetime

Multiple Template Types:

``` c++
template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>

    return 0;
}
```

**Template Usage Tip: Write normal functions first, and switch to templates if you observe yourself writing overloads**
**Template Usage Tip: Put all templates in a header file**
C++20: Abbreviated Function templates
- Use the auto keyword in the template return

``` c++
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

Non-Type Template Parameters: 
`std::bitset<8> bits {0b..};`, i.e. 8 is a non-type template param
See https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/
See also: https://www.learncpp.com/cpp-tutorial/using-function-templates-in-multiple-files/


---

(old)
# Function overloading
Function overloading allows the programmer to define functions with the same name, as long as its
parameters (#params, types) differ (i.e. functions are differentiated).
- Return type is not a differentiator.
- const can be a differentiator for member functions 
Function overload resolution: The process used by the compiler to match a function invocation to a definition. 
Compiler performs type promotion/conversions until a single best match is found. If multiple best matches, 
compiler returns ambiguous function error at compile time.

*Numeric promotion over numeric conversion* when matching overloads.

# Function templates
Allow the developer to specify function logic without being restricted by typing rules. 
Templates use placeholder types (type template parameters) in their definitions that are filled in at <compile-time>
```
template <typename T> // "template parameter declaration" defining T as a "type template parameter"
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}

// usage
max<actual_type>(arg1, arg2); // explicit template typess.  

// usage with type deduction
// if no non-template defintion exists, the templated version is
// called, with types autodeduced by the compiler.
// will call non-template if it is defined.
max(arg1, arg2);

max<>(arg1, arg2); // autodeuce, calls template only

```
The scope of a template parameter declaration is strictly limited to the function template (or class template) that follows
- So, each function template or class template needs its own template parameter declaration.

Function templates may also take in non-template parameters
```
#include <iostream>

template <typename T>
void print(T val, int times=1) // even default values allowed.
{
    while (times--)
    {
        std::cout << val;
    }
}

int main()
{
    print(5);      // print 5 1 time
    print('a', 3); // print 'a' 3 times

    return 0;
}
```

Parameter type conversion only occurs during function overload resolution (type promotion can still happen tho), and NOT during template argument deduction.
- Either static cast from caller. (`max(static_cast<double>(2), 3.5)`)
- Provide explicit type template arg in call (`max<double>(2, 3.5)`), no type deduction performed but the double,double template is instantiated.
- It is sometimes necessary for a template to allow the specification of more than one "type template argument".
```
template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // narrowing conversion problem. return value expects int, but double is the result.
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>

    return 0;
}
```

Function templates can be overloaded. 
- The rules for determining which of multiple matching function templates should be preferred are called “partial ordering of function templates”. 
- In short, whichever function template is more restrictive/specialized will be preferred. 
- add<T>(T, T) is the more restrictive function template vs add<T,U>(T,U) (since it only has one template parameter), so it is preferred.

Non-type template parameters are used to pass a function family "meta" value to each function instantiation.

Put all template defintions in a header file
```
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif
```



