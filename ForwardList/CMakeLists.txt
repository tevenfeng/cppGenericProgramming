cmake_minimum_required(VERSION 3.6)
project(ForwardList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ForwardListNode.cpp ForwardListNode.h ForwardList.cpp ForwardList.h)
add_executable(ForwardList ${SOURCE_FILES})