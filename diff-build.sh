#!/bin/bash
diff -rq compiled ccompiled -x Makefile |
grep -v cmake |
grep -v makefile |
grep -v "\.o" |
grep -v "\.so"