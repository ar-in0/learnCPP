#include <iostream>
#include <cstdlib>

// this function now returns an integer value
int get_user_val() { 
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input; // return the value the user entered back to the caller (return by value i.e. A copy of `input` is returned)
}

int main() {
	int num { get_user_val() }; // list-initialize num with the return value of getValueFromUser()

	std::cout << num << " doubled is: " << num * 2 << '\n';

	return EXIT_SUCCESS;
}