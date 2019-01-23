mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
./waves-testbench; # tu mozesz zmienic nazwe pliku wykonywalnego
cd -
