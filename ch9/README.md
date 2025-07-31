# Error Detection and Handling
Software testing (also called software validation) is the process of determining whether or not the software actually works as expected 
under a wide variety of conditions.
- This chapter contains practical tips for devs.

## 1. Test your program in small pieces
When you're modifying legacy software, the best practice is to write your program in small, well defined units (functions or classes), compile often, and test your code as you go.
- Most planning should/will go into breaking up your solution into minimal, testable components. Then, you test each component/functionality
enabled by that component individually. Such tests are called Unit Tests.

## How To Test?
a. Write a test function that invokes and validates the behaviour of the newly added component.
- To validate a returned value, the best practice is to use `assert`s.

`assert`: Cause the program to abort with an error message if any test (assertion) fails
```
#include <cassert> // for assert
#include <cstdlib> // for std::abort
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Program will halt on any failed test case
int testVowel()
{
#ifdef NDEBUG
    // If NDEBUG is defined, asserts are compiled out.
    // Since this function requires asserts to not be compiled out, we'll terminate the program if this function is called when NDEBUG is defined.
    std::cerr << "Tests run with NDEBUG defined (asserts compiled out)";
    std::abort();
#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('b'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('y'));
    assert(!isLowerVowel('z'));

    return 0;
}

int main()
{
    testVowel();

    // If we reached here, all tests must have passed
    std::cout << "All tests succeeded\n";

    return 0;
}
```

## 9.2 Code Coverage
The term code coverage is used to describe how much of the source code of a program is executed while testing.
Coverage is dependent on your **test inputs**. 

## Statement, Branch, Loop Coverage
- Statement: "Is every line of the function being touched in a run with my provided inputs? If yes, 100% statement coverage.
If no, need to devise a new input that touches the rest of the statements.

- Branch: "Is every branch decision covered by my set of inputs?" Aim for 100% branch coverage always. 
Higher priority than statement coverage. "Branch coverage is the percentage of branches that have been executed, with the affirmative case and negative case counting separately"

- Loop: Called the "0,1,2 test". If you have a loop in your code, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times. 
If it works correctly for the 2-iteration case, it should work correctly for all iterations greater than 2. (induction)

### Testing Input Categories
- Test the component using a representative input of a particular category. Input categories are dependent on the semantics of the
component being tested.

Above are a set of heuristics for choosing minimal sets of test inputs.

## 9.3 Common Semantic Errors in C++
https://www.learncpp.com/cpp-tutorial/common-semantic-errors-in-c/
- just go through this list

## 9.4 Detecting and handling errors
Most errors occur due to faulty assumptions made by the programmer and/or a lack of proper error detection/handling.

- A sentinel value is a value that has some special meaning in the context of a function or algorithm. Can be used to indiccate error to
caller, in case valid outputs are always different from the sentinel.

# 9.5 `std::cout` vs `std::cerr`
- Use std::cout for all conventional, user-facing text, and normal user-facing error messages.
- Use std::cerr or a logfile for status and diagnostic information that may be helpful for diagnosing issues but probably isn’t interesting for normal users. 
- For a non-interactive program (tool or service), use std::cerr for error output only (e.g. could not open file x). This allows errors to be displayed or parsed separately from normal output.
- For any application type that is transactional in nature (e.g. one that processes specific events, such as an interactive web browser or non-interactive web server), use a logfile to produce a transactional log of events that can be reviewed later. This can include outputting to the logfile which file is being processed, updates on the percentage complete, timestamps of when it started certain stages of computing, warning and error messages, etc…


# 9.6 assert, static_assert
Bouncer pattern: Add all the test-cases before core logic, so that the function exits on first error.
Invariant: A condition that is true as long as the code is executing. All loops have an invariant. The loop runs as long
as the invariant is satisfied.
Assertions: Statements that are true unless program has a bug. If false, the program exits with `std::abort` 
- Add context to assert error message: `assert(found && "Car could not be found in database");`
- `#undef NDEBUG` before all headers to enable assertions for a translation unit. `#define NDEBUG` to disable assertions (production code)

`static_assert`
- assertion that is checked at compile-time rather than at runtime, with a failing static_assert causing a compile error. 
- Because `static_assert` is evaluated by the compiler, the condition must be a constant expression.
- `static_assert` can be placed anywhere in the code file (even in the global namespace).
- `static_assert` is not deactivated in release builds (like normal assert is).
- Because the compiler does the evaluation, there is no runtime cost to a `static_assert`
```C++
static_assert(sizeof(long) == 8, "long must be 8 bytes"); // message is optional after C++17
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```

Favor static_assert() over assert() whenever possible
