All expressions in C++ have two properties: a `type` and a `value category`. (identifiers have duration and linkage)
- `type` of an expression is the type of the object that results upon evaluating that expression.
- `type` of an expression must be determinable at compiletime (although its value need not be - see constexpr).

The value category of an expression (or subexpression) indicates whether an expression resolves to a value, a function, or an object of some kind.
```
int main()
{
    int x{};

    x = 5; // valid: we can assign 5 to x

    // Assignment operator requires the left operand to be a modifiable lvalue expression and 
    // the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression

    return 0;
}
```
Compiler defines rules based on expression value categories to decide what allowed or not (ex. above)

Two kinds of value categories (pre C++):
`lvalues`: "left value"/ "locator value". May be modifiable (non-const) or non-modifiable
- Expression that evaluates to an identifiable object or function or bitfield.
- **"identifiable" entity -> an entity (object, function) that has an address and can be accessed via its address.**
- Entities with identities can be accessed via an identifier, reference, or pointer, and typically have a lifetime longer than a single expression or statement.
```
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression
    return 0;
}

int main()
{
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
```
- lvalues usually have the property of being allocated objects - but the addressablility property is probably the most general trait.

`rvalues`: All expressions that are not lvalues. These evaluate to some value.
- rvalues include literals (except C-style string literals, which are lvalues) and the return value of functions and operators that return by value. 
- Even functions that return rvalues are themsleves rvalues
- Rvalues aren’t identifiable, and only exist within the scope of the expression in which they are used.
```
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```


Operators expect their operands to be rvalues, unless otherwise speccified (ex. `=` assignment)
- For example, binary operator+ expects its operands to be rvalues:

# Rule of thumb
- Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
- Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.

Full list of lvalues and rvalues: https://en.cppreference.com/w/cpp/language/value_category


# C++ Value References
In C++, a reference is an alias for an existing object.
- Actions on reference are direct actions on object
- The type of a reference determines what type of object it can reference.
- lvalue references use the single `&` in type specifier. "const int&" is a reference type, const int is the referenced type.
- `&`: "lvalue refernce to", not "address of" 
- `&&`: "rvalue refernce to", not "reference to refernce"
```
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```

Like constants, all references must be initialized.
- In most cases, a reference will only bind to an object whose type matches the referenced type. (nheritence exceptions)
- The process by which such a reference is bound is called reference binding. 
- The object (or function) being referenced is sometimes called the referent.

**IMPORTANT: Result of a type conversion is always an rvalue**
- Therefore, type match between reference type and referrent is needed
```
int main()
{
    int x { 5 };
    int& ref { x };            // okay: referenced type (int) matches type of initializer

    double d { 6.0 };
    int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
    double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)

    return 0;
}
```

Once initialized, a reference in C++ cannot be reseated, meaning it cannot be changed to reference another object
- Assignments after refernce creation only upate the value of the referrent, and not the properties of the reference itself.

## References aren't objects
. A reference is not required to exist or occupy storage. If possible, the compiler will optimize references away by replacing all occurrences of a reference with the referent.
- You can’t have a reference to a reference, since an lvalue reference must reference an identifiable object, which a reference is not.
```
int var{};
int& ref1{ var };  // an lvalue reference bound to var
int& ref2{ ref1 }; // an lvalue reference bound to var
```

## Assigning dissimilar types to a refernce

"If you try to bind a const lvalue reference to a value of a different type, the compiler will create a temporary object of the same type as the reference, initialize it using the value, and then bind the reference to the temporary."

lvalue refernce to const: `const int&`
- These can be assigned to rvalues, although here a temporary object will be created.
- modifications to the original object will not be reflected by access via refernce, because the referncce aliases a newly created temporary object of same type.

## Utility of References (i.e. variable aliasing)
Declaring functions to take refernce parameters enables pass by reference over pass by value.
- Removes the need for copy, therefore better performance.

lvalue refernce to non-const only allows passing non-const objects by reference (which can subsequently be modified inside the function due to non-cconstness)
- To inclued constants, prefer using lvalue ref to const. (anyways function params are rarely modified inside the func)
```
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```

# Rule of Thumb
- As a rule of thumb, pass fundamental types by value and class types by const reference.
- If you aren’t sure what to do, pass by const reference, as you’re less likely to encounter unexpected behavior.


# C++ Pointers
`&` can be used:
- with type `<type>&` to specify lvalue reference.
- as a unary operator in an expression ex.`&<ident_name>` to return virtual address of that identifier.
- as a binary operator to perform bitwise AND `<ident_1> & <ident_2>`

`*<addr>` is used as the unary derefernce operator - returns value stored at address `addr`.
- The value is returned as an `lvalue`!!! 

```
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer. (ptr is a pointer variable to an int. note * must be near type)

    return 0;
}
```
The type of the pointer has to match the type of the object being pointed to:
```
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object
```

## Pointer behave like lvalue references
(See lvalue-x-ptr.cpp)

Differences
- References must be initialized, pointers are not required to be initialized (but should be).
- References are not objects, pointers are.
- References can not be reseated (changed to reference something else), pointers can change what they are pointing at.
- References must always be bound to an object, pointers can point to nothing 
- References are “safe” (outside of dangling references), pointers are inherently dangerous


Given variable int x, &x returns an int* holding the address of x.
```
#include <iostream>
#include <typeinfo>

int main()
{
	int x{ 4 };
	std::cout << typeid(x).name() << '\n';  // print the type of x
	std::cout << typeid(&x).name() << '\n'; // print the type of &x

	return 0;
}
```

# Dangling Pointer
dangling pointer is a pointer that is holding the address of an object that is no longer valid (e.g. because it has been destroyed).
- You can determine whether an object is destroyed by knowing its duration.

# Pass by <value, reference, address>
- value: make a copy of the original object, pass the copy to the function.
- reference: pass the original object to the function, using the given alias (reference)
- address: We pass the actual 64bit virtual address of the live object to the function.
- Issues: To pass an address -> the passed item must be an lvalue --> functions that are passed parameters by address 
can only take lvalues are parameters.
Best Practice: 
- Prefer std::optional for optional return types.
- Prefer function overloading for optional function parameters (when possible). Allows for rvalue too.
Otherwise, use std::optional<T> for optional arguments when T would normally be passed by value. Favor const T* when T is expensive to copy.
```
#include <iostream>
#include <string>

struct Employee
{
    std::string name{}; // expensive to copy
    int id;
};

void printEmployeeID()
{
    std::cout << "Your ID number is not known.\n";
}

void printEmployeeID(const Employee& e)
{
    std::cout << "Your ID number is " << e.id << ".\n";
}

int main()
{
    printEmployeeID(); // we don't know the Employee yet

    Employee e { "James", 34 };
    printEmployeeID(e); // we know the Employee's ID now

    printEmployeeID( { "Dave", 62 } ); // we can even pass rvalues

    return 0;
}
```


# Const pointer
- A const keyword used to make a pointer function parameter a const pointer provides little value (since it has no impact on the caller, and mostly serves as documentation that the pointer won’t change).
- A const keyword used to differentiate a pointer-to-const from a pointer-to-non-const that can modify the object passed in is significant (as the caller needs to know if the function could change the value of the argument).
```
void foo(const char* source, char* dest, int count);             // Using non-const pointers, all consts are significant.
void foo(const char* const source, char* const dest, int count); // Using const pointers, `dest` being a pointer-to-non-const may go unnoticed amongst the sea of spurious consts.
```
- In the former case, it’s easy to see that source is a pointer-to-const and dest is a pointer-to-non-const. 
- In the latter case, it’s much harder to see that dest is a const-pointer-to-non-const, whose pointed-to object can be modified by the function!
- `const char* const source`: const pointer to const. (i.e. cannot reassign source ka value, cannot modify the char stored at the address pointed to by source.)

## Best Practice
- Prefer pointer-to-const function parameters over pointer-to-non-const function parameters, unless the function needs to modify the object passed in.
Do not make function parameters const pointers unless there is some specific reason to do so.

- “Pass by reference when you can, pass by address when you must”.


## Changing what a pointer parameter points at
- Pass by address creates a copy of the object address. So reassigning in the function will only change address
of the copy, not the original ptr object.

- To actually modify the original, we'd need to pass the pointer by refernce (LOL)
```
#include <iostream>

void nullify(int*& refptr) // refptr is now a reference to a pointer
{
    refptr = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```

## Return by reference, return by address
https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/
k


## std::optional (C++17 onwards)
- a `std::optional<T>` can either have a value of type T, or not
Best Practice: Return a `std::optional` (instead of a sentinel value) for functions that may fail, unless your function needs to return additional information about why it failed.
```
We can construct a std::optional<T> either with or without a value:

std::optional<int> o1 { 5 };            // initialize with a value
std::optional<int> o2 {};               // initialize with no value
std::optional<int> o3 { std::nullopt }; // initialize with no value
To see if a std::optional has a value, we can choose one of the following:

if (o1.has_value()) // call has_value() to check if o1 has a value
if (o2)             // use implicit conversion to bool to check if o2 has a value
To get the value from a std::optional, we can choose one of the following:

std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
```
- Dereferencing a `std::optional` that does not contain a value is undefined behavior.
- See std::expected for C++23 