/**
 * FILE: q1.cpp
 * ------------
 * Write a program that asks the user to enter two integers, one named smaller, the other named larger. 
 * If the user enters a smaller value for the second integer, use a block and a temporary variable 
 * to swap the smaller and larger values. Then print the values of the smaller and larger variables. 
 * Add comments to your code indicating where each variable dies. 
 * Note: When you print the values, smaller should hold the smaller input and 
 * larger the larger input, no matter which order they were entered in.
 */
#include <iostream> 

// pass -DSTD_UTILITY at compile time
#ifdef STD_UTILITY
#include <utility>
#endif

int main(int argc, char *argv[]) {
    (void)argc, (void)argv;
    int smaller {};
    int larger {};
    std::cout << "Enter smaller: ";
    std::cin >> smaller;

    std::cout << "Enter larger: ";
    std::cin >> larger;

    if (smaller > larger) {
        std::cout << "Swapping values" << std::endl;
        int temp {smaller};
        smaller = larger;
        larger = temp;

#ifdef STD_UTILITY
        std::cout << "Using std::swap\n";
        std::swap(larger,smaller);
#endif


    } // temp dies

    std::cout << "Smaller: " << smaller << std::endl;
    std::cout << "Larger: " << larger << std::endl;

    return 0;

} // smaller, larger die