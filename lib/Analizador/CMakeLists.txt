cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../jsoncpp)

set(SOURCE_FILES
    Analizador.cpp
    Analizador.h
    EntidadNombrada.cpp
    EntidadNombrada.h
    Noticia.cpp
    Noticia.h NoticiaInterface.h)

add_library(analizadorLib ${SOURCE_FILES})