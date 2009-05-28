#!/bin/bash

echo -n "Cleaning up project..."
make clean
echo "done."

echo -n "Cleaning up backup files... "
find . -name "*~" | xargs rm -f
echo "done."

echo -n "Cleaning up CMake cache... "
find . -name "CMake*" | grep -v CMakeLists.txt | xargs rm -Rf
echo "done."
