#!/bin/bash



pushd ..

./tools/bin/premake/linux/premake5 --cc=clang --file=premake5.lua gmake2
./tools/bin/premake/linux/premake5 --cc=clang --file=premake5.lua export-compile-commands 

popd
