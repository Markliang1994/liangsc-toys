cmake_minimum_required(VERSION 3.5.0)
project(my_printf)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")
add_executable(my_printf my_printf.cpp)