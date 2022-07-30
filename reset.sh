#!/bin/bash

rm -r bin bin-int
find . -name Makefile -exec rm -rf {} \;
premake5 gmake2
make