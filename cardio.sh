#!/bin/bash

mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
./cardiorama $1 # tu mozesz zmienic nazwe pliku wykonywalnego
cd -
