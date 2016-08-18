cmake_minimum_required(VERSION 3.6)
project(AnalizarNoticiasLinux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tests)

set(SOURCE_FILES
    Analizador.cpp
    Analizador.h
    EntidadNombrada.cpp
    EntidadNombrada.h
    Main.cpp
    Noticia.cpp
    Noticia.h)

add_executable(AnalizarNoticiasLinux ${SOURCE_FILES})