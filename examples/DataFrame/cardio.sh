mkdir -p ${0%/*}/build &&
cd ${0%/*}/build &&
cmake .. &&
make &&
./dataframe-testbench;
cd -

