# Chapter 14: Introduction to Classes
C++ Object: a piece of memory that can be used to store values. 
Variable/Indentifier: Obj with a name
OOP: ` inheritance, encapsulation, abstraction, and polymorphism.`: Techniques to ensure modularity+extensibility of code.

Class Invariant enforcement: Lacking with aggregates (i.e. data-only structs). Therefore, `Classes`
- class invariant: Condition that must be true throughout the lifetime of the object - if not, object cannot be considered a valid instance of that class. (invalid state - UB may arise)
- example:Fraction representation must maintain the invariant that the denom !=0. Aggregate struct is not capable of this, but a Class is!
Workaround: Rely on user-defined functions to enforce class invariants, BUT THIS IS PROBLEMATIC/SUB-OPTIMAL

UB with class member declaration  order: See https://www.learncpp.com/cpp-tutorial/member-functions/
- Data members are alwyas initialized in the order of declaration. 
- methods can be defined to use data members before they are initialized, BUT data members being initialized with a non-initialized member is undefined behaviour

``` c++
class A {
// --OK--
int getf() { return m_getf} 
m_getf {5};
// --OK--, compiler forward declares any methods that use non-declared data members and defines the methods below class defintion via A::getf()
}

class B {
// --NOT-OK--
int getf() {return m_getf}
m_getf {m_getfHelper};
m_getfHelper {6};
// -- NOT-OK--, m_getfHelper initialized after m_getf declaration, undefinedd behaviour
}

class C {
// --NOT-OK--
int m_getf {getfHelper()};
int getfHelper() { return 5};
// --NOT-OK--, initializer of m_getf (i.e. getfHelper()) is declared after m_getf
}

```

* If a class type does not need data members, it is better to uuse a namespace.

**Const class objects, const member functions**
Recall const variables: named objects that cannot be modified after creation. Must be initialized at declaration time.
Rules: If an object is declared as const:
1. Methods that modify/directly modifying a member of that object causes compiation error
2. ! Calling a non-const member function also causes compile error (even if the function does not access any data member), i.e. non-const member functions cannot access non-const data members or non const member functions
- Solution: `const` member function:
Do: `void print() const {} // const member function` instead of `void print() {} // non-const member function` 
- If member function defined in different file (outside the class defintion), same rule must be followed
- For a const object, const member functions cannot call non-const member functions/variables or modify the constant implicit object. 
Howver they can call non-const methods that arent of the class. (i.e. const only applies to members)
- const member function of a non-const object can modify the implicit object.
Therefore best practice:
> A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both const and non-const objects.

**Const objects via pass by const reference**
More common technique to pass constant (const) objects to functions.
Why? Pass by value creates a copy, so anyways that fucntion cant modify the original object. So just pass a const reference to the function,
this avoids the copy and also maintains the invariant that the passed object cannot be modified. (see https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/)


**Access specifiers (Public private)**
- Each member of a class has an "access level" property that determines who can access the member (orthogonal to the const/non-const ideas)
- Members of struct are public by defautlt, members of class are private by default.
- Classes (with private members) cannot be aggregate-initialized.

``` c++
class A {
int m_p1; // private by default
int m_p2; // private by default
}

int main() {
A a {0, 1}; // compile error, private member variables cannot be aggegate initialized, by the public main. Therefore, need to use constructor!
}
```
Prefixes: m_ for private member, s_ for local static vars, g_ for global

Using access specifiers:

``` c++
class Date {
// Any members defined here would default to private
public: // here's our public access specifier
    void print() const {// public due to above public: specifier 
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
private: // here's our private access specifier
    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main() {
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
``` 

Best practices: 
- classes should have private /protected member variables and public member functions
- structs should have no access specifiers.

**Access levels between two classes/objects**
Access levels are defined for a class and the rule is upheld by every object of that class
- Therefore an object instance of class A can call the private attribute of a different object instance of class A with no issue (assuming objects are in scope).

**Access Functions (getters and setters)**
- Trivial public member functions that can return the value of/mutate the value of a private member variable.
- getters should be `const`: Allows them to retrieve const data members (non-const getters cannot access const members). Should return by value of const lvalue reference (see next section)
- setters should be non-`const`: Should not be able to set/modify const data members

**Member functions returning references to data members**
  Return by reference requirement: object being returned must exist after function returns
  - Can return function params that were passed by refernce (their object lie outside the function), can also return reference to vairables with static duration (static local or global vars) - these are not destroyed till program ends.
  
For member functions, data members are better returned by (const lvalue) reference (since data members are often large, expensive copy)
- The lifetime issue: Handled, since member functinos can be called only on objects, and the members are valid as long as the object is.
`const std::string& getName() const`: Const member function (const at end - allows the function to access const data members) that returns by const lvalue reference (first const, is )
https://stackoverflow.com/questions/21778045/c-return-value-reference-const-reference
- Return by value: make a copy, might be expensive
- Return by (non-const) reference: Returns an alias for the object, so we can modify that object via the alias
- Return by const referencce: The object cannot be modified by the returned alias, i.e. the object is marked as const.
- Can return const reference to const and non-const object, but can return non-const reference only to a non-const object, so _just make the returned reference const_ unless
there is a real need to modify the object via returned alias (sometimes for `operator=` definitions, see link).
> The return type of a member function returning a reference to a data member should match the data member’s type (i.e. dont return string_view&, return (const) string&)

* rvalue objects should not be returned by reference - they are destroyed at the end of the expression unless some special scenario.

``` c++
#include <iostream>
#include <string>
#include <string_view>

class Employee {
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name) {
	Employee e;
	e.setName(name);
	return e;
}

int main() {
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();
    
	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
    // 
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member
	return 0;
}
```

> In case 2, we run into problems. First, createEmployee("Garbo") returns an rvalue object. We then call getName() to get a reference to the m_name member of this rvalue. This m_name member is then used to initialize ref. At this point, the full expression containing the call to createEmployee("Garbo") ends, and the rvalue object and its members are destroyed. This leaves ref dangling. Thus, when we use ref in the subsequent statement, we’re accessing a dangling reference, and undefined behavior results.


**Do not return non-const references to private data members**
- This would allow you to modify the value of private members from public, i.e. subverting the access control systems 

**Const member functions can’t return non-const references to data members**

14.8: Data hiding aka encapsulation
- To maintain the seperation of interface from implementation, make details of implementation inaccessible to users of the innterface, i.e. via `private`
- Also why its better to implement a fucntion as a non-member if possible, to avoid complicating the interface.
https://embeddedartistry.com/fieldatlas/how-non-member-functions-improve-encapsulation/

Order of member declaration:
> Declare public members first, protected members next, and private members last. This spotlights the public interface and de-emphasizes implementation details.
Google C++ Style Guide:

```.txt
The following order is recommended by the Google C++ style guide:

- Types and type aliases (typedef, using, enum, nested structs and classes, and friend types)
- Static constants
- Factory functions
- Constructors and assignment operators
- Destructor
- All other functions (static and non-static member functions, and friend functions)
- Data members (static and non-static)
```

