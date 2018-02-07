#!/bin/bash


cd build
../src/stop.sh
rm -rf ./out/*
make -j7       # builds just enough to run vstart
if [ $? -ne 0 ]; then
    echo "make fail"
    exit 0
fi

../src/vstart.sh --debug --new -x --localhost 
./bin/ceph -s


