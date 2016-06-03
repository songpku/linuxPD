//--------------daemon.h-------------------
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syslog.h>
#include<time.h>
#include<sys/param.h>


int init_daemon(const char *pname, int facility);
