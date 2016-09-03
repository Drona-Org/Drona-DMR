#!/bin/bash

echo "Compiling Semplan.."
echo ""

cd ../../Semplan
make clean
make
cd ../Test/Test_2

echo ""
echo ""
echo "Running Semplan.."
echo ""

g++ ../../Semplan/*.o test.cpp -o test
./test

echo ""
echo ""
echo "Cleanning Directories.."
echo ""

cd ../../Semplan
make clean
cd ../Test/Test_2
rm -i test
