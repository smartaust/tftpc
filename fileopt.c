/***********************************************
*文 件 名：fileopt.c
*文件作用：tftp上传下载功能函数实现
*文件日期：2104-8-26
***********************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "handlearg.h"
#include "translate.h"
#include "packetopt.h"

static int  handlepacket(Remote_information * remoteptr) ;
	
int  getfile_assic(CMDstruct *pcmd) 
{		
	int sock ;
	int ret ;
	int len ;
	int fd ;
	int res ;
	unsigned short int  block = 1 ;

	PACKET_TYPE  packettype ;

	Remote_information  remote  ;

	unsigned short int count = 0;
	struct sockaddr_in sin;
	struct sockaddr_in recv_sin ;
        char testcmd[60] = {0};
	bzero(&sin,sizeof(sin));
	bzero(&remote,sizeof (Remote_information));

	len = sizeof(sin) ;
	sin.sin_family = AF_INET ;
	sin.sin_addr.s_addr = inet_addr(pcmd->ip);
	sin.sin_port = htons(pcmd->port);

	//添加判断该文件是否存在，如果是覆盖还是删除	
	fd = open(pcmd->dstname,O_WRONLY|O_CREAT,0644);
	remote.remoteaddr = *((struct sockaddr*)&sin) ;

        sock =  socket(AF_INET,SOCK_DGRAM,0);	

	len = packetwrq(remote.buf,RRQ_PACKET,pcmd->srcname,"octet");
	ret = mysenddata(sock,&remote,len);
	if(ret > 0)	
	{
		printf("send ok\n");
	}
	if(ret < 0 )	
	{
		printf("send err\n");
		return -1 ;

	}

	memset(remote.buf,0,sizeof(remote.buf));
	while((ret=myrecvdata(sock,&remote)))
	{	
		
		res = handlepacket(&remote);
		if(1 == res )
		{
//			printf("works \n");
			if(block == getDataparm  (remote.buf))
			{
				ret = write(fd,remote.buf+4,ret -4) ;
				if(ret < 0 )
				{
					continue ;
				}
				else 
				{
				//	printf("worked\n");
					memset(remote.buf,0,sizeof(remote.buf));
					len = packetack(block ,remote.buf) ;
					mysenddata(sock,&remote,len);
					block++;
					if(ret < 512)
					{
						printf("the last packet ,break \n");
						break ;
					}
					
				}
			}
			
		}
		else if(-1 == res )
		{
			
			printf("file not exist\n");
			break ;
		}
		else if(-2 == res )
		{
			printf("unknow erro\n");
			break ;
		}	
	
	}
	
				
	
	
	return 0 ;
}


int  uploadfile_assic(CMDstruct *pcmd)
{
	int sock;
	int len ;	
	int ret ;
	unsigned short int block  = 0 ;
	int fd ;
	struct sockaddr_in  sin ;
	Remote_information remote;

	bzero(&remote ,sizeof (remote)) ;
	bzero(&sin,sizeof (sin))  ;
	
	sin.sin_family = AF_INET ;
	sin.sin_addr.s_addr = inet_addr(pcmd->ip);
	sin.sin_port= htons(pcmd->port);

	remote.remoteaddr = *(struct sockaddr *)&sin ;

	fd = open(pcmd->srcname ,O_RDONLY,0644) ;
	if(fd > 0)
	{
		printf("ok\n");
	}
	sock = socket(AF_INET,SOCK_DGRAM,0);	
	//ret =wrq_packet(WRQ_PACKET,"test.jpg","octet",testcmd);
	
	len = packetwrq(remote.buf,WRQ_PACKET,pcmd->dstname,"octet");
	ret = mysenddata(sock,&remote,len);
        if(ret < 0 )
        {
               printf("packet error\n");
	}


	while((ret = myrecvdata(sock,&remote)))
        {
			if(getoptcode(remote.buf) == ACK_PACKET)
			{
			
				if ( getAckparm (remote.buf) == block)
				{
					block++ ;
					ret = packetdata(block ,remote.buf,fd);
					mysenddata(sock,&remote ,ret);
					
					if(ret <516 )
					{
						break ;	
					}	
				}
			}
		 
	}

	printf("translate complete\n");
        return 0 ;
} 





static int handlepacket(Remote_information * remoteptr) 
{

//	printf("handle packet\n");	
	switch (getoptcode(remoteptr->buf))
	{
		
		case  DATA_PACKET :
			
			return 1 ;
		
		case  ERR_PACKET :
			return -1;
			break ;
		default :
			return -2 ;
	}
}



















