cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../jsoncpp)
include_directories(../Utils)

set(SOURCE_FILES
    Analizador.cpp
    Analizador.h
        Noticia.cpp
    Noticia.h NoticiaInterface.h
        EntidadComposite.h EntidadComposite.cpp
        PalabrasReservadas.h PalabrasReservadas.cpp PalabrasReservadasInterface.h
        AgrupadorNoticias.cpp AgrupadorNoticias.h AgrupadorNoticiasInterface.h
        NoticiasBuilderInterface.h NoticiasBuilder.cpp NoticiasBuilder.h
        Tuit.cpp Tuit.h TuitsJsonBuilder.h TuitsJsonBuilder.cpp NoticiasJsonBuilder.cpp NoticiasJsonBuilder.h)

add_library(analizadorLib ${SOURCE_FILES})