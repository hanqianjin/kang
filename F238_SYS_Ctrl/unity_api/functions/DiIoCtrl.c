/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    DiIoCtrl.c
Description:  Just for temperature reading
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
NOTE:         When write, address MUST be 4 Bytes aligned, 
History:    

*****************************************************************************/

// Include files

#include <sys/mman.h> 
#include <string.h> 
#include <pthread.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include "../include/DiIoCtrl.h"
#include "../include/unity.h"

//==============================================================================
// Constants
#define  CPLD_PHY_ADDR    0x80001000  
#define  DSP_PHY_ADDR        0x80000000 

#define DETECTOR_PHY_ADDR   0x80010000
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
#define PAGE_SIZE  ((size_t)getpagesize())  
#define PAGE_MASK ((DiUInt64) (long)~(PAGE_SIZE - 1))  
#define PAGE_CHECK_SIZE  ((size_t)getpagesize() << 3)  

#define CPLD_OUT_BASE    ((CPLD_PHY_ADDR) & (PAGE_MASK))
#define CPLD_OUT_OFF_BASE  ((CPLD_PHY_ADDR) & (~PAGE_MASK))

#define DSP_BASE    ((DSP_PHY_ADDR) & (PAGE_MASK))
#define DSP_OFF_SET  ((DSP_PHY_ADDR) & (~PAGE_MASK))


#define DETECTOR_BASE    ((DETECTOR_PHY_ADDR) & (PAGE_MASK))
#define DETECTOR_OFF_SET  ((DETECTOR_PHY_ADDR) & (~PAGE_MASK))

#define CPLD_SIZE 		PAGE_SIZE
#define DSP_SIZE  		PAGE_SIZE
#define DETECTOR_SIZE 	PAGE_CHECK_SIZE
#define MMAP_SIZE		(CPLD_SIZE + DSP_SIZE + DETECTOR_SIZE)

#define  MEM_DEV   "/dev/mem"

volatile DiUInt8 *Cpld_Map_base,*Dsp_Map_base,*Dector_Map_base;  
volatile DiUInt8 *pl_map_base = NULL ;

static int RsrcCount = 0;

static pthread_mutex_t mutex; 
static int write_delay = 100;//us

static int mmap_size  ;


/*************************************************
Function: 		BitOpen
Description:    open and map the memorys be allocated by PL to user space
Calls: 			open mmap
Called By: 		extern
Input: 			rsrcName     --the device node to be mapped
				devHandle    --handle of the device node
Output: 		NULL
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitOpen(DiRsrc rsrcName,DiPSession devHandle)
{
	int Fd = -1;
	
    if((Fd = open(rsrcName, O_RDWR | O_SYNC)) < 0)
	{
		printf("open %s fail!\n", rsrcName) ;
		return -1; 
	}
	
	pl_map_base = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, 0);
	if (!pl_map_base)
	{
		printf("mmap err\n") ;
		return -1 ;
	}
	mmap_size = MMAP_SIZE ;
	*devHandle = Fd;
	
	return DI_SUCCESS ;
}

DiInt32 shareMemOpen(DiPSession devHandle)
{
    int Fd = -1; 
    
    if((Fd = open("/dev/pl-mem", O_RDWR | O_SYNC)) < 0)
    {   
        printf("open %s fail!\n", __func__) ;
        return -1; 
    }   
    
    pl_map_base = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, 0); 
    if (!pl_map_base)
    {   
        printf("mmap err\n") ;
        return -1 ;
    }   
    mmap_size = MMAP_SIZE ;
    *devHandle = Fd; 
    
    return DI_SUCCESS ;
}
/*
DiInt32 MemBitRead8(DiSession devHandle, DiUInt32 addr, DiPUInt8 value);
DiInt32 shareMemRead (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data)
{
    PRINTF("read addr:%x,offset:%x,len:%d\n", addr, offset, len);
	int i = 0;
	
	for(i = 0; i < len; i++) {
		MemBitRead8(devHandle, addr + i, ((DiUInt8 *)data + i));
		printf("%x\n", *((DiUInt8 *)data +i));
	}

   return DI_SUCCESS;   
}

DiInt32 shareMemWrite (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data)
{

    PRINTF("write addr:%x,offset:%x,len:%d\n", addr, offset, len);
	int i = 0;
	if (len % 4 != 0) {
		errUser("shareMemWrite");
		return -1;
	}
	for(i = 0; i < len/4; i++) {
    	BitWrite32(devHandle, addr + i, *((DiUInt32 *)data + i));
		printf("%x\n", *((DiUInt32 *)data+i));
	}
   return DI_SUCCESS;   
}*/

DiInt32 shareMemRead (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data)
{
	int i;

//   PRINTF("read addr:%x,offset:%x,len:%d\n", addr, offset, len);
   if(CPLD_PHY_ADDR <= (addr+offset) && (addr+offset) <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
		if (len & 3) {// len%4 ==> len&11b
			for(i = 0; i < len; i++) {
			  *((DiUInt8 *)data + i) = *((volatile DiUInt8 *)(pl_map_base + addr + offset - CPLD_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		} else {
			for(i = 0; i < len>>2; i++) {//  len/4  ==> len>>2
			  *((DiUInt32 *)data + i) = *((volatile DiUInt32 *)(pl_map_base + addr + offset - CPLD_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		}
   }   
   else if(DSP_PHY_ADDR <= (addr+offset) && (addr+offset) <= DSP_PHY_ADDR + DSP_SIZE)
   {  
		if (len & 3) { 
			for(i = 0; i < len; i++) {
			  *((DiUInt8 *)data + i) = *((volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + addr + offset - DSP_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		} else {
			for(i = 0; i < len >> 2; i++) {
			  *((DiUInt32 *)data + i) = *((volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + addr + offset - DSP_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		}
   }   
   else if(DETECTOR_PHY_ADDR <= (addr+offset) && (addr+offset) <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
		if (len & 3) {
			for(i = 0; i < len; i++) {
			  *((DiUInt8 *)data + i) = *((volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + addr + offset - DETECTOR_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		} else {
			for(i = 0; i < len >> 2; i++) {
			  *((DiUInt32 *)data + i) = *((volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + addr + offset - DETECTOR_PHY_ADDR)+i);
				//printf("data:%x\n", *((DiUInt8 *)data + i));
			}
		}
   }   
   else 
   {
        return SA_SHAREMEM_OVER; 
   }   

   return DI_SUCCESS;	
}
DiInt32 shareMemWrite (DiSession devHandle, DiUInt32 addr, DiBusAddress offset, DiBusAddress len, void* data)
{
	int i;

  // PRINTF("write addr:%x,offset:%x,len:%d\n", addr, offset, len);
	if (len & 3 != 0) {
		errUser("shareMem write must aligned by 4\n");
		return SA_SHAREMEM_ALIGNED;
	}
   if(CPLD_PHY_ADDR <= (addr+offset) && (addr+offset) <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
		for(i = 0; i < len >> 2; i++) {
	      *((volatile DiUInt32 *)(pl_map_base + addr + offset - CPLD_PHY_ADDR)+i) = *((DiUInt32 *)data + i);
			//printf("data:%x\n", *((DiUInt32 *)data + i));
		}
   }   
   else if(DSP_PHY_ADDR <= (addr+offset) && (addr+offset) <= DSP_PHY_ADDR + DSP_SIZE)
   {   
		for(i = 0; i < len >> 2; i++) {
	      *((volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + addr + offset - DSP_PHY_ADDR)+i) = *((DiUInt32 *)data + i);
			//printf("data:%x\n", *((DiUInt32 *)data + i));
		}
   }   
   else if(DETECTOR_PHY_ADDR <= (addr+offset) && (addr+offset) <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
		for(i = 0; i < len >> 2; i++) {
	      *((volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + addr + offset - DETECTOR_PHY_ADDR)+i) = *((DiUInt32 *)data + i);
			//printf("data:%x\n", *((DiUInt32 *)data + i));
		}
   }   
   else 
   {
        return SA_SHAREMEM_OVER; 
   }   
	usleep(write_delay);
   return DI_SUCCESS;
}
/*************************************************
Function: 		BitOpen_old
Description:    to open /dev/mem just for test
Calls: 			open mmap
Called By: 		extern
Input: 			rsrcName     --must be /dev/mem
				devHandle    --handle of the device node
Output: 		NULL
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 BitOpen_old(DiRsrc rsrcName,DiPSession devHandle, DiUInt32 addr)
{   
    DiInt32 iBack = 0;
	int Fd = -1;

	if((Fd = open(rsrcName, O_RDWR | O_SYNC)) < 0)
	{
		printf("open %s fail!\n", rsrcName) ;
		return -1; 
	}			
	Cpld_Map_base = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, CPLD_OUT_BASE); 
	Dsp_Map_base = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, DSP_BASE);
	Dector_Map_base = mmap(NULL, PAGE_CHECK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, DETECTOR_BASE);

	if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
    {
		pl_map_base = Cpld_Map_base ;
		mmap_size = PAGE_SIZE ;
    }
	else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
    {  
		pl_map_base = Dsp_Map_base - CPLD_SIZE ; 
		mmap_size = PAGE_SIZE ;
    }
	else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
	{
		pl_map_base =  Dector_Map_base  - CPLD_SIZE - DSP_SIZE ;
		mmap_size = PAGE_CHECK_SIZE ;
	}
	else
	{
		pl_map_base = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,Fd, addr);
		mmap_size = PAGE_SIZE ;
	}

    *devHandle = Fd;
    return iBack;
}

/*************************************************
Function: 		BitClose
Description:    close and unmap the memorys be allocated by PL to user space
Calls: 			munmap close
Called By: 		extern
Input: 			devHandle    --handle of the device node
Output: 		NULL
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 BitClose(DiSession devHandle)
{
	int iBack ;
	usleep(100) ;
	if (pl_map_base)
	{
		iBack = munmap((void *)pl_map_base, mmap_size);
		if (iBack < 0)
		{
			return iBack ;
		}
	}
	
	iBack = close(devHandle);
	if (iBack < 0)
	{
		return iBack ;
	}
	
	return DI_SUCCESS ;
}


/*************************************************
Function: 		MemBitRead8
Description:    read a data of uint8 from memory be allocated by PL
Calls: 			NULL
Called By: 		
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 MemBitRead8(DiSession devHandle, DiUInt32 addr, DiPUInt8 value)
{
	DiUInt32 offset = 0;  

    if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
    {
		offset = addr - CPLD_PHY_ADDR  ;
        *value = *(volatile DiUInt8 *)(pl_map_base + offset); 
	 //memcpy(value, (void *)(pl_map_base + offset), sizeof(DiUInt8)) ;
    }
    else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
    {  
		offset = addr - DSP_PHY_ADDR  ;   
		*value = *(volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + offset); 
    }
	else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
	{
		offset = addr - DETECTOR_PHY_ADDR ;
		*value = *(volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset);  
	}
    else 
    {
       return -1;
    }   
    return DI_SUCCESS;
}

/*************************************************
Function: 		MemBitRead16
Description:    read a data of uint16 from memory be allocated by PL
Calls: 			NULL
Called By: 		
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 MemBitRead16(DiSession devHandle,DiUInt32 addr,DiPUInt16 value)
{
    DiUInt32 offset = 0;

    if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
    {
		offset = addr - CPLD_PHY_ADDR  ;
		*value = *(volatile DiPUInt16)(pl_map_base + offset); 
    }
    else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
    {  
		offset=addr - DSP_PHY_ADDR  ;   
		*value = *(volatile DiUInt16 *)(pl_map_base + CPLD_SIZE + offset); 
    }
	else if(DETECTOR_PHY_ADDR<=addr&&addr<=DETECTOR_PHY_ADDR + DETECTOR_SIZE)
	{
		offset=addr - DETECTOR_PHY_ADDR  ;
		*value = *(volatile DiUInt16 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset) ;  
	}
    else 
    {
       return -1;
    }
    
    return DI_SUCCESS;
}

/*************************************************
Function: 		MemBitRead32
Description:    read a data of uint32 from memory be allocated by PL
Calls: 			NULL
Called By: 		BitMoveOut32
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 MemBitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value)
{  
   DiUInt32 offset;   

   if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
        offset = addr - CPLD_PHY_ADDR ;
        *value = *(volatile DiUInt32 *)(pl_map_base + offset); 
   }
   else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
   {  
        offset = addr - DSP_PHY_ADDR ;   
        *value = *(volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + offset); 
   }
   else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
        offset = addr - DETECTOR_PHY_ADDR ;
        *value = *(volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset);  
   }
   else 
   {
        return -1;
   }   
   return DI_SUCCESS;
}

/*************************************************
Function: 		MemBitRead64
Description:    read a data of uint64 from memory be allocated by PL
Calls: 			NULL
Called By: 		BitMoveOut64
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 MemBitRead64(DiSession devHandle, DiUInt32 addr, DiPUInt64 value)
{  
    DiUInt32 offset;    

   if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
        offset = addr - CPLD_PHY_ADDR ;
        *value = *(volatile DiUInt64 *)(pl_map_base + offset); 
   }
   else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
   {  
        offset = addr - DSP_PHY_ADDR ;   
        *value = *(volatile DiUInt64 *)(pl_map_base + CPLD_SIZE + offset); 
   }
   else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
        offset = addr - DETECTOR_PHY_ADDR ;
        *value = *(volatile DiUInt64 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset);  
   }
   else 
   {
        return -1;
   }   

   return DI_SUCCESS;
}

/*************************************************
Function: 		BitRead32
Description:    read a data of uint32 from memory be allocated by PL
Calls: 			NULL
Called By: 		BitMoveOut32
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint32
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value)
{
	int iBack = 0;

	iBack = MemBitRead32(devHandle, addr, value) ;
	
	return iBack ;
}

/*************************************************
Function: 		BitRead32Ex
Description:    read a data of uint32 from memory be allocated by PL
Calls: 			NULL
Called By: 		BitMoveOut32
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint32
Output: 		value        --the value read from memory 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitRead32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiPUInt32 value)
{
	DiUInt32 addr = 0 ;
	int iBack = 0;
	
	addr = space + offset * sizeof(DiUInt32) ;
	iBack = MemBitRead32(devHandle, addr, value) ;
	
	return iBack ;
}

/*************************************************
Function: 		BitMoveOut8
Description:    read some dataes of uint8 from memory be allocated by PL
Calls: 			MemBitRead8
Called By: 		extern
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				length       --the length of value to read
Output: 		buf8         --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut8(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt8 buf8)
{
	DiUInt32 tempaddr = addr;
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length;i++)
    {
        iBack = MemBitRead8(devHandle, tempaddr, buf8 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        tempaddr += sizeof(DiUInt8);
    }
    return iBack;
}

/*************************************************
Function: 		BitMoveOut16
Description:    read some dataes of uint16 from memory be allocated by PL
Calls: 			MemBitRead16
Called By: 		extern
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				length       --the length of value to read
Output: 		buf16        --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut16(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt16 buf16)
{
	DiUInt32 tempaddr = addr;
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length;i++)
    {
        iBack = MemBitRead16(devHandle, tempaddr, buf16 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        tempaddr += sizeof(DiUInt16);
    }
    return iBack;
}

/*************************************************
Function: 		BitMoveOut32
Description:    read some dataes of uint32 from memory be allocated by PL
Calls: 			MemBitRead32
Called By: 		extern
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				length       --the length of value to read
Output: 		buf32        --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt32 buf32)
{
    DiUInt32 tempaddr = addr;
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead32(devHandle, tempaddr, buf32 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        tempaddr += sizeof(DiUInt32);
    }
    return iBack;
}

DiInt32 DBitMoveOut64(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt64 buf64)
{
	DiUInt32 tempaddr = addr;
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead64(devHandle, tempaddr, buf64 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        tempaddr += sizeof(DiUInt64);
    }
    return iBack;
}

/*************************************************
Function: 		BitMoveOut8Ex
Description:    read some dataes of uint8 from memory be allocated by PL
Calls: 			MemBitRead8
Called By: 		extern
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint8
				length       --the length of value to read
Output: 		buf8         --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut8Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt8 buf8)
{
	DiUInt32 addr = space + offset * sizeof(DiUInt8);
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead8(devHandle, addr, buf8 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        addr += sizeof(DiUInt8);
    }
    return iBack;
}

/*************************************************
Function: 		BitMoveOut16Ex
Description:    read some dataes of uint16 from memory be allocated by PL
Calls: 			MemBitRead16
Called By: 		extern
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint16
				length       --the length of value to read
Output: 		buf16         --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut16Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt16 buf16)
{
	DiUInt32 addr = space + offset * sizeof(DiUInt16);
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead16(devHandle, addr, buf16 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        addr += sizeof(DiUInt16);
    }
    return iBack;
} 

/*************************************************
Function: 		BitMoveOut32Ex
Description:    read some dataes of uint32 from memory be allocated by PL
Calls: 			MemBitRead32
Called By: 		extern
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint32
				length       --the length of value to read
Output: 		buf32         --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt32 buf32)
{
	DiUInt32 addr = space + offset * sizeof(DiUInt32);
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead32(devHandle, addr, buf32 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);
			return iBack;
        }
        addr += sizeof(DiUInt32);
    }
    return iBack;
}

/*************************************************
Function: 		BitMoveOut64Ex
Description:    read some dataes of uint64 from memory be allocated by PL
Calls: 			MemBitRead64
Called By: 		extern
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be read
				offset       --the offset of base address in uint64
				length       --the length of value to read
Output: 		buf64        --store the read values 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitMoveOut64Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt64 buf64)
{
	DiUInt32 addr = space + offset * sizeof(DiUInt64);
    int iBack = 0;  

    int i = 0;
    for(i = 0;i < length; i++)
    {
        iBack = MemBitRead64(devHandle, addr, buf64 + i);
        if(iBack < 0)
        {
			printf("block read failed at %d times\n",i);//due to the PL, must be read twice
			return iBack;
        }
        addr += sizeof(DiUInt64);
    }
    return iBack;
}

/*************************************************
Function: 		BitWrite8
Description:    write a data of uint8 from memory be allocated by PL
Calls: 			NULL
Called By: 		
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				value        --the value write to memory
Output: 		NULL 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 DBitWrite8(DiSession devHandle, DiUInt32 addr, DiUInt8 value)
{
   DiUInt32 offset;

   if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
		offset = addr -CPLD_PHY_ADDR ;
		*(volatile DiUInt8 *)(pl_map_base + offset) = value;

   }
   else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
   {
        offset = addr - DSP_PHY_ADDR ;
        *(volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + offset) = value;

   }
   else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
        offset = addr - DETECTOR_PHY_ADDR ;
        *(volatile DiUInt8 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset) = value ; 

   }
   else 
   {
      return -1;
   }
usleep(write_delay);
   return DI_SUCCESS;
}

/*************************************************
Function: 		BitWrite16
Description:    write a data of uint16 from memory be allocated by PL
Calls: 			NULL
Called By: 		
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				value        --the value write to memory
Output: 		NULL 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 DBitWrite16(DiSession devHandle,DiUInt32 addr,DiUInt16 value)
{
   DiInt32 offset;

   if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
      offset = addr - CPLD_PHY_ADDR ;
      *(volatile DiInt16 *)(pl_map_base + offset) = value;

   }
   else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
   {
		offset = addr - DSP_PHY_ADDR ;
		*(volatile DiInt16 *)(pl_map_base + CPLD_SIZE + offset) = value;
   }
   else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
        offset = addr - DETECTOR_PHY_ADDR ;
        *(volatile DiUInt16 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset) = value ; 
   }
   else 
   {
      return -1;
   }
 usleep(write_delay); 
   return DI_SUCCESS;
}

/*************************************************
Function: 		BitWrite32
Description:    write a data of uint32 from memory be allocated by PL
Calls: 			NULL
Called By: 		BitWrite32Ex
Input: 			devHandle    --handle of the device node
				addr         --address of the memory to be read
				value        --the value write to memory
Output: 		NULL 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
 DiInt32 DBitWrite32(DiSession devHandle,DiUInt32 addr,DiUInt32 value)
{
   DiUInt32 offset;   

   if(CPLD_PHY_ADDR <= addr && addr <= CPLD_PHY_ADDR + CPLD_SIZE)
   {
      offset = addr - CPLD_PHY_ADDR ;
	  //printf("offset:%d\n", offset) ;
      *(volatile DiUInt32 *)(pl_map_base + offset) = value;
   }
   else if(DSP_PHY_ADDR <= addr && addr <= DSP_PHY_ADDR + DSP_SIZE)
   {
		offset = addr - DSP_PHY_ADDR ;
		*(volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + offset) = value;
   }
   else if(DETECTOR_PHY_ADDR <= addr && addr <= DETECTOR_PHY_ADDR + DETECTOR_SIZE)
   {
        offset = addr - DETECTOR_PHY_ADDR ;
        *(volatile DiUInt32 *)(pl_map_base + CPLD_SIZE + DSP_SIZE + offset) = value ; 

   }
   else 
   {
      return -1;
   }
usleep(write_delay);  
   return DI_SUCCESS;
}

/*************************************************
Function: 		BitWrite32Ex
Description:    write some dataes of uint32 from memory be allocated by PL
Calls: 			BitWrite32
Called By: 		
Input: 			devHandle    --handle of the device node
				space        --base address of the physical memory to be write
				offset       --the offset of base address in uint32
				value        --the value write to memory
Output: 		NULL 
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 DBitWrite32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiUInt32 value)
{
	int iBack ;
	DiUInt32 addr = space + offset * sizeof(DiUInt32) ;
	
	iBack = DBitWrite32(devHandle, addr, value) ;
	
	return iBack ;
}



static dev_fun_opt* shareMem_fun;

void init_shareMem(void)
{
    shareMem_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    
    shareMem_fun->bus_name   = "VIRTUAL";
    shareMem_fun->dev_num    = 2;
    shareMem_fun->dev_type   = "MEMACC";
    shareMem_fun->open = shareMemOpen;
    shareMem_fun->read = shareMemRead;
    shareMem_fun->write = shareMemWrite;
    shareMem_fun->close= BitClose; 

    register_dev_fun(shareMem_fun);
}

void exit_shareMem(void)
{
    free(shareMem_fun);
    unregister_dev_fun(shareMem_fun);
}

