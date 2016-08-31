cmake_minimum_required(VERSION 2.8.2)

include(CTest)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Trivial example using gtest and gmock

include_directories(../lib/Analizador)
include_directories(../lib/Utils)

add_executable(AnalizadorTests TestsAnalizador.cpp TestsNoticia.cpp NoticiaMock.h TestsEntidadComposite.cpp LineWordIteratorTest.cpp TestsPalabrasReservadas.cpp)
target_link_libraries(AnalizadorTests LINK_PUBLIC gtest gmock_main analizadorLib jsoncppLib)
add_test(NAME AnalizadorTests_test COMMAND AnalizadorTests)
add_custom_command(TARGET AnalizadorTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dataTests $<TARGET_FILE_DIR:AnalizadorTests>/dataTests)
add_custom_command(TARGET AnalizadorTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/dataTests2 $<TARGET_FILE_DIR:AnalizadorTests>/dataTests2)
