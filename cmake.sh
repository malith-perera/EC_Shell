#!/bin/bash

if [ -d "build" ]; then
  rm -r "build"
fi

mkdir "build"
cd "build"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../

make
