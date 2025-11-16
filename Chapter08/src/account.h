#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdio.h>
#include <string.h>
#include "auth.h"

#define MAX_ACCOUNT_TYPE 20
#define ACCOUNT_FILE "data/accounts.dat"

// Account structure
struct Account {
    int account_id;
    int user_id;
    char account_type[MAX_ACCOUNT_TYPE];
    float balance;
    char created_date[20];
};

// Function declarations
int create_account(int user_id);
void display_account(struct Account* account);
void display_user_accounts(int user_id);
int get_user_accounts(int user_id, struct Account accounts[], int max_accounts);
struct Account* get_account_by_id(int account_id, int user_id);
int get_next_account_id();
void get_current_date(char* date_str);

#endif
