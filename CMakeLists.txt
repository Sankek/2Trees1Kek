cmake_minimum_required(VERSION 3.15)
project(2Trees1Kek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(2Trees1Kek main.cpp RBTree.cpp RBTree.h ITree.h Node.h RBNode.h)