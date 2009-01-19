#!/bin/sh

# quick&dirty to build a demo, surprisingly the binary is called 'Demo'.
# will be deleted if normal build works

cat <<EOF | gcc -x c++ -Wall -g `wx-config --cxxflags --libs` -I include -o Demo -
#include "samples/fcp/nodeinfo.cpp"
#include "src/fcp/ioconnection.cpp"
#include "src/fcp/connection.cpp"
#include "src/fcp/message.cpp"
#include "src/fcp/logger.cpp"
EOF

