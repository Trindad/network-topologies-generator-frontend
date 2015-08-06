#!/bin/sh

if [ ! -d "build" ];
then
	mkdir "build"
fi

rm -rf ./packages/nttgen/data/nttgen

if [ ! -d "packages/nttgen/data/nttgen" ];
then
	mkdir "packages/nttgen/data/nttgen"
	mkdir "packages/nttgen/data/nttgen/platforms"
	mkdir "packages/nttgen/data/nttgen/libs"
fi

~/Qt/5.4/gcc/bin/qmake -makefile -o build/Makefile
cd build
make
cp interface ../packages/nttgen/data/nttgen
cp -r ./help ../packages/nttgen/data/nttgen
cd ..

cp libqxcb.so packages/nttgen/data/nttgen/platforms
cd packages/nttgen/data/nttgen
for dep in `ldd ./interface | awk '{print $3}' | grep -v "("`
do
	cp $dep ./libs
done

rm libs/libc.so.6

cd ../../../../

~/Qt/QtIFW2.0.1/bin/binarycreator -c config/config.xml -p packages/ --offline-only nttgen