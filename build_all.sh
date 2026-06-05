#!/bin/bash
set -e
rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_BEHAVIOR_TREE=ON -DENABLE_COROUTINE=ON
make -j$(nproc)
echo "Build completed successfully."
