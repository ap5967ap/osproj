#include"server.h"


int get_id()
{
    struct flock lock;
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    int fd=open("books.txt",O_RDONLY,0666);
    int offset=lseek(fd,-1*sizeof(struct Book),SEEK_END);
    lock.l_start=offset;
    if(lock.l_start<=0)
        return 1;
    lock.l_len=sizeof(struct Book);
    lock.l_pid=getpid();
    fcntl(fd,F_SETLKW,&lock);
    struct Book temp;
    read(fd,&temp,sizeof(struct Book));
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    return temp.id+1;
}
void add_book(int nsd)
{
    struct Book temp;
    bzero(&temp,sizeof(struct Book));
    int id=get_id();
    temp.id=id;
    read(nsd,&temp,sizeof(struct Book));
    printf("Title: %s\n",temp.title);
    printf("Author: %s\n",temp.author);
    printf("Copies: %d\n",temp.copies);
    printf("ID: %d\n",temp.id);
    struct flock lock;
    int fd=open("books.txt",O_WRONLY|O_CREAT,0666);
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_len=0;
    lock.l_start=0;
    lock.l_pid=0;
    fcntl(fd,F_SETLKW,&lock);
    lseek(fd,0,SEEK_END);
    write(fd,&temp,sizeof(struct Book));
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    close(fd);
    get_all_books(nsd);

}
void get_all_books(int nsd)
{
    struct Book books[100];
    int fd=open("books.txt",O_RDONLY,0666);
    struct flock lock;
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=0;
    lock.l_pid=getpid();
    fcntl(fd,F_SETLKW,&lock);
    int i=0;
    while(read(fd,&books[i],sizeof(struct Book)))
    {
        i++;
    }
    lock.l_type=F_UNLCK;
    fcntl(fd,F_SETLKW,&lock);
    // write(nsd,&i,sizeof(int));
    for(int j=0;j<i;j++)
    {
        write(1,&books[j],sizeof(struct Book));
    }
}

void admin_mode(int nsd)
{
    while(1)
    {
        int choice;
        read(nsd,&choice,sizeof(choice));
        printf("Choice: %d\n",choice);
        if(choice==1)
        {
            add_book(nsd);
        }
        else if(choice==2)
        {
            // delete_book(nsd);
        }
        else if(choice==3)
        {
            // modify_book(nsd);
        }
        else if(choice==4)
        {
            // add_user(nsd);
        }
        else
        {
            return;
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
    // ok=0;
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
    printf("Server listening.. on port %d\n",PORT);
    while(1)
    {
        len=sizeof(cli);
        nsd=accept(sd,(struct sockaddr*)&cli,&len);
        pthread_t tid;
        pthread_create(&tid,NULL,func,(void*)&nsd);
        
    }
}