cmake_minimum_required(VERSION 3.15)
project(2Trees1Kek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(src SOURCES)

add_executable(2Trees1Kek ${SOURCES} src/RBNode.cpp src/AVLNode.cpp)