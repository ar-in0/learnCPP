#include <iostream>

const int num_stds = 7;

const long std_code[num_stds] = {199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L};

const char* std_name[num_stds] = { "Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26" };

long get_CPP_std() {
#if defined (_MSVC_LANF)
    return _MSVC_LANG; // MSVC doesnt support the standard-recommended __cplusplus.
#elif defined (_MSC_VER)
    return -1;
#else
    return __cplusplus; // 
#endif
}

int main() {
    long _std = get_CPP_std();

    if (_std == -1) {
        std::cout << "Error: STD not determined.\n";
        return 0;
    }

    for (int i = 0; i < num_stds; i++) {
        if (_std == std_code[i]) {
            std::cout << "Compiler uses " << std_name[i] << 
            "(language standard code " << _std << "L)\n";
            break;
        }

        if (_std < std_code[i]) {
            std:: cout << "Compiler uses preview/pre-release of " << std_name[i] <<
            "(Language standard code " << _std << "L)\n";
        }
    }

    return 0;
}