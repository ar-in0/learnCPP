/**
 * FILE: 1.10-0.cpp
 * ----------------
 * To test some hypotheses about the 
 * return values of `expressions`
 */
#include <iostream>

// std::cout cant be returned as an object.
auto ret_stdout() {
   auto x = 5;
   return (x = 5); // but value assingement returns x
}

int main() {
    
    auto y = ret_stdout();
    std::cout << y << std::endl;
}