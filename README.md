# C++ Guidelines
Compile-Time Options
- Debug mode: `-ggdb`
- Release mode: `-02 -DNDEBUG`
- Warnings: `-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion`
- Warnings as errors: `-Werror`
- Specify C++ Language Standard: `-std=c++17/20/23`
- Expertimental C++ Language Standard: `std=c++2c`

Standard compile: `g++ -ggdb -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror`

Translation unit: Result of pre-processing a single .cpp file (recursively unpacking header contents, etc) into 
a single "combined" file.
- Header files were meant to contain forward declarations of externally linked functions, and const globals.


