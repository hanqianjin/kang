#!/bin/bash
mstr=$1
if [ $mstr = "sa" ]
then
./SaCalcAnaApp 
elif [ $mstr = "rtsa" ]
then
./RtsaCalcAnaApp
fi



