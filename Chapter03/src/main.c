#include <stdio.h>

int main() {
    int choice;

    do {
        printf("=== Banking Management System ===\n");

        printf("1. Register\n");

        printf("2. Login\n");

        printf("3. Exit\n");

        printf("Enter your choice: \n");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Registration feature - Coming soon!!\n");
                break;

            case 2:
                printf("Login feature - Coming soon!!\n");
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again...\n");
                break;
        }

    } while (choice != 3);

    printf("Thank yu for using Banking Management System");

    return 0;
}