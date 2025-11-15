#include <stdio.h>
#include "auth.h"

int main() {
    int choice;
    int logged_in_user_id = 0;  // 0 means not logged in
    
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
                    printf("Create Account - Coming in Chapter 5!\n");
                    break;
                case 2:
                    printf("View Accounts - Coming in Chapter 5!\n");
                    break;
                case 3:
                    printf("Deposit - Coming in Chapter 6!\n");
                    break;
                case 4:
                    printf("Withdraw - Coming in Chapter 6!\n");
                    break;
                case 5:
                    printf("View Statement - Coming in Chapter 7!\n");
                    break;
                case 6:
                    logged_in_user_id = 0;  // Logout
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
