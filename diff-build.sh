#!/bin/bash

# just xpt and .a for now because it produces a lot of noise

diff -rq compiled ccompiled -x Makefile \
| grep -v cmake | grep -v CMakeFiles \
| grep -v "config.log" | grep -v "config.status" | grep -v "dependencies" \
| grep -v "\.o" | grep -v "\.so" \
| grep -v "xpt" | grep -v "\.a"