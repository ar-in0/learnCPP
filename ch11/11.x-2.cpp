#include <iostream>
#include <type_traits>  // std::common

//1. Write a function template named add() that allows the users to add 2 values of the same type.

// write your add function template here
template <typename T>
T add(T x, T y) {
    return x + y;
}

// 2. Write a function template named mult() that allows the user to 
// multiply one value of any type (first parameter) and an integer (second parameter). 
// The second parameter should not be a template type. 
// The function should return the same type as the first parameter
template <typename T>
T mult(T x, int y) {
    // return static_cast<T>(x*y); // cast not neccessary, return will always be of t type
    return x * y;
}

// 3. Write a function template named sub() 
// that allows the user to subtract two values of different types.
// ---
// note auto keyword



#if (__cplusplus >= 202002L)
auto sub(auto x, auto y)
{
    std::cout << "abbrev. func template, C++20\n";
	return x - y;
}
#else
template <typename T, typename U>
auto sub(T x, U y) {
    std::cout << "regular func template\n";
    return x - y;
}
#endif


int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}