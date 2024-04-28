
struct User{
    char username [100];
    char password [100];
    int type;
};
struct Book
{
    char title[BUFSIZ];
    char author[BUFSIZ];
    bool valid;
    int copies;
    int id;
};