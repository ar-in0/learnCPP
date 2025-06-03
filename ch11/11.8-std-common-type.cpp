#include <iostream>
#include <type_traits> // for std::common_type_t

// If we need a function that can be forward declared, 
// we have to be explicit about the return type.
template <typename T, typename U>
auto max(T x, U y) -> std::common_type_t<T, U>; // returns the common type of T and U

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}

template <typename T, typename U>
auto max(T x, U y) -> std::common_type_t<T, U>
{
    return (x < y) ? y : x;
}

// C++20
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}