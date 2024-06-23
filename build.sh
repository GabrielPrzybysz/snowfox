#!/bin/bash

VERSION="0.0.1"

rm -rf build
mkdir build

sudo apt-get update
sudo apt-get install -y g++ make cmake

cd build
cmake ../src -DCMAKE_CXX_STANDARD=20
make snowfox
mv snowfox snowfox-linux-${VERSION}

echo "The build was a success: snowfox-linux-${VERSION}"
