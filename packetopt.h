/**********************************************
*file name : packetopt.h
***********************************************/
#ifndef _PACKETOPT_H_
#define _PACKETOPT_H_


#define   U16  unsigned int
#define   UNKNOWNERROR  "Unknown error"
#define   FILENOTFIND   "Request file is not exist"
#define   OPTILLAGE  "File access is illage"
#define   SPACELOW   "Disk space is not enough"
#define   FILEEXIST  "File is already existed"

typedef enum 
{
	 UNKNOWERR = 0 ,	
	 FILE_UNFIND = 1 ,
	 ILLAGE ,
	 LOWSPCE ,
	 FILE_EXIST
}ERR_TYPE ;

typedef enum PACKET_TYPE
{
         RRQ_PACKET = 1 ,
         WRQ_PACKET,
         DATA_PACKET,
         ACK_PACKET,
         ERR_PACKET
 } PACKET_TYPE;
	
/*typedef enum
{
	 RRQ = 1,
	 WRQ ,
	 DATA,
	 ACK ,
         ERR 
	
}PACKET_OPT_TYPE;*/

PACKET_TYPE  getoptcode(char *buf)  ;
int getRWRQparm (char *pfilename,char *model,char *buf) ;
int getAckparm  (char *buf) ;
int getDataparm  (char *buf);
int getErrparm  (U16 errno , char *errmsg) ;

int packetwrq(char * buf ,PACKET_TYPE type , char * filename ,char * model) ;
int packetack (U16 blocks,char *buf);
int packetdata (U16 blocks , char *pdata , int datalen) ;
int packeterr (char *buf, ERR_TYPE errtype , char * errmsg) ;


#endif 
