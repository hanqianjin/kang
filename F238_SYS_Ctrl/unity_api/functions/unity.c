#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <linux/input.h>


#include "unity.h"
#include "uniuser.h"
#include "udisk.h"


struct input_event g_key_event;

typedef struct fun_desc
{
	char *bus_name;
	DiInt32 dev_num;
	char *dev_type;
	void (*init_func)(void);
	void (*exit_func)(void);
}fun_desc;

extern void init_temp(void);
extern void exit_temp(void);
extern void init_temp_rf(void);
extern void exit_temp_rf(void);
extern void init_udisk(void);
extern void exit_udisk(void);
extern void init_pl_misc(void);
extern void exit_pl_misc(void);
extern void init_gps(void);
extern void exit_gps(void);
extern void init_mcu_uart(void);
extern void exit_mcu_uart(void);
extern void init_micro_usb(void);
extern void exit_micro_usb(void);
extern void init_snd(void);
extern void exit_snd(void);
extern void init_fpga_temp(void);
extern void exit_fpga_temp(void);



static fun_desc fun_arry[] = {
    {"VIRTUAL", 0, "DEVICE",      init_pl_misc,     exit_pl_misc},   //misc devices
    {"ASRL_PL", 0, "DEVICE",      init_gps,         exit_gps},       //GPS
    {"ASRL_PL", 1, "DEVICE",      init_mcu_uart,     exit_mcu_uart},   //mcu usart
    {"I2C"    , 0, "DEVICE",      init_temp,        exit_temp},      //temperature(main board)
    {"I2C"    , 1, "DEVICE",      init_temp_rf,     exit_temp_rf},   //temperature (radio board)
    {"VIRTUAL", 1, "DEVICE",      init_snd,         exit_snd},       //audio/FM
    {"VIRTUAL", 2, "MEMACC",      NULL,             NULL},           //shard memery(no use)
    {"VIRTUAL", 3, "MEMACC",      NULL,             NULL},           //DPX(no use)
    {"VIRTUAL", 4, "DEVICE",      NULL,             NULL},           //sweep(no use)
    {"VIRTUAL", 5, "DEVICE",      init_udisk,       exit_udisk},     //udisk insert/out
    {"VIRTUAL", 6, "DEVICE",      NULL,             NULL},           //
    {"USB"    , 1, "DEVICE",      init_micro_usb,   exit_micro_usb}, //usb
    {"VIRTUAL", 7, "DEVICE",      init_fpga_temp,   exit_fpga_temp}, //fpga temperature
};


typedef struct Node
{
	dev_fun_opt *data;
	struct Node *pNext;
}NODE,*PNODE;


typedef struct HeadNode
{
	char        *bus_name;
	struct Node  Node;
}HEAD_NODE,*PHEAD_NODE;

static int  g_epfd = -1;
#define EPOLL_NUM 10

static pthread_t g_thread;
#define FUN_NUM 128
#define BUS_NUM 20

#define OPEN_FUNC_NUM 128
dev_fun_opt * g_open_func[OPEN_FUNC_NUM];

static HEAD_NODE g_bus_array[BUS_NUM];

static PHEAD_NODE check_add_bus(dev_fun_opt *dev_opt)
{
	DiInt32 i;

	for(i = 0; i < BUS_NUM; i++)
	{
		if(g_bus_array[i].bus_name != NULL) {
			if (!strcmp(dev_opt->bus_name, g_bus_array[i].bus_name)) {
				//PRINTF("check__bus:g_bus_array[%d] %s\n", i, g_bus_array[i].bus_name);
				return &g_bus_array[i];
			}
		}
		else {
			PRINTF("add new bus\n");
			g_bus_array[i].bus_name = dev_opt->bus_name;
			//PRINTF("_add_bus:g_bus_array[%d] %s\n", i, g_bus_array[i].bus_name);
			return &g_bus_array[i];
		}
	}

	return NULL;
}

static PHEAD_NODE find_bus(char *bus_name)
{
	DiInt32 i;

	for(i = 0; i < BUS_NUM; i++)
	{
		if(g_bus_array[i].bus_name != NULL) {
			if (!strcmp(bus_name, g_bus_array[i].bus_name)) {
			//	PRINTF("find_bus:g_bus_array[%d] %s\n", i, g_bus_array[i].bus_name);
				return &(g_bus_array[i]);
			}
		}
	}
	errUser("no shuch bus:%s\n", bus_name);
	return NULL;
}

static DiInt32 insert_list(PNODE list_head, dev_fun_opt* dev_opt)
{
	PNODE temp;
	temp = list_head;

	while(temp->pNext != NULL) {
		//PRINTF("instert1:%s %d\n", temp->pNext->data->bus_name, temp->pNext->data->dev_num);
		if(dev_opt->dev_num == temp->pNext->data->dev_num) {
			errUser("this dev_fun id already registered\n");
			return SA_DEV_RESISTED;
		}
		temp = temp->pNext;
	}
	temp->pNext = (PNODE)malloc(sizeof(struct Node));
	if(!(temp->pNext)) {
		errUser("malloc err!\n");
		return SA_MEM_ALLOC;
	}
	temp->pNext->data = dev_opt;
	temp->pNext->pNext = NULL;
	//PRINTF("instert2:%s %d\n", temp->pNext->data->bus_name, temp->pNext->data->dev_num);
	return 0;
}

static  DiInt32 delete_list(PNODE list_head, dev_fun_opt* dev_opt)
{
	PNODE temp;
	PNODE t = NULL;
	temp = list_head;

	while(temp->pNext != NULL) {
		if(dev_opt->dev_num == temp->pNext->data->dev_num) {
			t = temp->pNext;
			temp->pNext = t->pNext;
			break;
		}
		temp = temp->pNext;
	}
	
	if (t != NULL){
		free(t);
	}
	else {
		errUser("no dev_fun to unregister\n");
		return SA_DEV_UNRESISTE_FAILD;
	}
	return 0;
}

static dev_fun_opt* find_list(PNODE list_head, DiInt32 dev_num)
{
	PNODE temp;
	temp = list_head;
	
	while(temp->pNext != NULL) {
		//PRINTF("find:%s %d\n", temp->pNext->data->bus_name, temp->pNext->data->dev_num);
		if(dev_num == temp->pNext->data->dev_num) {
			return temp->pNext->data;
		}
		temp = temp->pNext;
	}

	errUser("find no dev:%d\n", dev_num);
	return NULL;
}

static dev_fun_opt* find_open_func(int fd)
{

        if(g_open_func[fd] != NULL) {
            return g_open_func[fd];
        }

    errUser("find no fd:%d\n", fd);
    return NULL;
}

static void* epoll_func(void *arg)
{   
    struct epoll_event events[EPOLL_NUM];
    int nfds = -1;
    DiInt32 i;
	void *func_data = NULL;
	dev_fun_opt *temp_fun;
    DiInt32 ret;

    while(1)
    {
        nfds = epoll_wait(g_epfd, events, EPOLL_NUM, -1);
        if (nfds < 0) { 
            if(EINTR == errno) {
                errUser("signal inperrupt\n");
                nfds = epoll_wait(g_epfd, events, EPOLL_NUM, -1);
            }
            else {
                errUser("epoll_wait err!\n");
                return NULL;
            }
        }
        for(i = 0; i < nfds; i++)
        {
            if(events[i].events & EPOLLIN) {
			//	PRINTF("handle epoll %d fd %d events =%d\n", i, events[i].data.fd,events[i].events);
				temp_fun = find_open_func( events[i].data.fd);
				if(temp_fun == NULL) {
					errUser("find no fun fd:%d\n", events[i].data.fd);
					return NULL;
				}
				if(temp_fun->epoll_prepare != NULL) {
                    ret = temp_fun->epoll_prepare(&func_data);
                    if (ret < 0) {
                        errUser("epoll_prepare-busname:%s,devnum:%d\n", temp_fun->bus_name, temp_fun->dev_num);  
						break;
                    }
                }
				if(temp_fun->epoll_deal != NULL) {
					//if (!strcmp(temp_fun->bus_name, "VIRTUAL") && (temp_fun->dev_num == 5)){//udisk
					//		temp_fun->read(events[i].data.fd,0, 0, sizeof(udisk_status),(void *)&udisk_status);
					ret = temp_fun->epoll_deal(func_data);
                    if (ret < 0) {
                        errUser("epoll_deal ret=%d-busname:%s,devnum:%d\n",ret, temp_fun->bus_name, temp_fun->dev_num);   
						break;
                    }
					//}
				}
				if(temp_fun->epoll_done != NULL) {
                    ret = temp_fun->epoll_done(func_data);
                    if (ret < 0) {
                        errUser("epoll_done-busname:%s,devnum:%d\n", temp_fun->bus_name, temp_fun->dev_num);   
						break;
                    }
                }
			}
        }
	}
}


DiInt32 register_dev_fun(dev_fun_opt* dev_fun)
{
	DiInt32 ret;
	if (g_epfd == -1) {
		g_epfd = epoll_create(EPOLL_NUM); 
		
		ret = pthread_create(&g_thread, NULL, epoll_func, NULL);
    	if (ret != 0)
    	{   
       		errUser("creat thread err\n");
       		return SA_THREAD_CREATE; 
    	}
	}

	if(dev_fun == NULL) {
		errUser("register_dev_fun err!\n");
		return SA_DEV_RESISTE_FAILD;
	}
	
	dev_fun->fd = -1;
	dev_fun->num_open = 0;
	
	ret = insert_list(&check_add_bus(dev_fun)->Node, dev_fun);
	if (ret < 0) {
		errUser("insert_list err\n");
		return SA_DEV_RESISTE_FAILD;
	}
	PRINTF("register_dev:insert %s %d\n", dev_fun->bus_name, dev_fun->dev_num);

	return ret;	
}

DiInt32 unregister_dev_fun(dev_fun_opt* dev_fun)
{
	DiInt32 ret;
    dev_fun_opt *temp_fun;
    
	temp_fun = find_list(&find_bus(dev_fun->bus_name)->Node, dev_fun->dev_num);
	if(temp_fun != NULL) {
		errUser("the function has been used, close it first!\n");
		return SA_DEV_UNRESISTE_FAILD;
	}
	
	if(dev_fun != NULL) {
		errUser("unregister_dev_fun err!\n");
		return SA_DEV_UNRESISTE_FAILD;
	}

	ret = delete_list(&find_bus(dev_fun->bus_name)->Node, dev_fun);
	if(ret < 0) {
		errUser("delect_list err\n");
		return SA_DEV_UNRESISTE_FAILD;
	}
	if (g_epfd != -1) {
    	close(g_epfd);
    	g_epfd = -1; 
	
	    ret = pthread_cancel(g_thread);
    	if (ret != 0){   
        	errUser("cancel thread err\n");
			return SA_THREAD_CANCEL;
    	}
    	pthread_join(g_thread, NULL);
	}
	return ret;
}

DiInt32 OpenDev(char *rsrc_name, DiPSession pHandle)
{
	DiInt32 ret = 0;
	dev_fun_opt *temp_fun;
	struct epoll_event ev; //
    char* delim=":";//

	//PRINTF("rsrc_name:%s\n", rsrc_name);
	char temp_name[256];
	memcpy(temp_name, rsrc_name, strlen(rsrc_name));
    char* bus_name     = strtok(temp_name, delim);
	//PRINTF("bus_name:%s\n", bus_name);
    char* str_dev_num = strtok(NULL, delim);   
    DiInt32 dev_num = atoi(str_dev_num);
	//PRINTF("dev_num:%d\n", dev_num);
    char* dev_type     = strtok(NULL,delim);
	//PRINTF("dev_type:%s\n", dev_type);
PRINTF("DiOpenDev times:dev:%s\n", temp_name);	
	temp_fun = find_list(&find_bus(bus_name)->Node, dev_num);
	if(temp_fun == NULL) {
		errUser("find no fun dev_num:%d\n", dev_num);
		return SA_DEV_NOT;
	}

	if (0 == temp_fun->num_open) {
		ret = temp_fun->open(pHandle);
	    if (ret < 0) {
            errUser("DiOpenDev busname:%s,devnum:%d\n", temp_fun->bus_name, temp_fun->dev_num) ;
            return ret;
        }
		
		temp_fun->fd = *pHandle;

	    if (temp_fun->is_epoll) {
    	    ev.data.fd = *pHandle;
       		ev.events = EPOLLIN|EPOLLET;
        	ret = epoll_ctl(g_epfd, EPOLL_CTL_ADD, *pHandle, &ev);
			if (ret < 0) {
				errSys("epoll_ctl busname:%s,devnum:%d\n", temp_fun->bus_name, temp_fun->dev_num);
				return ret;
			}
    	}
		g_open_func[temp_fun->fd] = temp_fun;
		//g_open++;
        __sync_fetch_and_add(&(temp_fun->num_open), 1); 
    }   
    else
    {   
        __sync_fetch_and_add(&(temp_fun->num_open), 1); 
        //g_open++
		*pHandle = temp_fun->fd;
    }
	PRINTF("DiOpenDev times:%d dev:%s %d handle:%d\n", temp_fun->num_open, temp_fun->bus_name, temp_fun->dev_num, temp_fun->fd);	
	return ret;
}

DiInt32 CloseDev(DiSession pHandle)
{
	DiInt32 ret = 0;
	struct epoll_event ev; 	
	dev_fun_opt *temp_fun;
	//PRINTF("diclosedev handle:%d\n", pHandle);
	temp_fun = find_open_func( pHandle);
	if(temp_fun == NULL) {
		errUser("find no fun fd:%d\n", pHandle);
		return SA_DEV_NOT;
	}
	//PRINTF("DiCloseDev num:%d %s handle:%d\n", temp_fun->num_open, temp_fun->rsrc_name, temp_fun->fd);	
    if (temp_fun->num_open < 1) {
        errUser("not need to close\n") ;
        return -1 ;
    }
    if (1 == temp_fun->num_open) { 
		if (temp_fun->is_epoll) {
			ev.data.fd = pHandle;
   			ev.events = EPOLLIN|EPOLLET; 
			ret = epoll_ctl(g_epfd, EPOLL_CTL_DEL, pHandle, &ev); 
		}
	
		ret = temp_fun->close(pHandle);
	    if (ret < 0) {
            errUser("close busname:%s,devnum:%d\n", temp_fun->bus_name, temp_fun->dev_num) ;
            return ret ;
        }
		g_open_func[temp_fun->fd] = NULL;
		temp_fun->fd = -1;
        //g_open--;
        __sync_fetch_and_sub(&(temp_fun->num_open), 1);
    }
    else {
        //g_open--;
        __sync_fetch_and_sub(&(temp_fun->num_open), 1);
    }
	return ret;
}

DiInt32 DiReadDev(DiSession pHandle, DiInt32 offset, DiInt32 len, void* data)
{
    DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( pHandle);
	if(temp_fun == NULL) {
		errUser("find no fun fd:%d\n", pHandle);
		return SA_DEV_NOT;
	}

	ret = temp_fun->read(pHandle, 0,offset, len, data);

	return ret;
}

DiInt32 DiWriteDev(DiSession pHandle, DiInt32 offset, DiInt32 len, void* data)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( pHandle);
	if(temp_fun == NULL) {
		errUser("find no fun fd:%d\n", pHandle);
		return SA_DEV_NOT;
	}
	
	return ret;
	
}

DiInt32 DiCtlDev(DiSession pHandle, DiInt32 cmd, void *data)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( pHandle);
	if(temp_fun == NULL) {
		errUser("find no fun fd:%d\n", pHandle);
		return SA_DEV_NOT;
	}

	ret = temp_fun->ioctl(pHandle, cmd, data);
	return ret ;
}
/*
DiInt32 BitWrite32(DiSession devHandle,DiUInt32 addr,DiUInt32 value)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->write != NULL) {
		ret = temp_fun->write(devHandle, addr, 0, sizeof(value), &value);
	}
	else {
		errUser("no write");
		return SA_DEV_WRITE;
	}
	
	return ret;
}
DiInt32 BitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

	 temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, addr, 0, sizeof(value), (void*)value);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}

	return ret;	
}
DiInt32 BitMoveOut8(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt8 buf8)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, addr, 0, length * sizeof(DiUInt8), (void*)buf8);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut16(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt16 buf16)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_READ;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, addr, 0, length * sizeof(DiUInt16), (void*)buf16);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt32 buf32)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, addr, 0, length * sizeof(DiUInt32), (void*)buf32);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut64(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt64 buf64)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, addr, 0, length * sizeof(DiUInt64), (void*)buf64);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}

DiInt32 BitWrite32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiUInt32 value)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->write != NULL) {
		ret = temp_fun->write(devHandle, space, offset, sizeof(DiUInt32), &value);
	}
	else {
		errUser("no write");
		return SA_DEV_WRITE;
	}
	
	return ret;
}
DiInt32 BitRead32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiPUInt32 value)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, space, offset, sizeof(DiUInt32), (void*)value);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut8Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt8 buf8)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, space, offset, length * sizeof(DiUInt8), (void*)buf8);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut16Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt16 buf16)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, space, offset, length * sizeof(DiUInt16), (void*)buf16);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt32 buf32)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, space, offset, length * sizeof(DiUInt32), (void*)buf32);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
DiInt32 BitMoveOut64Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt64 buf64)
{
	DiInt32 ret = 0;
    dev_fun_opt *temp_fun;

    temp_fun = find_open_func( devHandle);
	if(temp_fun == NULL) {
		errUser("find no fun\n");
		return SA_DEV_NOT;
	}
	
	if (temp_fun->read != NULL) {
		ret = temp_fun->read(devHandle, space, offset, length * sizeof(DiUInt64), (void*)buf64);
	}
	else {
		errUser("no read");
		return SA_DEV_READ;
	}
	
	return ret;
}
*/
DiInt32 RegisterCallback(DiSession fd, DiInt32(*callback_func)(void *))
{
    dev_fun_opt *temp_fun;
       temp_fun = find_open_func(fd);
        int data = 0;
	if(temp_fun == NULL) {
		errUser("find no fun fd:%d\n", fd);
		return SA_DEV_NOT;
	}
	if(temp_fun->is_epoll) {
		temp_fun->epoll_deal = callback_func;

        if (temp_fun->epoll_initcheck != NULL) {
            temp_fun->epoll_initcheck();
        }

		return 0;
	} 

	return SA_NO_CALLBACK;
}


void InitDevs(void)
{
	DiInt32 i;
	#ifdef __LOG_FILE
	openLog();
	#endif
	for(i = 0; i < sizeof(fun_arry)/sizeof(fun_arry[0]); i++) {
		if(fun_arry[i].init_func != NULL) {
			fun_arry[i].init_func();
		}
	}
}
