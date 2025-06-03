# Namespace Guidelines
Namespaces: Help avoiding name collisions in large C++ projects.

`A::b` is the scope resolution operator. Compiler looks for the definition of `b` in the `A` namespace.
- `::b`: Compiler looks for the definition of `b` in the global namespace.
- identifiers declared in global namespace are visible from time they are declared to end of the FILE in which they were declared.
(global namespace scope/file scope).
- Identifiers in user-defined namespaces (that is defined in global scope) are also part of global scope (i.e. they are accessible 
from anywhere in the file, albeit with the `A::b` syntax).
- *Best Practice*: Define global variables inside a namespace rather than simply in the global namespace.

Namespaces and their members can be declared in a `.h` file, and defined in a seperate `.cpp` file.
- Functions declared in a `.h` namespace must be defined in same namespace in the `.cpp` file. (and vice-versa
for forward declarations). Failure to do so will lead to compiler or linker errors depending on function invocation.

Namespace blocks themselves can be declared across multiple header/source files
- The set of items belonging to (logical)namespace `A` is the union of items declared in every
namespace across the project with name `A`.
- C++ STL splits single namespace functionality across multiple header files.

Namespace aliases can be used to reduce typing required to refer to an item in a nested namespace.
```
namespace Foo::Goo {
    // define add(), i.e. Foo::Goo::add()
}

// Alias assignment
namespace FGAlias = Foo::Goo;

FGAlias::add() // instead of Foo::Goo::add()
```
- Aliases help with development, because only one alias needs to be reassigned if ever the functionality in `Foo::Goo` is moved to some other namespace, say `V2`.

Unnamed (anon) namespaces mark all its identifiers as internally linked.
- Helps when theres a lot of idents, and you dont want to use static on all.

# Identifiers and Scope Guidelines
https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/
Identifiers have two properties: `duration` and `linkage`.
- Automatic duration: identifier is destroyed at the end of the block in which it was defined.
- No Linkage: If the same identifier is declarated in seperate blocks, each refers to a different object.
- Local identifiers have no linkage.

Internal Linkage: identifier visible only to its own translation unit. Marked by `static`.
- `const, constexpr` globals are internally linked by default (no static reqd). Reason: Enforces assignment of initializer value
at declaration. (well-defined b4 compilation). To make these external, use `extern` keyword.
- non-const globals are externally linked by default (`static` required to label as internally linked)
```
// `extern` is used to create a forward declaration for externally-linked identifiers
// and also to mark identifiers as externally-linked.
//---main.cpp
int g_x;
const int g_y {3}; // internal by default. const idents must be initialized.
extern const int g_z {4}// made external, usable in other files after forward declaration.

//---a.cpp
extern int g_x; // forward decl of non-const global g_x
// -- g_y cannot be accessed in other source files --
extern const int g_z; // forward decl of externed const global g_z
```

`static` local variables: Can be used as id trackers. Initialized just once, and only destroyed at the end of program.

# Inline Function Guidelines
"The compiler needs to be able to see the full definition of an inline function wherever it is used, 
and all definitions for an inline function (with external linkage) must be identical (or undefined behavior will result)"
- *Best Practice*: Do not use the inline keyword to request inline expansion for your functions.

C++17 new addition: inline *variables*. 
- Variables that can have more than one definition, so long as those definitions are identical.
- Useful for sharing symbolic global constants.
- inline variables have external linkage by default.
