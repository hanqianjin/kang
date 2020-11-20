#ifndef LIB_USB_H
#define LIB_USB_H
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>
#define USB_DT_DEVICE			0x01
#define USB_DT_INTERFACE		0x04

#define VERDOR_ID               0x80ee
#define PRODUCT_ID              0x21

static char usb_scpi_path[256] = {0};
struct usb_device_descriptor {
    __u8  bLength;
    __u8  bDescriptorType;
    __u16 bcdUSB;
    __u8  bDeviceClass;
    __u8  bDeviceSubClass;
    __u8  bDeviceProtocol;
    __u8  bMaxPacketSize0;
    __u16 idVendor;
    __u16 idProduct;
    __u16 bcdDevice;
    __u8  iManufacturer;
    __u8  iProduct;
    __u8  iSerialNumber;
    __u8  bNumConfigurations;
} __attribute__ ((packed));

static int matchDevice(FILE *fd)
{
    struct usb_device_descriptor dev;

    if (fread(&dev, sizeof dev, 1, fd) != 1)
        return -1;

    if (dev.bLength != sizeof dev || dev.bDescriptorType != USB_DT_DEVICE)
        return -1;

    if (dev.idVendor == VERDOR_ID && dev.idProduct == PRODUCT_ID)
        return 0;
    return -1;
}

static int findDevice(const char *name, const struct stat */*sb*/, int flag)
{
    FILE            *fd;
    int				ifnum;
    if (flag != FTW_F)
        return 0;

    fd = fopen(name, "rb");
    if (!fd) {
        perror(name);
        return 0;
    }

    ifnum = matchDevice(fd);
    fclose(fd);
    if (ifnum < 0)
        return 0;

    strcpy(usb_scpi_path,name);
    return 1;
}

const char *usbDir()
{
    static char udev_usb_path[] = "/dev/bus/usb";

    if (access(udev_usb_path, F_OK) == 0)
        return udev_usb_path;

    return NULL;
}
const char *usbDevice(){
    return usb_scpi_path;
}

void searchDHInfoUsbScpiDevice(){
    const char *udev_usb_path = usbDir();
    if (udev_usb_path == NULL)return;
    if (ftw (udev_usb_path,findDevice, 3) != 0) {
        return;
    }
}

#endif // LIB_USB_H
