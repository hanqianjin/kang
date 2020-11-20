#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/mount.h>

#include "error_functions.h"
#include "unity.h"
#include "udisk.h"

#define MAXCOUNT 500

static dev_fun_opt* udisk_fun;
static DiInt32 inotifyFd;

DiInt32 openUdisk(DiPSession handle)
{
    DiInt32 ret;

    inotifyFd = inotify_init();
    ret = inotify_add_watch(inotifyFd, "/dev", IN_DELETE | IN_CREATE);//
    if (ret < 0)
    {
        errSys("inotify_add_watch /dev");
        return SA_UDISK_OPEN;
    }
    ret = inotify_add_watch(inotifyFd, "/dev/input/", IN_DELETE | IN_CREATE);
    if (ret < 0)
    {
        errSys("inotify_add_watch /dev/input/");
        return SA_UDISK_OPEN;
    }
    if (ret < 0)
    {
        errSys("inotify_add_watch");
        return SA_UDISK_OPEN;
    }	
    *handle = inotifyFd;
    PRINTF("haha,in openUdisk\n");
    return 0;
}

DiInt32 closeUdisk(DiSession handle)
{
    DiInt32 ret;

    ret = close(handle);
    if(ret < 0) {
        errSys("closeUdisk");
        return SA_UDISK_CLOSE;
    }
    PRINTF("hh, in closeUdisk\n");

    return ret;
}

DiInt32 Udisk_initcheck(void)
{
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *found = NULL;
    char *end = NULL;
    usbDevInfo* temp_data = NULL;
    
    temp_data = (usbDevInfo*)malloc(sizeof(usbDevInfo));
	if (temp_data == NULL) {
		errSys("Udisk_initcheck malloc");
		return -1;
	}

    /*if((access("/dev/input/mouse0",F_OK))!=-1){
        temp_data->state = USB_MOUSE_IN; 
        udisk_fun->epoll_deal(temp_data);
    }
    else*/ if ((access("/dev/input/mouse1",F_OK))!=-1) {
        temp_data->state = USB_MOUSE_IN; 
        udisk_fun->epoll_deal(temp_data);
    }


    fp = fopen("/proc/mounts", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        found = strstr(line, "/dev/sd");
        if (found != NULL) {
            PRINTF("%s", line);
            end = strchr(line, ' ');

            temp_data->state = USB_DISK_IN;
            snprintf(temp_data->mount_dir, end-found+1, "/mnt%s",line+4);
            udisk_fun->epoll_deal(temp_data);
        }
    }
    free(line);
    fclose(fp);

    free(temp_data);
    return 0;
}

DiInt32 Udisk_callback_prepare(void** data)
{
    char inotifyBuf[MAXCOUNT];
    DiInt32 readCount = 0;
    struct inotify_event*  curInotifyEvent;
    usbDevInfo* temp_data = NULL;
    
    temp_data = (usbDevInfo*)malloc(sizeof(usbDevInfo));
    if (temp_data == NULL) {
        errSys("Udisk_callback_prepare malloc");
        return -1;
    }
    *data = (void *)temp_data;

	if (inotifyFd <= 2) {
        errSys("has not open udisk");
        return -1;
	}
    readCount = read(inotifyFd, inotifyBuf, MAXCOUNT);

    if (readCount <  sizeof(struct inotify_event))
    {
        errSys("inofity event\n");
        return SA_UDISK_READ; 
    }

    curInotifyEvent = (struct inotify_event*)inotifyBuf;

    while(readCount >= sizeof(struct inotify_event))
    {
        if (curInotifyEvent->len > 0)
        {
            if(curInotifyEvent->mask & IN_CREATE)
            {
                //PRINTF("add file :%s\n",curInotifyEvent->name);

                if ((curInotifyEvent->name[0] == 's') && (curInotifyEvent->name[1] == 'd') && (isdigit(curInotifyEvent->name[3])) ) {
                    temp_data->state = USB_DISK_IN ;
                    sprintf(temp_data->mount_dir,"/mnt/%s", curInotifyEvent->name);
                    return 0;
                }
                else if(strncmp(curInotifyEvent->name,"mouse", strlen("mouse")) == 0)
                {
                    temp_data->state = USB_MOUSE_IN;
                    return 0;
                }
                else {
                    temp_data->state = USB_UNKNOW ;
                }

            }
            else if(curInotifyEvent->mask & IN_DELETE)
            {
                //   PRINTF("remove file :%s\n",curInotifyEvent->name);
                if ((curInotifyEvent->name[0] == 's') && (curInotifyEvent->name[1] == 'd') && (isdigit(curInotifyEvent->name[3])) ) {
                    temp_data->state = USB_DISK_OUT;
                    sprintf(temp_data->mount_dir,"/mnt/%s", curInotifyEvent->name);
                    return 0;
                }
                else if(strncmp(curInotifyEvent->name,"mouse", strlen("mouse"))==0)
                {
                    temp_data->state = USB_MOUSE_OUT;
                    return 0;
                }
                else {
                    temp_data->state = USB_UNKNOW ;
                }
            }

        }
        curInotifyEvent --; 
        readCount -= sizeof(struct inotify_event);
    }
    return 0;
}

DiInt32 Udisk_callback_done(void* data)
{
    if (data != NULL) {
        free(data);
    }
    return 0;
}

DiInt32 UdiskUmount(char* mount_dir)
{
    //printf("mount_dir=%s\n", mount_dir);
    if (access(mount_dir,F_OK)) {
        errSys("umount access");
        return SA_UMOUNT_ERR;
    }

    if (umount(mount_dir)) {
        if (errno == EBUSY) {
            errSys("on busy, try again\n");
            return SA_UMOUNT_BUSY;
        }
        else {
            errSys("umount err\n");
            return SA_UMOUNT_ERR;
        }
    }
    if (rmdir(mount_dir)) {
        errSys("cannot remove mount_dir");
        return SA_UMOUNT_ERR;
    }
    return 0;
}

void init_udisk(void)
{
    udisk_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    memset(udisk_fun, 0, sizeof(struct dev_fun_opt));

    udisk_fun->bus_name       = "VIRTUAL";
    udisk_fun->dev_num        = 5;
    udisk_fun->dev_type       = "DEVICE";
    udisk_fun->open           = openUdisk;
    udisk_fun->close          = closeUdisk;
    udisk_fun->epoll_initcheck= Udisk_initcheck;
    udisk_fun->epoll_prepare  = Udisk_callback_prepare;
    udisk_fun->epoll_done     = Udisk_callback_done;
    udisk_fun->is_epoll       = 1;

    register_dev_fun(udisk_fun);
}

void exit_udisk(void)
{
    unregister_dev_fun(udisk_fun);
    free(udisk_fun);
}

