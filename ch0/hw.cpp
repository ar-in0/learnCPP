#include <iostream>
#include <limits>
#include <print>

int main() {
    #if (__cplusplus >= 202302L)
        std::println("hello from print");
    #elif (__cplusplus < 202302L)
        std::cout << "Hello World" << std::endl;
    #endif

    std::cin.clear(); // reset error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // get one or more char from user (wait for enter)

    return 0;
}