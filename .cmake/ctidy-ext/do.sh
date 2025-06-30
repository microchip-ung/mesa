#!/usr/bin/env bash

if [ ! -d build ]
then
    mkdir build
    cd build
    CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -GNinja ..
else
    cd build
fi

ninja


#clang-tidy --load=ClangTidyModule/build/libcmake-clang-tidy-module.so  c.c

