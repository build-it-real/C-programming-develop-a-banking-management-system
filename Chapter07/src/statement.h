#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "account.h"

#define MAX_TRANSACTIONS 1000

// Function declarations
int get_transaction_history(int account_id, int user_id, struct Transaction transactions[], int max_transactions);
void display_transaction_history(int account_id, int user_id);
void generate_account_statement(int account_id, int user_id);
void calculate_summary(struct Transaction transactions[], int count, float* total_deposits, float* total_withdrawals);

#endif
