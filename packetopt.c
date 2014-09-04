/**********************************************************
filename : packetopt.c
**********************************************************/
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include "packetopt.h"

PACKET_TYPE  getoptcode(char *buf)  
{
	
	U16  optcode ;
	memcpy(&optcode ,buf,2) ;
	optcode = ntohs(optcode);
	return optcode ;
}

int getRWRQparm (char *pfilename,char *model,char *buf)
{
	int len ;
	strcpy(pfilename,buf+2);
	len = strlen(buf+2);
	strcpy(model,buf+3+len);
	return 0 ;
}

int getAckparm  (char * buf)
{
	U16 blocks ;
 	memcpy(&blocks,buf+2,2);
	blocks = ntohs(blocks);
	return blocks ;
}
	
int getErrparm  (U16 errno , char *errmsg) 
{	
	return 0 ;
	
}


int getDataparm (char * buf)
{
	U16  blocks ;
	memcpy(&blocks , buf+2 , 2);
	blocks = ntohs(blocks);
	return  blocks ;
}

	
int packetwrq(char *buf , PACKET_TYPE type , char * filename ,char * model) 
{
		int ret ;
		U16 packettype = type ;
		packettype = htons(packettype);
		
		memcpy(buf,&packettype,2 );
		ret = sprintf(buf+2 ,"%s%c%s%c",filename ,0x00 ,model ,0x00);
		return ret + 2 ;
	 
}



int packetack (U16 blocks,char *buf)
{
	 U16   optcode = ACK_PACKET ;
	 optcode = htons(optcode) ;
	 blocks= htons(blocks);
	 memcpy(buf,&optcode,2);	
	 memcpy(buf+2 ,&blocks ,2);
	 return 4 ;
}
	
int packetdata (U16 blocks , char *buf , int fd )
{ 		
	 int ret ;
	 char data[1024] = {0}  ;
	 U16  optcode = DATA_PACKET ;
	 optcode = htons(optcode);
	 blocks  = htons(blocks);
         ret = read(fd ,data ,512);
	 memcpy(buf,&optcode,2);
	 memcpy(buf+2,&blocks,2);
	 memcpy(buf+4,data,ret);
	 return ret+4 ;
}

int packeterr (char *buf , ERR_TYPE errtype , char * errmsg) 
{
	U16  optcode  =  ERR_PACKET ;
	U16  errno = errtype ;
	optcode = htons(optcode);
	errno = htons (errno);
	memcpy(buf, &optcode,2);
	memcpy (buf+2,&errno,2);
	strcpy(buf+4,errmsg);
	return strlen(errmsg) + 4;
}
