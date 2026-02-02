#include <iostream>

int main() {
    // Const integral variables with a constant expression initializer can be
    // used in constant expressions:
    const int a{5};  // a is usable in constant expressions, a is a const
                     // integral variable
    [[maybe_unused]] const int b{
        a};  // b is usable in constant expressions (a is a constant integral
             // variable i.e. it is a constant expression and is used as initializer for b
             // as seen)
    [[maybe_unused]] const long c{
        a + 2};  // c is usable in constant expressions (operator+ has constant
                 // expression operands)

    // Other variables cannot be used in constant expressions (even when they
    // have a constant expression initializer): const int d {};
    int d{};
    std::cin >> d;  // fails to compile when d is const.
    [[maybe_unused]] const int e{
        d};  // e is not usable in constant expressions (initializer is not a
             // constant expression)
    [[maybe_unused]] const int e_prime{
        e};  // declarations compile, but usage where a constant expression
             // (constexpr) is expected will fail to compile?

    [[maybe_unused]] const double f{
        1.2};  // f is not usable in constant expressions (not a const integral
               // variable)

    // See comments at:
    // https://www.learncpp.com/cpp-tutorial/constant-expressions/
    // - compiler optimizations occur even at -O0
    // --------------------------------------------------------------
    // https://en.cppreference.com/w/cpp/language/constant_expression.html
    // - types of constexpr
    // --------------------------------------------------------------
    // if array is unused, unassigned, the std::cin is optimized away by default
    // (-O0 prevents this)
    // - cannot reproduce the std::cin issue
    [[maybe_unused]] int array[e_prime];  // no fail? becuase compiler is being
                                          // easier than the c++ standard.
    // array[0] = 42;
    // std::cout << array[0] << std::endl; // use the set array variable
}
