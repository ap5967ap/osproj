#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
struct User{
    char username [100];
    char password [100];
    int type;
};
struct Book
{
    char title[100];
    char author[100];
    // bool valid;
    int copies;
    int id;
};