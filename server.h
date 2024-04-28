#ifndef SERVER_H
#define SERVER_H
#include"structs.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>
#include<sys/poll.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/resource.h>
#include<signal.h>
#include<time.h>
#include<pthread.h>
#include<sched.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define pr perror
#define PORT 5000





void admin_mode(int);
void add_book(int);
void remove_book(int);
// void
#endif // !SERVER_H