#!/bin/bash

# no xpt and .a for now because it produces a lot of noise
# -b should be removed eventually to make sure we are
# producing newlines the right way on each platform
diff -rq -b compiled ccompiled -x Makefile \
| grep -v cmake | grep -v CMake \
| grep -v "config.log" | grep -v "config.status" | grep -v "dependencies" \
| grep -v "\.o" | grep -v "\.so" \
| grep -v "xpt" | grep -v "\.a" \
| grep -v "test" | grep -v "mock" \
| grep -v "win32" | grep -v "macosx" | grep -v "windows"