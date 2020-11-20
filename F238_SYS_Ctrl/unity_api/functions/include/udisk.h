#ifndef __UDISK_H__
#define __UDISK_H__

#ifdef __cplusplus
    extern "C" {
#endif

typedef enum usb_dev_stat {
    USB_DISK_IN   = 1,
    USB_DISK_OUT,
    USB_MOUSE_IN,
    USB_MOUSE_OUT,
    USB_UNKNOW,
}usbDevStat;

typedef struct usb_dev_info {
    usbDevStat state;
    char mount_dir[128];
}usbDevInfo;

DiInt32 UdiskUmount(char* mount_dir);

#ifdef __cplusplus
    }
#endif

#endif
