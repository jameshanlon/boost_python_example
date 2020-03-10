rm -rf Debug
mkdir -p Debug
pushd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
ctest .
