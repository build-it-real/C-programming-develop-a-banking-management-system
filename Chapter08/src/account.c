#include "account.h"
#include <time.h>

// Get current date as string
void get_current_date(char* date_str) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(date_str, 20, "%Y-%m-%d", tm_info);
}

// Get next available account ID
int get_next_account_id() {
    FILE* file;
    int max_id = 0;
    int current_id;
    char line[500];
    
    file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        return 1;  // First account
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

// Create a new account
int create_account(int user_id) {
    struct Account new_account;
    FILE* file;
    char account_type_choice;
    
    printf("\n=== Create New Account ===\n");
    printf("Select account type:\n");
    printf("1. Savings\n");
    printf("2. Checking\n");
    printf("Enter choice: ");
    
    scanf(" %c", &account_type_choice);
    
    if (account_type_choice == '1') {
        strcpy(new_account.account_type, "Savings");
    } else if (account_type_choice == '2') {
        strcpy(new_account.account_type, "Checking");
    } else {
        printf("Invalid choice!\n");
        return 0;
    }
    
    printf("Enter initial balance: ");
    scanf("%f", &new_account.balance);
    
    if (new_account.balance < 0) {
        printf("Error: Initial balance cannot be negative!\n");
        return 0;
    }
    
    // Set account details
    new_account.account_id = get_next_account_id();
    new_account.user_id = user_id;
    get_current_date(new_account.created_date);
    
    // Open file for appending
    file = fopen(ACCOUNT_FILE, "a");
    if (file == NULL) {
        file = fopen(ACCOUNT_FILE, "w");
        if (file == NULL) {
            printf("Error: Cannot create account file!\n");
            return 0;
        }
        fclose(file);
        file = fopen(ACCOUNT_FILE, "a");
    }
    
    // Write account to file
    fprintf(file, "%d|%d|%s|%.2f|%s\n",
            new_account.account_id,
            new_account.user_id,
            new_account.account_type,
            new_account.balance,
            new_account.created_date);
    
    fclose(file);
    printf("Account created successfully! Account ID: %d\n", new_account.account_id);
    return new_account.account_id;
}

// Get all accounts for a user
int get_user_accounts(int user_id, struct Account accounts[], int max_accounts) {
    FILE* file;
    char line[500];
    int count = 0;
    struct Account account;
    
    file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        return 0;  // No accounts file yet
    }
    
    // Read all accounts
    while (fgets(line, sizeof(line), file) && count < max_accounts) {
        sscanf(line, "%d|%d|%19[^|]|%f|%19[^\n]",
               &account.account_id,
               &account.user_id,
               account.account_type,
               &account.balance,
               account.created_date);
        
        // If account belongs to this user, add to array
        if (account.user_id == user_id) {
            accounts[count] = account;
            count++;
        }
    }
    
    fclose(file);
    return count;  // Number of accounts found
}

// Get account by ID (and verify it belongs to user)
struct Account* get_account_by_id(int account_id, int user_id) {
    static struct Account account;
    FILE* file;
    char line[500];
    
    file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        return NULL;
    }
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%d|%19[^|]|%f|%19[^\n]",
               &account.account_id,
               &account.user_id,
               account.account_type,
               &account.balance,
               account.created_date);
        
        // Check if this is the account we're looking for
        if (account.account_id == account_id && account.user_id == user_id) {
            fclose(file);
            return &account;
        }
    }
    
    fclose(file);
    return NULL;  // Not found
}

// Display account information
void display_account(struct Account* account) {
    if (account == NULL) {
        printf("Error: Invalid account!\n");
        return;
    }
    
    printf("\n--- Account Details ---\n");
    printf("Account ID:    %d\n", account->account_id);
    printf("Type:          %s\n", account->account_type);
    printf("Balance:       $%.2f\n", account->balance);
    printf("Created:       %s\n", account->created_date);
    printf("-----------------------\n");
}

// Display all accounts for a user
void display_user_accounts(int user_id) {
    struct Account accounts[100];
    int count;
    
    count = get_user_accounts(user_id, accounts, 100);
    
    if (count == 0) {
        printf("\nNo accounts found. Create your first account!\n");
        return;
    }
    
    printf("\n=== Your Accounts ===\n");
    printf("%-10s %-15s %-15s %-12s\n", "Account ID", "Type", "Balance", "Created");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10d %-15s $%-14.2f %-12s\n",
               accounts[i].account_id,
               accounts[i].account_type,
               accounts[i].balance,
               accounts[i].created_date);
    }
    printf("------------------------------------------------------------\n");
    printf("Total accounts: %d\n", count);
}
