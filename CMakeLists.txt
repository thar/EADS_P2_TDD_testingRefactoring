cmake_minimum_required(VERSION 3.6)
project(AnalizarNoticiasLinux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib)
add_subdirectory(tests)

include_directories(lib/Analizador)

set(SOURCE_FILES
        main.cpp)

add_executable(AnalizarNoticiasLinux ${SOURCE_FILES})
target_link_libraries(AnalizarNoticiasLinux analizadorLib)