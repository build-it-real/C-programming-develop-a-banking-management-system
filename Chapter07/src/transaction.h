#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdio.h>
#include <string.h>
#include "account.h"

#define MAX_TRANSACTION_TYPE 20
#define MAX_DESCRIPTION 100
#define TRANSACTION_FILE "data/transactions.dat"

// Transaction structure
struct Transaction {
    int transaction_id;
    int account_id;
    char type[MAX_TRANSACTION_TYPE];
    float amount;
    char date[20];
    char description[MAX_DESCRIPTION];
};

// Function declarations
int deposit(int user_id, int account_id, float amount, const char* description);
int withdraw(int user_id, int account_id, float amount, const char* description);
int update_account_balance(int account_id, int user_id, float new_balance);
int record_transaction(int account_id, const char* type, float amount, const char* description);
int get_next_transaction_id();

#endif
