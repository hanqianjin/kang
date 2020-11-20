#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#include <string.h>  
#include <sys/types.h>  
#include <linux/input.h>
#include <sys/mman.h>  
#include <unistd.h>  
#include <fcntl.h>    
#include <signal.h> 
#include "sweepinterupt.h"

#define  KeyBoardDev  "/dev/input/event0"  
#define  PlInterruput "/dev/dpx-mem" 
#define  GpsUartDev   "/dev/ttyUL0"

int KeyFd = 0;
int PlInterruptFd = 0;
extern void ReleaseCtrlInHand(DiInt32 handle);
extern int sweepHandle; 
extern int SweepDoneFlag;
int firstInterrupt = 0;

void sig_handler(int signo)   
{    
//printf("ctrl app sweep interrupt    begin        ------------------\n");
   if (signo==SIGIO)   
   {   
   		if(firstInterrupt == 0)
   			{
				__sync_fetch_and_add(&firstInterrupt,1);
				ReleaseCtrlInHand(sweepHandle); 
				//printf("interrupt arrive~~~~~~~~~~~~~~\n");
				//firstInterrupt = 1;
   			}
		else
			{
// 				if(SweepDoneFlag == 0)
//			{
//				ReleaseCtrlInHand(sweepHandle); 
// 			}				
		}
	//printf("ctrl app sweep interrupt!!!!\n");
   }  
return; 
}

void OpenKeyValue()
{
   KeyFd = open ("/dev/input/event0", O_RDWR); 
   if (KeyFd <= 0)  
   {  
     printf ("open /dev/input/event0 device error!\n");  
     return;  
   } 
}

int OpenPlInterrupt()
{
#if BIT_DEBUG
    return 0;
#endif
    struct sigaction action;       

     memset(&action, 0, sizeof(action));   
    
     action.sa_handler = sig_handler; 
	
     //sigemptyset(&action.sa_mask);
     action.sa_flags = 0;       
   
     sigaction(SIGIO, &action, NULL);   

     PlInterruptFd = open(PlInterruput, O_RDONLY);   
     if(PlInterruptFd < 0)
     {
	 printf("can not open /dev/sync \n");
	 return -1;
     }
     //tell driver now thread's PID
     fcntl(PlInterruptFd, F_SETOWN, getpid());   
     //support sync
     fcntl(PlInterruptFd, F_SETFL, fcntl(PlInterruptFd, F_GETFL) | FASYNC);  
     return 0; 
}

void CloseKeyValue()
{
   close (KeyFd); 
}
void ClosePlInterrupt()
{
   close (PlInterruptFd);
}
void PlInterruptValue(int * keyValue)
{  
     struct input_event t;  
     if (read (PlInterruptFd, &t, sizeof (t)) == sizeof (t))  
     {  

	 if (t.type == EV_KEY) 
         {  
	     if (t.value == 0 || t.value == 1)  
	     {  
                   printf ("key %d %s\n", t.code, (t.value) ? "Pressed" : "Released"); 
		   if(t.value == 0)//HIGH
		   {                   
		      *keyValue = 0xff;
		   }
                   else//low
                   {
                      *keyValue = t.code;  
                   }
                   
	      } 
	 }    
     }  
}
void GetKeyValue(int * keyValue)
{  
     struct input_event t;  
     if (read (KeyFd, &t, sizeof (t)) == sizeof (t))  
     {  
	 if (t.type == EV_KEY) 
         {  
	     if (t.value == 0 || t.value == 1)  
	     {  
                   printf ("key %d %s\n", t.code, (t.value) ? "Pressed" : "Released"); 
		   if(t.value == 0)
		   {                   
		      *keyValue = 0xff;
                      
		   }
                   else
                   {
                      *keyValue = t.code;  
                   }
                   
	      } 
	 }    
     }  
}

