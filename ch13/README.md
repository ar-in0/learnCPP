# Chapter 13: User-Defined Types (Program-Defined Types)
Two categories:
- Enumerated types (including unscoped and scoped enumerations)
- Class types (including structs, classes, and unions).
All program-defined types (i.e. new types) must be defined and given a name before use. (like type aliases `using`)

"the C++20 language standard helpfully defines the term “program-defined type” to mean class types and enumerated types that are not defined as part of the standard library, implementation, or core language. In other words, “program-defined types” only include class types and enum types that are defined by us (or a third-party library)."

Type definition: definition for a user defined type
- TD + name -> valid type. compiler needs to know how much mem to allocate.
## Creating Program Defined Types
Best Practice:
- Name your program-defined types starting with a capital letter and do not use a suffix.
- A program-defined type used in only one code file should be defined in that code file as close to the first point of use as possible.
- A program-defined type used in multiple code files should be defined in a header file with the same name as the program-defined type and then #included into each code file as needed.

## Enumerations
Scoped and Unscoped.
Unscoped enumerations have each enumerator in th esame scope as the defintion
- SO in the same scope, 2 enumerations cannot contain the same enumerator -- name collision
- putting your enumerations inside a named scope region (such as a namespace or class) to avoid name collisions.
- enumerators are constexpr
Enum to string: https://www.learncpp.com/cpp-tutorial/converting-an-enumeration-to-and-from-a-string/

```
// Define a new unscoped enumeration named Color
enum Color
{
    // Here are the enumerators
    // These symbolic constants define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    red,
    green,
    blue, // trailing comma optional but recommended
}; // the enum definition must end with a semicolon

int main()
{
    // Define a few variables of enumerated type Color
    Color apple { red };   // my apple is red
    Color shirt { green }; // my shirt is green
    Color cup { blue };    // my cup is blue

    Color socks { white }; // error: white is not an enumerator of Color
    Color hat { 2 };       // error: 2 is not an enumerator of Color

    return 0;
}
```
- unscoped enumerators will implicitly convert to integral values
Best practice
- Prefer putting your enumerations inside a named scope region (such as a namespace or class) so the enumerators don’t pollute the global namespace.

## Intergral Conversion

Specify underlying type:
```
#include <cstdint>  // for std::int8_t
#include <iostream>

// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
    black,
    red,
    blue,
};

int main()
{
    Color c{ black };
    std::cout << sizeof(c) << '\n'; // prints 1 (byte)

    return 0;
}
```

## Printing enums
- Create a function eg:
```
enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}
```

- Overload the I/O operators

- Overload the unary + operator:

``` c++
#include <type_traits> // underlying_type_t
// Overload the unary + operator to convert an enum to the underlying type
// adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
// In C++23, you can #include <utility> and return std::to_underlying(a) instead
template <typename T>
constexpr auto operator+(T a) noexcept
{
    return static_cast<std::underlying_type_t<T>>(a); //c++23
}

int main()
{
    std::cout << +Animals::elephant << '\n'; // convert Animals::elephant to an integer using unary operator+

    return 0;
}
```


`using enum`: C++20, for scoped enums (enum class)
- using enum <name> to bring enumeratoin into current scope, avoids scope resolutionn operatosr






## 13.8 Struct aggregate initialization
New in C++20: Designated intializers
- Allow you to explicitly define which initialization values map to which members. The members can be initialized using list or copy initialization, and must be initialized in the same order in which they are declared in the struct, otherwise a warning or error will result. Members not designated an initializer will be value initialized.
```
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}
```

`Employee joe {}; // value-initialize all members`


Passing structs to functions
- usually by reference, maybe const refernce
`void printEmployee(const Employee& employee)`: employee isa reference to an Employee constant (i.e. the struct passed in cannot be changed)

- Structs defined inside functions are usually returned by value, so as not to return a dangling reference.

Class Templates
- analogous to function templates, but for types of data members rather than parameters
- Difference: Type defintions (struct) cannot be overloaded...so we need a class generator i.e. template
https://www.learncpp.com/cpp-tutorial/class-templates/

Comining class and fnction tenmplates:

``` c++
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // call to max<double> using template argument deduction (prefer this)

    return 0;
}
```
- use `std::pair`


Class Template Argument Deduction
https://www.learncpp.com/cpp-tutorial/class-template-argument-deduction-ctad-and-deduction-guides/

Use C++20!
Why?
- C++17 class template deduction rules need to be put manually

``` c++
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    
    Pair p2{ 1, 2 };     //ok in c++20, c++17 fails without deduction guid.
    // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    return 0;
}
```

`
