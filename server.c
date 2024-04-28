#include"server.h"

void add

void admin_mode(int nsd)
{
    while(1)
    {
        int choice;
        read(nsd,&choice,sizeof(choice));
        if(choice==1)
        {
            // add_book(nsd);
        }
        if(choice==2)
        {
            // delete_book(nsd);
        }
        if(choice==3)
        {
            // modify_book(nsd);
        }
        if(choice==4)
        {
            // add_user(nsd);
        }
    }
}

void *func(void *args)
{
    int nsd=*((int *)args);
    printf("%d\n",nsd);
    write(nsd,"Connected to server\n",sizeof("Connected to server\n"));
    struct User temp;
    read(nsd,&temp,sizeof(struct User));
    printf("Username: %s\n",temp.username);
    printf("Password: %s\n",temp.password);
    struct flock lock;
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    lock.l_pid=getpid();
    int fd=open("users.txt",O_RDONLY,0666);
    fcntl(fd,F_SETLKW,&lock);
    struct User u;
    int flag=0;
    while(read(fd,&u,sizeof(u)))
    {
        if(strcmp(u.username,temp.username)==0)
        {
            flag=1;
            break;
        }
    }
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    int ok;
    // printf("%s %s\n",u.password,temp.password);
    if(strcmp(u.password,temp.password))
        ok=-1;
    else ok=strcmp(u.password,temp.password);
    write(nsd,&ok,sizeof(int));
    if(ok==0)
    {
        admin_mode(nsd);
    }

}

int main()
{
    int sd,nsd,len;
    struct sockaddr_in serv,cli;
    sd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&serv, sizeof(serv)); 
    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    serv.sin_port=htons(PORT);
    bind(sd,(struct sockaddr*)&serv,sizeof(serv));
    listen(sd,50);
    printf("Server listening.. on port \n");
    while(1)
    {
        len=sizeof(cli);
        nsd=accept(sd,(struct sockaddr*)&cli,&len);
        pthread_t tid;
        pthread_create(&tid,NULL,func,(void*)&nsd);
        
    }
}