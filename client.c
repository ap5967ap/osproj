#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"

void showAdminMenu(int sd){
    printf("Choose option:\n");
    printf("1. Add a new book.\n");;
    printf("2. Delete a book.\n");
    printf("3. Modify a book.\n");
    printf("4. Add a new user.\n");
    int response;
    scanf("%d",&response);
    write(sd,&response,sizeof(int));
}

int main(){
    struct sockaddr_in server;

    int sd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_addr.s_addr = inet_addr("192.168.42.181");
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);

    int stat = connect(sd,(struct sockaddr*)&server,sizeof(server));
    if(stat<0){
        perror("Connect");
    }

    char buf[BUFSIZ];
    read(sd,buf,BUFSIZ);
    printf("%s",buf);

    int authstat = 0;

    struct User temp;
    printf("Enter username: ");
    scanf("%s",temp.username);
    printf("\n Enter Password: ");
    scanf("%s",temp.password);
    temp.type = 0;

    printf("%s\n",temp.password);

    write(sd,&temp,sizeof(temp));

    read(sd,&authstat,sizeof(int));

    if(authstat == 0){
        printf("Logged in Successfully as Admin\n");
        printf("admin\n");

        while(1){
            showAdminMenu(sd);
        }
    } 
    else if(authstat == 1){
        printf("Logged in Successfully\n");
        printf("normal\n");
    }
    else {
        printf("Authentication Failed\n");
        return -1;
    }





}