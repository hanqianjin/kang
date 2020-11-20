#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "SaDataStruct.h"
#include "DigSigDealVirtualDriver.h"
#include <fcntl.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BITMSGBUFFER 1024
#define PORT 5555

FILE *fp = NULL;
pthread_t threadId;
pthread_t connectId;
static void* CalcFlatCtrl(void *functionData);
static void* MultiConncet(void* param);

static int serverId = 0;
static int clientId = 0;
static char cbuffer[BITMSGBUFFER];
struct sockaddr_in svraddr = {0};
struct sockaddr_in clientaddr = {0};

int main(int argc, char *argv[])
{
	DiInt32 iBack = 0;

	char pPath[256] = {0};
    	getcwd(pPath, 256);
	strcat(pPath,"/SaFlatCalc.txt");
	fp = fopen(pPath,"w");

	serverId = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(-1 == serverId)
	{
		perror("server create socket failed\n");
		return -1;
	}
	printf("the server ID is%d\n\n",serverId);
	  
   	svraddr.sin_family = AF_INET;
   	svraddr.sin_port = htons(PORT);
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(serverId,(struct sockaddr *)&svraddr,sizeof(svraddr));
	listen(serverId,SOMAXCONN);//noblock	

		//start calc thread
	iBack = pthread_create(&connectId,NULL,MultiConncet,NULL);
	if(iBack < 0)
	{
		perror("multi connect thread create fail");
		return iBack;
	}

	int ialive = 1;
	char ch = ' ';	

	while(ialive && (ch = getchar()))
	{
		switch(ch)
		{
			case 'q':
			if(close(clientId) < 0)
				printf("client close falied\n");
			else
				printf("client close OK\n");
			if(close(serverId) < 0)
				printf("server close failed\n");
			else
				printf("server close OK\n");
			ialive = 0;
			break;
		}	
	}	
	return 0;
}

static void* MultiConncet(void* param)
{
	int iBack = 0;
	while(1)
	{
		int clientaddrLen = sizeof(clientaddr);
		printf("wait for client...\n");
		clientId = accept(serverId,(struct sockaddr*)&clientaddr,&clientaddrLen);
		printf("have a client comes...\n");

		//start calc thread
		iBack = pthread_create(&threadId,NULL,CalcFlatCtrl,NULL);
		if(iBack < 0)
		{
			perror("mid msg thread create fail");
			return NULL;
		}
	};
	return NULL;
}

static int liverun = 1;
static void* CalcFlatCtrl(void *functionData)
{
	int ret = 0;
	int result = 0;	
	while(liverun)
	{
		memset(cbuffer,0,BITMSGBUFFER);
		//receive msg
		printf("wait cmd from client...\n");
		ret = recv(clientId,cbuffer,BITMSGBUFFER,0);
		if(ret <= 0)
		{
			printf("the connect has disconnect!!\n");			
			return NULL;
		}
		cbuffer[ret] = '\0';

		//parase the buffer
		printf("%s\n",cbuffer);
		sscanf(cbuffer,"%d",&result);
		printf("the result val is%d\n",result);
		switch(result)
		{
			case 1:
				sprintf(cbuffer,"%d",100);
				send(clientId, cbuffer, strlen(cbuffer), 0);
			break;
			case 33:
				sprintf(cbuffer,"%d",111);
				send(clientId, cbuffer, strlen(cbuffer), 0);
			break;
			case -1:
			liverun = 0;
			break;
		}		

	};
	
	fclose(fp);
	printf("the calc is over\n");
	return NULL;
}
