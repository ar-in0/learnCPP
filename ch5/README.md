# Constant Variables (named constants)
Constant: A value that may not be changed during program execution.
C++ has:
- named constants: constant values that are associated with an identifier (ex. a = some_constant_value).
- literal constant: constant values not associated with an identifier (ex. some_constant_value)

named constants: constant variables, object-like macros with subst. text, enumerated constants.
non constant variables: value can be changed at any time via assignemnt.
```C++
// non-const variables
int main()
{
    int x { 4 }; // x is a non-constant variable
    x = 5; // change value of x to 5 using assignment operator

    return 0;
}
```

```C++
// const variable declaration, "const" keyword is called the "const qualifier"
const double gravity { 9.8 };  // preferred use of const before type. Type of gravity == [const double]
int const sidesInSquare { 4 }; // "east const" style, okay but not preferred

// - const variables must be initialized upon definition.
const double gravity;
gravity = 9.99; // error!

// const variables can be initialized from other (even non-const!) variables
int age = 77;
const int constAge {age};

// const variables cannot be modified
age = 88; // OK
constAge = age // NOT OK


// const function parameters
// - no explicit initializer passed to the const variable x that is used as a function parameter.
// - This is OK, since the variable is only defined when called, at which point the passed value
// is used to initialize the const x.
// ---
// HOWEVER, when passing arguments to function by value, using const is redundant.
// - pass by value makes a copy of the passed in value, so it doesnt matter whethter the function
// modifies it. 
// - however, using pass by reference and by address we need to place invariants on the value of the 
// passed in variable.
void printInt(const int x) // x is a "value parameter"
{
    std::cout << x << '\n';
}

printInt(5); // 5 used as the initializer to x
printInt(8); // 8 used as the initializer to x
```
Best practice: Make variables constant whenever possible. 
- Exception cases include by-value function parameters and by-value return types, which should generally not be made constant.
- Prefer constant variable over object-like macros (see ex 5.1-0.cpp)

Type qualifiers: keyword that is applied to a type that modifies how that type behaves
C++23 has 2 type qualifiers: ("cv-qualifiers")
- `const`: used to declare a constant variable.
- `volatile`: used to tell the compiler that an object may have its value changed at any time. Disables some optimizations.

# Literals
Literals are values that are inserted directly into the code. AKA literal constants, since meaning cannot be redefined.
```C++
return 5;                     // 5 is an integer literal
bool myNameIsAlex { true };   // true is a boolean literal
double d { 3.4 };             // 3.4 is a double literal
std::cout << "Hello, world!"; // "Hello, world!" is a C-style string literal
```

The type of a literal is dedeuced from its value.
```
integer value	        5, 0, -3	    int	
boolean value	        true, false	    bool	
floating point value	1.2, 0.0, 3.4	double (not float!)	
character	            ‘a’, ‘\n’	    char	
C-style string	        “Hello, world!”	const char[14]
```

Literal suffixes: Can be appended to a literal if the default type is not what the desired type.
```
Data type	Suffix	                                Meaning
integral	u or U	                                unsigned int
integral	l or L	                                long
integral	ul, uL, Ul, UL, lu, lU, Lu, LU	        unsigned long
integral	ll or LL	                            long long
integral	ull, uLL, Ull, ULL, llu, llU, LLu, LLU	unsigned long long
integral	z or Z	                                The signed version of std::size_t (C++23)
integral	    uz, uZ, Uz, UZ, zu, zU, Zu, ZU	    std::size_t (C++23)
floating point	f or F	                            float // most commonly used.
floating point	l or L	                            long double
string	s	                                        std::string
string	sv	                                        std::string_view
```
- suffixes are most often used in cases where type deduction is involved. (CTAD 13.14, auto keyword 10.8)
```C++
    int a { 5 };          // ok: types match
    unsigned int b { 6 }; // ok: compiler will convert int value 6 to unsigned int value 6
    long c { 7 };         // ok: compiler will convert int value 7 to long value  7

    std::cout << 5.0 << '\n';  // 5.0 (no suffix) is type double (by default)
    std::cout << 5.0f << '\n'; // 5.0f is type float
    float f {4.1} // error, float -double
    float f {4.1f} // no error
```

### String Literals
- A string is a collection of sequential characters used to represent text. (ex `"hello world"`) --> double quotes for strings, single quotes for char.
- C++ uses C-style strings: implicit null terminator, so "hello world" is of type `const char[14]` and not `const char[13]`.
- C-style string literals are const objects, guaranteed to exist for the duration of the program.
- `std::string` and `std::string_view` create temporary objects --> must be used immediately as they are destroyed at the end of the full expression
in which they are created (???)

https://www.learncpp.com/cpp-tutorial/numeral-systems-decimal-binary-hexadecimal-and-octal/ : Number systems in C++ reference.
https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/ : compile-time optimizations.

```C++
// Compile-time and runtime constants in C++
#include <iostream>

int five()
{
    return 5;
}

int pass(const int x) // x is a runtime constant. It is set to a value at runtime, not before that, and has the const keyword.
{
    return x;
}

int main()
{
    // The following are non-constants:
    [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    // value is determined in a runtime context.
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value of five() isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value of pass(5) isn't known until runtime

    return 0;
}
```
- 'as-if' Rule: The as-if rule says that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program’s “observable behavior”.

- Compile-time programming: The use of language features that result in compile-time evaluation. The features make it explicit to the compiler that compile-time
eval is required, ensuring that the programmer and compiler are on the same page.
```
Constexpr variables (discussed in upcoming lesson 5.6 -- Constexpr variables).
Constexpr functions (discussed in upcoming lesson F.1 -- Constexpr functions).
Templates (introduced in lesson 11.6 -- Function templates).
static_assert (discussed in lesson 9.6 -- Assert and static_assert).
```

## Constant expressions
https://www.learncpp.com/cpp-tutorial/constant-expressions/
- standard defines "constant expressions" rather than "compile-time xxx": These are expression that must be evaluatable at compile-time.
- In a constant expression (non-empty sequence of literals, variables, operators, and function calls) each part of the expression must be evaluatable at compile-time.
- if a constant expression is required somewhere, compiler will inform.

A few common cases where a compile-time evaluatable expression is required:
- The initializer of a constexpr variable (5.6 -- Constexpr variables).
- A non-type template argument (11.9 -- Non-type template parameters).
- The defined length of a std::array (17.1 -- Introduction to std::array) or a C-style array (17.7 -- Introduction to C-style arrays).

"The compiler is only required to evaluate constant expressions at compile-time in contexts 
that require a constant expression (such as the initializer of a constexpr variable)"

```C++
// constant and non-constant (runtime) expressions
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```
- The compiler is only required to evaluate constant expressions at compile-time in contexts that require a constant expression. (manifestly constant-evaluated expression)
```C++
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```

The likelihood that an expression is fully evaluated at compile-time can be categorized as follows:
- Never: A non-constant expression where the compiler is not able to determine all values at compile-time.
- Possibly: A non-constant expression where the compiler is able to determine all values at compile-time (optimized under the as-if rule).
- Likely: A constant expression used in a context that does not require a constant expression.
- Always: A constant expression used in a context that requires a constant expression.

# Constant identifiers and compile-time optimization
Use of constants guarantees to the compiler that the value of this ident will not change in the future, therefore the compiler can more reliably perform constant folding, dead-code elim optimizations.
- Expressions are evaluated either at runtime or compile time. 
- constant expression is a non-empty sequence of literals, constant variables, operators, and function calls, all of which must be evaluatable at compile-time

Const identifiers can be used in compile-time (i.e. constant) expressions. Therefore, these must always be compile-time evaluated
```
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```
- only const *integral* variables with a constant expression initializer are compile-time constants (i.e. constant expressions).


# Constexpr Variables
Uniform way to create variables that can be used in compile-time expressions (i.e. constant expressions), towards a method to ensure code executes at compile time.
- `constexpr` keyword is used to define non-integer compile-time constants
```
constexpr double d { 1.2 }; // d can be used in constant expressions!
```
`const` means that the value of an object cannot be changed after initialization. The value of the initializer may be known at compile-time or runtime. The const object can be evaluated at runtime.
- Any constant variable whose initializer is not a constant expression (making it a runtime constant) should be declared as const.

`constexpr` means that the object can be used in a *constant expression*. The value of the initializer must be known at compile-time. The constexpr object can be evaluated at runtime or compile-time
- Any constant variable whose initializer is a constant expression should be declared as constexpr.

```
Term	                Definition
Compile-time constant	A value or non-modifiable object whose value must be known at compile time (e.g. literals and constexpr variables).
Constexpr	            Keyword that declares objects as compile-time constants (and functions that can be evaluated at compile-time). Short for “constant expression”.
Constant expression	    An expression that contains only compile-time constants and operators/functions that support compile-time evaluation.
Runtime expression	    An expression that is not a constant expression.
Runtime constant	    A value or non-modifiable object that is not a compile-time constant.
```

## 5.7 Intro to std::string
An alternative to C-style string literals is required for C++ (that is easier and safer to work with)
- `std::string` and `std::string_view`: "Class types" rather than fundamental types.
```C++
#include <string>

std::string name {} // empty string.
std::string my_name {"armaan"} // initialize with string literal
my_name = "armaan chowfin" // change name. The std::string class takes care of any memory alloc/deallocs.
```

## 5.8 std::string_view
```C++
// initializer = 5 (a literal)
// when this line is executed, the initialization value
// is copied to the memory allocated for variable int x
// - This copy is fast for fundamental types
int x {5}

// slow copy of the initializer (a C-style string literal)
// alternatives are required.
// - 
// https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/
// if the initializer is a temp object ex. sstring literal, it
// will be destroyed after initialization.
std::string s{ "Hello, world!" }; 
```
Need to minimize copies of std::strings
```C++
// C++17: std::string_view
#include <string_view>

// no copy of s is made. _s parameter is initialized
// from s without copy
void printSV(std::string_view _s) {
    std::cout << _s << '\n';
}

std::string hello = "hello";
// s is an object that gives the caller a read-only view of the string literal.
std::string_view s{ hello }; // s is viewing "hello"

s = "hello brozki" // s is viewing "hello brozki", stored in the .txt section of the ELF.

s = name // sv now viewing "hello", but the brozki literal will have to be re-assigned if required.

// no copy of s is made.
printSV(s);
```

```C++
// string view from C-style literals
// use the sv suffix
using namespace std::string_literals;      // access the s suffix
using namespace std::string_view_literals; // access the sv suffix

std::cout << "foo\n";   // no suffix is a C-style string literal
std::cout << "goo\n"s;  // s suffix is a std::string literal
std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

// constexpr is preferred. marks s as compile-time evaluatable expression.
constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
```

### Safe usage of std::string_view
- Part of a larger set of `view` types.

Owners and Viewers:
- Owner: Responsible for acquire, manage, and properly dispose of the objects you own
- Viewer: Inexpensive, no responsibility for the objects you are viewing, but you also have no control over those objects

> In programming, when we call an object an owner, we generally mean that it is the sole owner (unless otherwise specified). Sole ownership (also called single ownership) ensures it is clear who has responsibility for that data.

> A view is dependent on the object being viewed. If the object being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.
- A `std::string_view` that is viewing a string that has been destroyed is sometimes called a dangling view.

Best practices:
- Use string_view over const std::string&

```C++
// improper usage
#include <iostream>
#include <string>
#include <string_view>

std::string getName() {
    std::string s { "Alex" };
    return s;
}

int main() {
    // Return values are temporary objects that are destroyed at the end of the full expression containing the function call. 
    // We must either use this return value immediately, or copy it to use later.
    // it is essentially filling up %r9 with the std::string, but %r9 is cleared
    // so the string that name is viewing is also lost.
    // --------------------------------------------------------------------------
    // Q. but isnt there a copy of the return value being made in the initializer?
    // A. NO. Copy would be made if:
    // ```
    // std::string str = getName(); // copy made
    // std::string_view name = str; // assignment
    // std::cout << name;
    // ```
    // --------------------------------------------------------------------------
    // No copy of return value is created.
    std::string_view name { getName() }; // name initialized with return value of function
    std::cout << name << '\n'; // undefined behavior

    return 0;
}
```
https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/
Key takeaways: 
- The initializer of the string_view must outlive the string_view, or be a string literal.
- Modifying a std::string is likely to invalidate all views into that std::string
- string_view can view a substring 




