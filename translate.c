#include <sys/socket.h>
#include <string.h>
#include "translate.h"
int myrecvdata(int sock, Remote_information * remote)
{
	
	int ret ;
	int len ;
	fd_set fds ;
	struct timeval  tm;
	tm.tv_sec = 10 ;
	tm.tv_usec = 0 ;
	FD_ZERO (&fds);
	FD_SET (sock, &fds);
	len = sizeof(remote->remoteaddr);
	memset(remote->buf,0,sizeof (remote->buf)) ;
	ret = recvfrom(sock ,remote->buf,BUFLEN,0,&(remote->remoteaddr),&len);
	return ret ;
	
}

int mysenddata(int sock ,Remote_information* remote,int buflen)
{
	int ret  ;
	ret = sendto(sock ,remote->buf,buflen,0,&(remote->remoteaddr),sizeof(remote->remoteaddr));
	return ret ;
}
