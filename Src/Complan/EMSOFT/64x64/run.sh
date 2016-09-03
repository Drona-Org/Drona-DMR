#!/bin/bash

echo "Compiling Complan.."
echo ""

cd ../../Complan
make clean
make
cd ../Test/Test_1

echo ""
echo ""
echo "Running Complan.."
echo ""

g++ ../../Complan/*.o test.cpp -o test
./test

echo ""
echo ""
echo "Cleanning Directories.."
echo ""

cd ../../Complan
make clean
cd ../Test/Test_1
rm -i constraints.smt2
rm -i z3_output
rm -i test
