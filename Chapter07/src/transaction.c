#include "transaction.h"
#include <time.h>

// Get next transaction ID
int get_next_transaction_id() {
    FILE* file;
    int max_id = 0;
    int current_id;
    char line[500];
    
    file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        return 1;  // First transaction
    }
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|", &current_id);
        if (current_id > max_id) {
            max_id = current_id;
        }
    }
    
    fclose(file);
    return max_id + 1;
}

// Record a transaction
int record_transaction(int account_id, const char* type, float amount, const char* description) {
    FILE* file;
    struct Transaction transaction;
    char date_str[20];
    
    // Set transaction details
    transaction.transaction_id = get_next_transaction_id();
    transaction.account_id = account_id;
    strcpy(transaction.type, type);
    transaction.amount = amount;
    
    // Get current date
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(date_str, 20, "%Y-%m-%d", tm_info);
    strcpy(transaction.date, date_str);
    
    if (description != NULL && strlen(description) > 0) {
        strcpy(transaction.description, description);
    } else {
        strcpy(transaction.description, "");
    }
    
    // Append to transactions file
    file = fopen(TRANSACTION_FILE, "a");
    if (file == NULL) {
        file = fopen(TRANSACTION_FILE, "w");
        if (file == NULL) {
            return 0;  // Error
        }
        fclose(file);
        file = fopen(TRANSACTION_FILE, "a");
    }
    
    fprintf(file, "%d|%d|%s|%.2f|%s|%s\n",
            transaction.transaction_id,
            transaction.account_id,
            transaction.type,
            transaction.amount,
            transaction.date,
            transaction.description);
    
    fclose(file);
    return 1;  // Success
}

// Update account balance
int update_account_balance(int account_id, int user_id, float new_balance) {
    FILE* file;
    struct Account accounts[1000];
    int count = 0;
    int found = 0;
    char line[500];
    
    // Read all accounts
    file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        return 0;  // File doesn't exist
    }
    
    while (fgets(line, sizeof(line), file) && count < 1000) {
        sscanf(line, "%d|%d|%19[^|]|%f|%19[^\n]",
               &accounts[count].account_id,
               &accounts[count].user_id,
               accounts[count].account_type,
               &accounts[count].balance,
               accounts[count].created_date);
        
        // Update balance if this is the target account
        if (accounts[count].account_id == account_id && 
            accounts[count].user_id == user_id) {
            accounts[count].balance = new_balance;
            found = 1;
        }
        count++;
    }
    fclose(file);
    
    if (!found) {
        return 0;  // Account not found
    }
    
    // Write all accounts back
    file = fopen(ACCOUNT_FILE, "w");
    if (file == NULL) {
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%d|%s|%.2f|%s\n",
                accounts[i].account_id,
                accounts[i].user_id,
                accounts[i].account_type,
                accounts[i].balance,
                accounts[i].created_date);
    }
    
    fclose(file);
    return 1;  // Success
}

// Deposit money
int deposit(int user_id, int account_id, float amount, const char* description) {
    struct Account* account;
    
    // Validate amount
    if (amount <= 0) {
        printf("Error: Deposit amount must be positive!\n");
        return 0;
    }
    
    // Get account (verifies it belongs to user)
    account = get_account_by_id(account_id, user_id);
    if (account == NULL) {
        printf("Error: Account not found or you don't have access!\n");
        return 0;
    }
    
    // Calculate new balance
    float old_balance = account->balance;
    float new_balance = old_balance + amount;
    
    // Update account balance
    if (!update_account_balance(account_id, user_id, new_balance)) {
        printf("Error: Failed to update account balance!\n");
        return 0;
    }
    
    // Record transaction
    if (!record_transaction(account_id, "DEPOSIT", amount, description)) {
        printf("Warning: Transaction recorded but balance update may have failed!\n");
    }
    
    printf("Deposit successful!\n");
    printf("Amount deposited: $%.2f\n", amount);
    printf("Previous balance: $%.2f\n", old_balance);
    printf("New balance: $%.2f\n", new_balance);
    
    return 1;
}

// Withdraw money
int withdraw(int user_id, int account_id, float amount, const char* description) {
    struct Account* account;
    
    // Validate amount
    if (amount <= 0) {
        printf("Error: Withdrawal amount must be positive!\n");
        return 0;
    }
    
    // Get account (verifies it belongs to user)
    account = get_account_by_id(account_id, user_id);
    if (account == NULL) {
        printf("Error: Account not found or you don't have access!\n");
        return 0;
    }
    
    // Check sufficient balance
    if (account->balance < amount) {
        printf("Error: Insufficient balance!\n");
        printf("Current balance: $%.2f\n", account->balance);
        printf("Requested withdrawal: $%.2f\n", amount);
        return 0;
    }
    
    // Calculate new balance
    float old_balance = account->balance;
    float new_balance = old_balance - amount;
    
    // Update account balance
    if (!update_account_balance(account_id, user_id, new_balance)) {
        printf("Error: Failed to update account balance!\n");
        return 0;
    }
    
    // Record transaction
    if (!record_transaction(account_id, "WITHDRAWAL", amount, description)) {
        printf("Warning: Transaction recorded but balance update may have failed!\n");
    }
    
    printf("Withdrawal successful!\n");
    printf("Amount withdrawn: $%.2f\n", amount);
    printf("Previous balance: $%.2f\n", old_balance);
    printf("New balance: $%.2f\n", new_balance);
    
    return 1;
}
