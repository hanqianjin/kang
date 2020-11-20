#! /bin/bash

project=$1
echo "bit_name:$1";

rmmod g_tmc
if [ $? != 0 ]; then
    echo "----rm g_tmc"
fi
rmmod usb_f_tmc
if [ $? != 0 ]; then
    echo "----rm f_tmc"
fi
rmmod libcomposite
if [ $? != 0 ]; then
    echo "----rm libcom"
fi
rmmod configfs
if [ $? != 0 ]; then
    echo "----rm conf"
fi
rmmod udc-xilinx
if [ $? != 0 ]; then
    echo "----rm udc"
fi
#------

cat $1 > /dev/xdevcfg
if [ $? != 0 ]; then
	echo "bitfile reconfig err!"
	exit 1
fi

#---ins mico usb driver
insmod /app/drivers/udc-xilinx.ko
if [ $? != 0 ]; then
    echo "----ins udc"
fi
insmod /app/drivers/configfs.ko
if [ $? != 0 ]; then
    echo "----ins conf"
fi
insmod /app/drivers/libcomposite.ko
if [ $? != 0 ]; then
    echo "----ins libcom"
fi
insmod /app/drivers/usb_f_tmc.ko
if [ $? != 0 ]; then
    echo "----ins f_tmc"
fi
insmod /app/drivers/g_tmc.ko product_information="inno","F238","V0.1"
if [ $? != 0 ]; then
    echo "----ins g_tmc"
fi


