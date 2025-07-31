cmake_minimum_required(VERSION 3.14)
project(GTest_GMock)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  # 24 july 2025
  URL https://github.com/google/googletest/archive/32f9f4c82afa4249af66b55278df15c16b3031ea.zip
)
FetchContent_MakeAvailable(googletest)


enable_testing()

# if we use a main() before run tests
# (see mixxx/test/main.cpp), it must be 
# a part of the src list.
# in this case, gtest_main need not be linked. (link GTest::gtest instead)
#https://google.github.io/googletest/primer.html
set(src-learncpp-gtest
    0_factorialtest.cpp
    1_fifotest.cpp
  )
add_executable(learncpp-test ${src-learncpp-gtest})

# obj files containing other class definitions need to be linked
# if we are writing tests for a larger app my_app, then we need
# to add my_app to the link_libraries list too.
target_link_libraries(learncpp-test GTest::gtest_main)