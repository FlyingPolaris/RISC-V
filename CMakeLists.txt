cmake_minimum_required(VERSION 3.5)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2")

add_executable(code main.cpp IF.hpp ID.hpp EX.hpp MEM.hpp WB.hpp hardware.hpp typedef.hpp operation.hpp prediction.hpp documentreading.hpp forwarding.hpp Intermediate_register.hpp run.hpp)