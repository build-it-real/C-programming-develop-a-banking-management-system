#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 100
#define MAX_EMAIL 100
#define USER_FILE "data/users.dat"

// User structure
struct User {
    int user_id;
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
    char email[MAX_EMAIL];
};

// Function declarations
int register_user();
int login_user();
int find_user_by_username(const char* username, struct User* user);
int get_next_user_id();

#endif
