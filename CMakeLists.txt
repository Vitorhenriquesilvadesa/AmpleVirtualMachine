cmake_minimum_required(VERSION 3.28)
project(CompilerStudy)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompilerStudy main.cpp
        src/Compiler/Lexer.cpp
        src/Compiler/Lexer.h
        src/Error.h
        src/Util/FileReader.cpp
        src/Util/FileReader.h
        src/Compiler/Expression.cpp
        src/Compiler/Expression.h
        src/Compiler/Token.h
        src/Compiler/BaseType.h
        src/VirtualMachine/VirtualMachine.cpp
        src/VirtualMachine/VirtualMachine.h
)
