#!/bin/bash

eval $(grep -v -e '^#' release.env | xargs -I {} echo export "'{}'")

mkdir temp
mkdir build 2>/dev/null

cd temp
cmake ..
make snowfox
mv snowfox ../build/snowfox-linux-${VERSION}

cd ..
rm -rf temp

echo "The build was a success: snowfox-linux-${VERSION}"