#ifndef VERIFY_SESSION_H
#define VERIFY_SESSION_H

typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
} UserData;

int login();

#endif
