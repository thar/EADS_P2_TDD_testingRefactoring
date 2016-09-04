#!/bin/bash - 

# Setear la variable CMAKE a la ruta donde se encuentra el binario de cmake-3.6
CMAKE=cmake

if [ ! -d "build" ]; then
  mkdir build
fi

pushd build
$CMAKE ../
$CMAKE --build . --target AnalizadorTests
$CMAKE --build . --target AnalizarNoticiasLinux
popd

