cmake_minimum_required(VERSION 3.15)
project(Assembler)

set(CMAKE_CXX_STANDARD 14)

# Add main.cpp file of project root directory as source file


add_executable(Interpreter main.cpp general_data.h commands.h register.h functions_asm.h)