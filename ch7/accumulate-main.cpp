#include <iostream>

static int accumulate(int x) {
    static int y {0}; // updates to y persist across function calls.
    y += x;
    return y;
}

int main()
{
    std::cout << accumulate(4) << '\n'; // prints 4
    std::cout << accumulate(3) << '\n'; // prints 7
    std::cout << accumulate(2) << '\n'; // prints 9
    std::cout << accumulate(1) << '\n'; // prints 10

    return 0;
}