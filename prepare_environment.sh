#!/usr/bin/env sh
# Download and compile source
apt-get source libid3tag0
cd libid3tag-0.15.1b/
AFL_USE_ASAN=1 CC=afl-cc CXX=afl-c++ ./configure
AFL_USE_ASAN=1 CC=afl-cc CXX=afl-c++ make
cd ..

# Compile simple usage code to load MP3
AFL_USE_ASAN=1 afl-cc test_libid3tag.c -I'./libid3tag-0.15.1b/' -L"./libid3tag-0.15.1b/.libs" -lid3tag -o test_libid3tag

# Start the fuzzer:
LD_LIBRARY_PATH=./libid3tag-0.15.1b/.libs afl-fuzz -i seeds/ -o out -- ./test_libid3tag @@

# Test a crash:
# LD_LIBRARY_PATH=./libid3tag-0.15.1b/.libs ./test_libid3tag out/default/crashes/id\:000000*

