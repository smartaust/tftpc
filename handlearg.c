#include <malloc.h>
#include <stdio.h>
#include <string.h>	
#include <unistd.h>
#include "handlearg.h"
void help()
{
                printf("\n<-----------------------HELP MENU----------------------->\n\n");
                printf ("./test host [PUT|GET] src [dst] [-p](parm) [-i]\n\n");
                printf ("   host     远程主机的IP\n");
                printf ("   PUT      上传数据\n");
                printf ("   GET      下载数据\n");
                printf ("   src      本地文件\n");
                printf ("   [dst]    本地文件在远程存的文件名，默认和本机相同\n");
                printf ("   -p parm  指定远程端口，后面加参数\n");
                printf ("   [-i]     指定二进制传输，默认以文本模式传输\n\n\n");
}

void CMDstructinit(CMDstruct * pcmd)	
{
	pcmd->ip = NULL ;
	pcmd->opttype = 0 ;
	pcmd->srcname = NULL ;
	pcmd->dstname = NULL ;
	pcmd->port = 0 ;
	pcmd->model = 0 ;
}


void CMDstructfree(CMDstruct *pcmd)
{
	if(pcmd->ip != NULL)
	{
		printf("free ip\n");
		free(pcmd->ip);
	}
	if(pcmd->srcname != NULL)
	{
		printf("free srcname\n");
		free(pcmd->srcname) ;
	}
	if(pcmd->dstname != NULL)
	{
		printf("free dstname\n");
		free (pcmd ->dstname);
	}

}


int handlearg(int argc ,char *argv[],CMDstruct *pcmd)
{
	 char ch ;
 	 int count = 0;
	 int ret ; 
	 while((ch=getopt(argc ,argv ,"ip:")) != -1)
	 {
		if(ch =='i')
		{
			count++ ;
			pcmd ->model = 1 ;
		}
		if(ch == 'p')
		{
			count+= 2 ;
			pcmd->port= atoi(optarg);	
		}

	 }

	ret = argc-count-1 ;//减去可执行文件名 和-i和-p两个参数

	if(ret < 3 || ret >4 )
	{
		return -1 ;
	}
	 

	if(3 == ret)
	{	
		pcmd ->ip =(char *)malloc(strlen(argv [count+1]+1));
		strcpy(pcmd->ip,argv[count+1]);

		if (!strcmp(argv[count+2],"PUT")||!strcmp(argv[count+2],"put"))	
		{
			pcmd->opttype =  1 ;
		
		}
		else if(!strcmp(argv[count+2],"GET")||!strcmp(argv[count+2],"get"))
		{
			pcmd->opttype = 2 ;
	
		}
		else
		{
			pcmd->opttype =-1 ;
		}
		
		pcmd ->srcname =(char *)malloc(strlen(argv [count+3])+1) ;
		strcpy(pcmd->srcname,argv[count+3]);
	
		pcmd->dstname = NULL ;

//		printf("there is no dstname\n");
	}

	if(4 == ret )
	{
	
		pcmd ->ip =(char *)malloc(strlen(argv [count+1])+1) ;
		strcpy(pcmd->ip,argv[count+1]);

		if (!strcmp(argv[count+2],"PUT")||!strcmp(argv[count+2],"put"))	
		{
			pcmd->opttype =  1 ;
		
		}
		else if(!strcmp(argv[count+2],"GET")||!strcmp(argv[count+2],"get"))
		{
			pcmd->opttype = 2 ;
	
		}
		else
		{
			pcmd->opttype =-1 ;
		}
			
		pcmd ->srcname =(char *)malloc(strlen(argv [count+3])+1) ;
		strcpy(pcmd->srcname,argv[count+3]);
	
		pcmd ->dstname =(char *)malloc(strlen(argv [count+4])+1) ;
		strcpy(pcmd->dstname,argv[count+4]);

	//	printf("there is dstname\n");
	}
		
	return 0 ;
	 
}
