#include <stdio.h>
#include "auth.h"
#include "account.h"
#include "transaction.h"
#include "statement.h"

int main() {
    int choice;
    int logged_in_user_id = 0;
    int account_id;
    float amount;
    char description[100];
    
    do {
        if (logged_in_user_id == 0) {
            // Main menu (not logged in)
            printf("\n=== Banking Management System ===\n");
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    register_user();
                    break;
                case 2:
                    logged_in_user_id = login_user();
                    break;
                case 3:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
                    break;
            }
        } else {
            // Banking menu (logged in)
            printf("\n=== Banking Menu ===\n");
            printf("1. Create Account\n");
            printf("2. View Accounts\n");
            printf("3. Deposit\n");
            printf("4. Withdraw\n");
            printf("5. View Statement\n");
            printf("6. Logout\n");
            printf("Enter your choice: ");
            
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    create_account(logged_in_user_id);
                    break;
                case 2:
                    display_user_accounts(logged_in_user_id);
                    break;
                case 3:
                    printf("\n=== Deposit ===\n");
                    printf("Enter account ID: ");
                    scanf("%d", &account_id);
                    printf("Enter amount: ");
                    scanf("%f", &amount);
                    printf("Enter description (optional): ");
                    getchar();
                    fgets(description, sizeof(description), stdin);
                    description[strcspn(description, "\n")] = 0;
                    deposit(logged_in_user_id, account_id, amount, description);
                    break;
                case 4:
                    printf("\n=== Withdraw ===\n");
                    printf("Enter account ID: ");
                    scanf("%d", &account_id);
                    printf("Enter amount: ");
                    scanf("%f", &amount);
                    printf("Enter description (optional): ");
                    getchar();
                    fgets(description, sizeof(description), stdin);
                    description[strcspn(description, "\n")] = 0;
                    withdraw(logged_in_user_id, account_id, amount, description);
                    break;
                case 5:
                    printf("\n=== View Statement ===\n");
                    printf("Enter account ID: ");
                    scanf("%d", &account_id);
                    generate_account_statement(account_id, logged_in_user_id);
                    break;
                case 6:
                    logged_in_user_id = 0;
                    printf("Logged out successfully.\n");
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
                    break;
            }
        }
        
    } while (choice != 3 || logged_in_user_id != 0);
    
    printf("Thank you for using Banking Management System!\n");
    
    return 0;
}
