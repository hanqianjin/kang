#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>  
#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "dpxMem.h"
#define DPXDEV "/dev/dpx-mem"

static void(*g_func)(void*) ;
static pthread_t g_thread;
static int g_epfd = -1;
static int g_open;
static int g_register;
static void *dpx_map_base = NULL;

/*************************************************
Function:       openDPXMem
Description:    open and map the memorys be allocated by PL to user space
Calls:          open mmap
Called By:      extern
                devHandle    --handle of the device node
Output:         NULL
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
DiInt32 openDPXMem(DiPSession devHandle)
{
    static int Fd = -1;
    
	if (0 == g_open) {
   		if((Fd = open(DPXDEV, O_RDWR | O_SYNC)) < 0)
    	{   
        	printf("open  fail!\n") ;
        	return -1; 
    	}   
    
    	//dpx_map_base = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, 0); 
    //	printf("mem addr:%p", dpx_map_base);
	//	if (!dpx_map_base)
   // 	{   
    //    	printf("mmap err\n") ;
   //     	return -1 ;
   // 	}   
		
		//g_open++;
        __sync_fetch_and_add(&g_open, 1);
    }
	else {
        __sync_fetch_and_add(&g_open, 1);
        //g_open++;

	}
	
	*devHandle = Fd; 

    return DI_SUCCESS ;
}
/*************************************************
Function:       getDPXAddr
Description:    open and map the memorys be allocated by PL to user space
Calls:          
Called By:      extern
                devHandle    --handle of the device node
Output:         NULL
Return:         address of DPX mem   --success
                NULL                 --err
Others:         NULL
*************************************************/
void* getDPXAddr(DiSession devHandle)
{
	return dpx_map_base ;
}

/*************************************************
Function:       epoll_func
Description:    call user function when epoll wakeup
Calls:          epoll_wait
Called By:      registerDPXHandler
Input:          arg    --pass epoll fd
Output:         NULL
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
void* epoll_func(void *arg)
{
	struct epoll_event events[5];
	int nfds = -1;
	int i;

	while(1)
	{
		nfds = epoll_wait(g_epfd, events, 5, -1);
		if (nfds < 0) {
			if(EINTR == errno) {
				printf("a signal happened\n");
				nfds = epoll_wait(g_epfd, events, 5, -1);
			}
			else {
				printf("epoll_wait err!\n");
				return NULL;
			}
		}
		for(i = 0; i < nfds; i++)
		{ 
			if(events[i].events & EPOLLIN) {
					printf("handle epoll %d fd %d\n", i, events[i].data.fd); 
					g_func(dpx_map_base);
				}   
			}
	}
}

/*************************************************
Function:       registerDPXHandler
Description:    register a function to handle DPX when data ready
Calls:          epoll_create epoll_ctl pthread_create
Called By:      extern
Input:          devHandle    --handle of the device node
				func         --handle DPX data
Output:         NULL
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
DiInt32 registerDPXHandler(DiSession devHandle, void(*func)(void *))
{
	struct epoll_event ev; //ev用于注册事件，数组用于返回要处理的事件
	int ret ;

	g_func = func;
	
	if (0 == g_register) {
		g_epfd = epoll_create(1); //只需要监听一个描述符——标准输入
		ev.data.fd = devHandle;
		ev.events = EPOLLIN|EPOLLET; //监听读状态同时设置ET模式
		ret = epoll_ctl(g_epfd, EPOLL_CTL_ADD, devHandle, &ev); //注册epoll事件
		if (ret != 0)
    	{
        	printf("epoll_ctl err\n");
			return -1;
    	} 

		ret = pthread_create(&g_thread, NULL, epoll_func, NULL);
		if (ret != 0)
		{
			printf("creat thread err\n");
			errno = ret ;
			perror("pthread_create");
			return -1;
		}
		__sync_fetch_and_add(&g_register, 1);
	}
	else {
		__sync_fetch_and_add(&g_register, 1);
	}
	return DI_SUCCESS ;
}
/*************************************************
Function:       unregisterDPXHandler
Description:    unregister a function to handle DPX when data ready
Calls:          close pthread_cancel
Called By:      extern
Input:          devHandle    --handle of the device node
Output:         NULL
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
DiInt32 unregisterDPXHandler(DiSession devHandle)
{
    int ret;

    if (g_register < 1) {
        printf("not need to close\n") ;
        return -1 ;
    }

    if (1 == g_register) {
		close(g_epfd);
		g_epfd = -1;

    	ret = pthread_cancel(g_thread);
    	if (ret != 0){   
       		printf("cancel thread err\n");
        	errno = ret ;
        	perror("pthread_cancel");
    	}
		pthread_join(g_thread, NULL);
		__sync_fetch_and_sub(&g_register, 1);
	}
	else
	{
		
		__sync_fetch_and_sub(&g_register, 1);
	}
    return DI_SUCCESS ;
}
/*************************************************
Function:       closeDPXMem
Description:    close and unmap the memorys be allocated by PL to user space
Calls:          munmap close
Called By:      extern
Input:          devHandle    --handle of the device node
Output:         NULL
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
DiInt32 closeDPXMem(DiSession devHandle)
{
    if (g_open < 1) {
        printf("not need to close\n") ;
        return -1 ;
    }

    if (1 == g_open) {
		if (dpx_map_base != NULL) {
			munmap(dpx_map_base, MMAP_SIZE);
			dpx_map_base = NULL;
		}
		close(devHandle);
        //g_open--;
        __sync_fetch_and_sub(&g_open, 1);
    }
    else {
        //g_open--;
        __sync_fetch_and_sub(&g_open, 1);
    }

}


