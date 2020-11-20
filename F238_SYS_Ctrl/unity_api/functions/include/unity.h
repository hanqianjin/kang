#ifndef __UNITY_H__
#define __UNITY_H__

#ifdef __cplusplus
    extern "C" {
#endif

//#include "BitVisaType.h"
//#include "error_functions.h"
#include "BitSehInfo.h"

//#define BIT_NEW_LCD
#define BIT_OLD_LCD
typedef struct dev_fun_opt
{
	char *bus_name;
	DiInt32 dev_num;
	char *dev_type;

    DiInt32 fd;
    DiInt32 num_open;
	DiInt32 is_epoll;
	void *priv_data;

    DiInt32 (*open)  (DiPSession devHandle);
    DiInt32 (*close) (DiSession devHandle);
    DiInt32 (*read)  (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data);
    DiInt32 (*write) (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data);
    DiInt32 (*ioctl) (DiSession devHandle, DiInt32 cmd, void* data);
	DiInt32 (*epoll_initcheck)(void);
	DiInt32 (*epoll_prepare)(void **data);
	DiInt32 (*epoll_deal)(void *data);
	DiInt32 (*epoll_done)(void *data);
} dev_fun_opt;


extern DiInt32 register_dev_fun(dev_fun_opt* dev_fun);
extern DiInt32 unregister_dev_fun(dev_fun_opt* dev_fun);
extern void func_init(void(*func)(void));
extern void func_exit(void(*func)(void));

#ifdef __cplusplus
    }   
#endif

#endif

