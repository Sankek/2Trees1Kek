cmake_minimum_required(VERSION 3.15)
project(2Trees1Kek)

include_directories(h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(2Trees1Kek main.cpp src/RBTree.cpp h/RBTree.h h/ITree.h h/Node.h h/RBNode.h h/AVLTree.h h/AVLNode.h src/AVLTree.cpp Timer.h)