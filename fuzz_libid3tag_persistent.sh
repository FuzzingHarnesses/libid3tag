#!/usr/bin/env sh

# Start the fuzzer:
LD_LIBRARY_PATH=./libid3tag-0.15.1b/.libs afl-fuzz -i seeds/ -o out -- ./test_libid3tag_persistent @@
