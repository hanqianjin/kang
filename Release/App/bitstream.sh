#! /bin/bash

project=$1
echo "bit_name:$1";

#close vdma vtc
echo 2 > /sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag
if [ $? != 0 ]; then
	echo "disable lcd err!"
	exit 1
fi


echo 0 > /sys/devices/soc0/amba_pl/amba_pl:mcu-interrupt/mcu_interrupt/mcu_interrupt_flag
if [ $? != 0 ]; then
	echo "disable mcu interrupt!"
	exit 1
fi



echo 1 > /sys/bus/i2c/drivers/icn85xx/icn_suspend
if [ $? != 0 ]; then
	echo "disable touchscreen!"
	exit 1
fi

echo 0 > /sys/devices/soc0/amba/amba:matrix-keyboard/matrix_gpio
if [ $? != 0 ]; then
	echo "disable keypad err!"
	exit 1
fi

echo  1  >  /sys/devices/soc0/amba_pl/80021000.serial/usart_pl/usart_flag
if [ $? != 0 ]; then
	echo "disable uart err!"
	exit 1
fi

echo  1  >  /sys/devices/soc0/amba_pl/80028000.serial/usart_pl/usart_flag
if [ $? != 0 ]; then
	echo "disable uart err!"
	exit 1
fi
#echo  1  >  /sys/devices/soc0/amba_pl/80024000.serial/usart_pl/usart_flag
#if [ $? != 0 ]; then
#	echo "disable wifi_bt uart err!"
#	exit 1
#fi
#----rm mico usb driver
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

#open vdma vtc
echo 1 > /sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag
if [ $? != 0 ]; then
	echo "enable lcd err!"
	exit 1
fi

echo 0 > /sys/bus/i2c/drivers/icn85xx/icn_suspend
if [ $? != 0 ]; then
	echo "enable touchscreen!"
	exit 1
fi

echo 1 > /sys/devices/soc0/amba/amba:matrix-keyboard/matrix_gpio
if [ $? != 0 ]; then
	echo "enable keypad err!"
	exit 1
fi

#echo  0  >  /sys/devices/soc0/amba_pl/80024000.serial/usart_pl/usart_flag
#if [ $? != 0 ]; then
#	echo "disable wifi_bt uart err!"
#	exit 1
#fi
echo  0  >  /sys/devices/soc0/amba_pl/80021000.serial/usart_pl/usart_flag
if [ $? != 0 ]; then
	echo "enable uart err!"
	exit 1
fi

echo  0  >  /sys/devices/soc0/amba_pl/80028000.serial/usart_pl/usart_flag
if [ $? != 0 ]; then
	echo "enable uart err!"
	exit 1
fi

echo 1 > /sys/devices/soc0/amba_pl/amba_pl:mcu-interrupt/mcu_interrupt/mcu_interrupt_flag
if [ $? != 0 ]; then
	echo "enable mcu interrupt!"
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
insmod /app/drivers/g_tmc.ko product_information="inno","F263","V0.1"
if [ $? != 0 ]; then
    echo "----ins g_tmc"
fi


