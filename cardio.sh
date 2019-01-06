mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
./cardiorama; # tu mozesz zmienic nazwe pliku wykonywalnego
cd -
