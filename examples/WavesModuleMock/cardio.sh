mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
./wavesmock-testbench; # tu mozesz zmienic nazwe pliku wykonywalnego
cd -