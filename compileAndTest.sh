#!/bin/bash - 

set -o nounset                              # Treat unset variables as an error

./compile.sh
./test.sh
