#!/usr/bin/env bash
mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
cd - &&
${0%/*}/build/rpeaks-example;