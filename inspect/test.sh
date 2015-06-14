#!/bin/sh
set -e
#inspect.hpp test suite
#currently there are no 

g++ -std=c++11 -O2 -otest1 test.cpp
./test1 > test1.txt
head -n3 test.cpp > test2.cpp
./test1 >> test2.cpp
tail -n2 test.cpp >> test2.cpp
g++ -std=c++11 -O2 -otest2 test2.cpp
./test2 > test2.txt
diff test1.txt test2.txt
rm test1 test1.txt test2 test2.txt test2.cpp
echo test successful.
