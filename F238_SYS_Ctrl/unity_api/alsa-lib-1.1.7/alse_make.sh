#! /bin/bash

CC=arm-linux-gnueabihf-gcc ./configure --host=arm-linux --prefix=`pwd`/../functions/alsa_lib/
make
make install

