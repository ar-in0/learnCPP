// IO buffering
#include <iostream>  // for std::cout and std::cin

int main() {
    std::cout << "Enter two numbers: "; // 2 3

    int x{};
    std::cin >> x; // first number extracted from buffer, stored in x. (buffer still has 2nd num)
    std::cout << "Val entered " << x << std::endl;
    // while(1) {};

    int y{};
    std::cin >> y; // no waiting for input, the leftover 2nd num is sent automatically.

    std::cout << "You entered " << x << " and " << y << '\n';

    return 0;
}