// To demonstrate a pitfall of using std::string with std::cin
// and a solution using std::getline()
#include <iostream>
#include <string>

void get_name_naive() {
    std::cout << "Enter your full name: ";
    std::string name{}; // armaan chowfin
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';
}

void get_name_std_getline() {
    std::cout << "Enter your full name: ";
    std::string name{};

    // std::ws
    // - input manipulator, tells std::cin to ignore any leading whitespace before extraction.
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';
}

int main()
{
    #ifdef GETLINE // -DGETLINE
        get_name_std_getline();
    #else
        get_name_naive();
    #endif

    return 0;
}