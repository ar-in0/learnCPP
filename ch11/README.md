https://www.learncpp.com/cpp-tutorial/chapter-11-summary-and-quiz/

# Function overloading
Function overloading allows the programmer to define functions with the same name, as long as its
parameters (#params, types) differ (i.e. functions are differentiated).
- Return type is not a differentiator.
- const can be a differentiator.

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



