#!/bin/bash

RELEASE_INFO=$(cat release_info.txt)
VERSION=$(echo "$RELEASE_INFO" | grep '^VERSION=' | sed 's/VERSION=//')

mkdir temp
mkdir build 2>/dev/null

sudo apt-get update
sudo apt-get install -y g++ make cmake

cd temp
cmake ../src -DCMAKE_CXX_STANDARD=20
make snowfox
mv snowfox ../build/snowfox-linux-${VERSION}

cd ..
rm -rf temp

echo "The build was a success: snowfox-linux-${VERSION}"