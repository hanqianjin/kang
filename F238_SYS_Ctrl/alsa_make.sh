#! /bin/bash

cd ./unity_api/alsa-lib-1.1.7
if [ $1 == "clean" ]; then
	make distclean
	echo "-----------------"
	rm -rf ../functions/alsa_lib/*
else
	CC=arm-linux-gnueabihf-gcc ./configure --host=arm-linux --prefix=`pwd`/../functions/alsa_lib/
	make
	make install
fi
cd -

