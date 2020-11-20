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
#include <signal.h>
#include <stdlib.h>

#include "../include/unity.h"

static int openEpoll(unsigned int *handle)  
{    
    int fd; 
    
    fd = open("/dev/input/event0", O_RDWR);  
    if (fd < 0)  
    {
        printf("can't open!\n"); 
        return fd ;
    }
    *handle = fd;
	printf("hei,I am in openEpoll2\n");
    return 0;  
} 

static int closeEpoll(unsigned int handle)
{
	close(handle);
	
	printf("hei,I am in closeEpoll2\n");
	return 0;
}


static dev_fun_opt* epoll_fun;

void init_epoll2(void)
{
    epoll_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    
    epoll_fun->rsrc_name   = "TEST:1:DEVICE";
    epoll_fun->open = openEpoll;
    epoll_fun->close= closeEpoll;
	epoll_fun->is_epoll = 1;

    register_dev_fun(epoll_fun);
}

void exit_epoll2(void)
{
    unregister_dev_fun(epoll_fun);
	free(epoll_fun);
}

