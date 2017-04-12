cmake_minimum_required(VERSION 3.6)
project(SimpleJsonParser)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Value.cpp Value.h Object.cpp Object.h Array.cpp Array.h ValueType.cpp ValueType.h JsonParser.cpp JsonParser.h)
add_executable(SimpleJsonParser ${SOURCE_FILES})