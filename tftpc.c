/****************************************
*filename : tftpc.c 
*function : main function  
****************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "handlearg.h"
#include "fileopt.h"

int main(int argc ,char *argv[])
{
	
	int ret ;
	CMDstruct  cmd ;
	CMDstructinit(&cmd);
	memset(&cmd , 0 ,sizeof(cmd)) ; 
	ret = handlearg(argc,argv,&cmd) ;	

	if(ret < 0)
	{
		help();	
		return 0 ;
	}

	if(cmd.opttype == 1 )
	{
		printf("put file\n");
		uploadfile_assic(&cmd);
	}
	else if (cmd.opttype == 2)
	{
		printf("get file\n");
		getfile_assic(&cmd);
		
		
	}	
	else
	{
		printf("parm err \n\n");
		help();
	
	}
	printf("ip:%s\nsrc:%s\ndst:%s\n",cmd.ip,cmd.srcname ,cmd.dstname);
	CMDstructfree(&cmd);
	return 0;

}
