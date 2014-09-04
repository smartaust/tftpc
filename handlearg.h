/***************************************************
*filename :handlearg.h
***************************************************/
#ifndef _HANDLE_H_
#define _HANDLE_H_


typedef struct cmdstruct 
{
	char *ip ;
	char opttype ;
	char *srcname;
	char *dstname ;
	int  port ;
	char model;	
}CMDstruct ;


void help();
void CMDstructinit(CMDstruct * pcmd);
void  CMDstructfree(CMDstruct * pcmd);
int handlearg(int argc, char *argv[] ,CMDstruct * pcmd);

#endif
