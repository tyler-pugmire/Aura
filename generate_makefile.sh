#!/bin/bash
cmake -B ./bin-int/glfw/ -S ./Aura/vendor/glfw/
./tools/bin/premake/linux/premake5 --cc=clang --file=premake5.lua gmake2
./tools/bin/premake/linux/premake5 --cc=clang --file=premake5.lua export-compile-commands 

