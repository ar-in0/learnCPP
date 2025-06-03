#include <iostream>

int a;         // default-initialization (no initializer)

// Traditional initialization forms:
// b,c,d are identical init methods in most cases
int b = 5;     // copy-initialization (initial value after equals sign)
int c ( 6 );   // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
int d { 7 };   // direct-list-initialization (initial value in braces)
int e {};      // value-initialization (empty braces)

int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

int main() {
    int width { 5 };    // define variable width and initialize with initial value 5
    std::cout << width << std::endl; // prints 5

    return 0;
}