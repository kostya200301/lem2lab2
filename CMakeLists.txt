cmake_minimum_required(VERSION 3.21)
project(SEN2lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(SEN2lab2 main.cpp "SparseVector.h" SparseMatrix.h AlfPointer.h FreqSeQ.h UnitTests.h)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/user/Documents/libraryes/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/user/Documents/libraryes/SFML/include)

target_link_libraries(SEN2lab2 sfml-system sfml-window sfml-graphics sfml-audio)