/**
 * FILE: 
 * -----
 * Get num as input, return product.
 * ```
 * Enter an integer: 4
 * Double that number is: 8
 * ```
 */
#include <iostream>

int main() {
    std::cout << "Enter number: ";

    int num {};
    std::cin >> num;

    std::cout << "Double that number is: " << num * 2 << "\n";

    return 0;
}