#!/bin/bash

OUTDIR=`pwd`/build-third/
mkdir -p $OUTDIR
mkdir -p $OUTDIR/lib
mkdir -p $OUTDIR/include

cd lib
echo "Building restbed"

if [ ! -f $OUTDIR/include/corvusoft/restbed ]; then
    mkdir restbed/build
    cd restbed/build
    cmake -DBUILD_SSL=NO -DBUILD_TESTS=NO ..
    make install
    cd ../..
    cp -a restbed/distribution/include/* $OUTDIR/include/
    cp -a restbed/distribution/library/* $OUTDIR/lib/
fi

echo "Building json..."
if [ ! -f $OUTDIR/include/nlohmann/json.hpp ]; then
    cp -a json/include/* $OUTDIR/include/
fi

if [ ! -f $OUTDIR/include/nlohmann/json.hpp ]; then echo "Failed"; exit; fi

echo "Building XPLM..."
if [ ! -f $OUTDIR/include/XPLM/XPLMPlugin.h ]; then
    cp -a XSDK/CHeaders/XPLM $OUTDIR/include
    cp XSDK/Libraries/Win/* $OUTDIR/lib
    cp -a XSDK/Libraries/Mac/* $OUTDIR/lib
fi
if [ ! -f $OUTDIR/include/XPLM/XPLMPlugin.h ]; then echo "Failed"; exit; fi

cd ..