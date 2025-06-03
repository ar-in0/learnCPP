#include <iostream>
#include <typeinfo>

int main()
{
    // g++: i,
    //      Pi
	int x{ 4 };
	std::cout << typeid(x).name() << '\n';  // print the type of x
	std::cout << typeid(&x).name() << '\n'; // print the type of &x

	return 0;
}