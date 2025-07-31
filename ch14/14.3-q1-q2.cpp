/*
 * Create a struct called IntPair that holds two integers. Add a member function named print that prints the value of the two integers.
 * The following program function should compile:
*/

#include <iostream>
// #include <stdbool.h> // not required in C++ to use boolean.

// new: 
// note that typedef is not required in C++
struct IntPair {
    int i_0 {};
    int i_1 {};

    void print(void) {
        std::cout << "Pair(" << i_0 << ", " << i_1 << ")" << std::endl;
    }

	bool isEqual(IntPair& p) {
		return true ? (i_0 == p.i_0 && i_1 == p.i_1): false;
	}
};

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}