#include "statement.h"

// Get transaction history for an account
int get_transaction_history(int account_id, int user_id, struct Transaction transactions[], int max_transactions) {
    FILE* file;
    char line[500];
    int count = 0;
    struct Transaction transaction;
    struct Account* account;
    
    // First verify account belongs to user
    account = get_account_by_id(account_id, user_id);
    if (account == NULL) {
        return 0;  // Account not found or doesn't belong to user
    }
    
    file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        return 0;  // No transactions file
    }
    
    // Read all transactions
    while (fgets(line, sizeof(line), file) && count < max_transactions) {
        // Parse: transaction_id|account_id|type|amount|date|description
        sscanf(line, "%d|%d|%19[^|]|%f|%19[^|]|%99[^\n]",
               &transaction.transaction_id,
               &transaction.account_id,
               transaction.type,
               &transaction.amount,
               transaction.date,
               transaction.description);
        
        // If transaction belongs to this account, add to array
        if (transaction.account_id == account_id) {
            transactions[count] = transaction;
            count++;
        }
    }
    
    fclose(file);
    return count;  // Number of transactions found
}

// Display transaction history
void display_transaction_history(int account_id, int user_id) {
    struct Transaction transactions[MAX_TRANSACTIONS];
    int count;
    
    count = get_transaction_history(account_id, user_id, transactions, MAX_TRANSACTIONS);
    
    if (count == 0) {
        printf("\nNo transactions found for this account.\n");
        return;
    }
    
    printf("\n=== Transaction History ===\n");
    printf("Account ID: %d\n", account_id);
    printf("%-5s %-12s %-12s %-12s %s\n", 
           "ID", "Date", "Type", "Amount", "Description");
    printf("--------------------------------------------------------------------------------\n");
    
    // Display transactions
    for (int i = 0; i < count; i++) {
        printf("%-5d %-12s %-12s $%-11.2f %s\n",
               transactions[i].transaction_id,
               transactions[i].date,
               transactions[i].type,
               transactions[i].amount,
               transactions[i].description);
    }
    
    printf("--------------------------------------------------------------------------------\n");
    printf("Total transactions: %d\n", count);
}

// Calculate summary statistics
void calculate_summary(struct Transaction transactions[], int count, 
                       float* total_deposits, float* total_withdrawals) {
    *total_deposits = 0.0;
    *total_withdrawals = 0.0;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(transactions[i].type, "DEPOSIT") == 0) {
            *total_deposits += transactions[i].amount;
        } else if (strcmp(transactions[i].type, "WITHDRAWAL") == 0) {
            *total_withdrawals += transactions[i].amount;
        }
    }
}

// Generate formatted account statement
void generate_account_statement(int account_id, int user_id) {
    struct Account* account;
    struct Transaction transactions[MAX_TRANSACTIONS];
    int count;
    float total_deposits, total_withdrawals;
    
    // Get account information
    account = get_account_by_id(account_id, user_id);
    if (account == NULL) {
        printf("Error: Account not found or you don't have access!\n");
        return;
    }
    
    // Get transaction history
    count = get_transaction_history(account_id, user_id, transactions, MAX_TRANSACTIONS);
    
    // Calculate summary
    calculate_summary(transactions, count, &total_deposits, &total_withdrawals);
    
    // Display statement header
    printf("\n");
    printf("========================================\n");
    printf("      ACCOUNT STATEMENT\n");
    printf("========================================\n");
    printf("Account ID:      %d\n", account->account_id);
    printf("Account Type:    %s\n", account->account_type);
    printf("Current Balance: $%.2f\n", account->balance);
    printf("Date Created:    %s\n", account->created_date);
    printf("========================================\n");
    printf("\n");
    
    // Display transaction history
    if (count == 0) {
        printf("No transactions to display.\n");
    } else {
        printf("TRANSACTION HISTORY\n");
        printf("------------------------------------------------------------\n");
        printf("%-5s %-12s %-12s %-12s %s\n", 
               "ID", "Date", "Type", "Amount", "Description");
        printf("------------------------------------------------------------\n");
        
        for (int i = 0; i < count; i++) {
            printf("%-5d %-12s %-12s $%-11.2f %s\n",
                   transactions[i].transaction_id,
                   transactions[i].date,
                   transactions[i].type,
                   transactions[i].amount,
                   transactions[i].description);
        }
        
        printf("------------------------------------------------------------\n");
    }
    
    // Display summary
    printf("\n");
    printf("SUMMARY\n");
    printf("------------------------------------------------------------\n");
    printf("Total Deposits:    $%.2f\n", total_deposits);
    printf("Total Withdrawals: $%.2f\n", total_withdrawals);
    printf("Net Change:        $%.2f\n", total_deposits - total_withdrawals);
    printf("Current Balance:   $%.2f\n", account->balance);
    printf("------------------------------------------------------------\n");
    printf("\n");
}
