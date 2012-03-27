#!/bin/bash

# just xpt and .a for now because it produces a lot of noise

diff -rq compiled ccompiled -x Makefile \
| grep -v cmake | grep -v CMake \
| grep -v "config.log" | grep -v "config.status" | grep -v "dependencies" \
| grep -v "\.o" | grep -v "\.so" \
| grep -v "xpt" | grep -v "\.a" \
| grep -v "test" | grep -v "mock" \
| grep -v "win32" | grep -v "macosx" | grep -v "windows"