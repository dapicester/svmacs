#!/bin/bash

echo -n "Cleaning up project..."
make clean
echo "done."

echo -n "Cleaning up backup files... "
find . -name "*~" | xargs rm -f
echo "done."

echo -n "Cleaning up CMake... "
find . -name "CMake*" | grep -v CMakeLists.txt | xargs rm -Rf
find . -name "cmake*" | xargs rm -Rf
echo "done."

echo -n "Cleaning up CTest... "
find . -name "Testing" | xargs rm -Rf
find . -name "CTest*" | xargs rm -Rf
echo "done."
