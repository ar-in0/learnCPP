# Constant identifiers and compile-time optimization
Use of constants guarantees to the compiler that the value of this ident will not change in the future, therefore the compiler can more reliably perform constant folding, dead-code elim optimizations.
- Expressions are evaluated either at runtime or compile time. 
- constant expression is a non-empty sequence of literals, constant variables, operators, and function calls, all of which must be evaluatable at compile-time

Const identifiers can be used in compile-time (constant) expressions. Therefore, these must always be compile-time evaluated
```
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```
- only const *integral* variables with a constant expression initializer are compile-time constants.

# Constexprs
Uniform way to create variables that can be used in compile-time expressions, towards a method to ensure code executes at compile time.
- `constexpr` allows us to define non-integer compile-time constants
```
constexpr double d { 1.2 }; // d can be used in constant expressions!
```
`const` means that the value of an object cannot be changed after initialization. The value of the initializer may be known at compile-time or runtime. The const object can be evaluated at runtime.
- Any constant variable whose initializer is not a constant expression (making it a runtime constant) should be declared as const.

`constexpr` means that the object can be used in a *constant expression*. The value of the initializer must be known at compile-time. The constexpr object can be evaluated at runtime or compile-time
- Any constant variable whose initializer is a constant expression should be declared as constexpr.

