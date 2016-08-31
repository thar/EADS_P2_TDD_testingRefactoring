cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../jsoncpp)

set(SOURCE_FILES
    Analizador.cpp
    Analizador.h
        Noticia.cpp
    Noticia.h NoticiaInterface.h
        EntidadComposite.h EntidadComposite.cpp)

add_library(analizadorLib ${SOURCE_FILES})