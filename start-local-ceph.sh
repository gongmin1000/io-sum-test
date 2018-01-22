#!/bin/bash


cd build
../src/stop.sh
make vstart        # builds just enough to run vstart
../src/vstart.sh --debug --new -x --localhost 
./bin/ceph -s


