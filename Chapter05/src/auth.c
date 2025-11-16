#include "auth.h"

#include <stdlib.h>

// Register a new user
int register_user() {
    struct User new_user;
    FILE* file;

    // Get user input
    printf("\n==== User Registration ===\n");
    
    printf("Enter username: ");
    scanf("%s", new_user.username);

    printf("Enter password: ");
    scanf("%s", new_user.password);

    // Validate password length
    if (strlen(new_user.password) < 6) {
        printf("Error: Password must be at least 6 characters!\n");
        return 0;
    }

    printf("Enter full name: ");
    getchar(); // Clear input buffer
    fgets(new_user.name, MAX_NAME, stdin);

    // Remove newline from fgets
    new_user.name[strcspn(new_user.name, "\n")] = 0;

    printf("Enter email: ");
    scanf("%s", new_user.email);

    // Check if username already exists
    struct User existing_user;
    
    if(find_user_by_username(new_user.username, &existing_user) == 1) {
        printf("Error: Username already exists!\n");
        return 0; // Registration failed
    }
    
    // Generate user ID
    new_user.user_id = get_next_user_id();

    // Open file for appending
    file = fopen(USER_FILE, "a");
    
    if (file == NULL) {
        // Try to create file
        file = fopen(USER_FILE, "w");
        
        if (file == NULL) {
            printf("Error: Cannot create user file! Please create 'data' directory\n");
            return 0;
        }

        fclose(file);

        file = fopen(USER_FILE, "a");
    }

    // Write user to file
    fprintf(file, "%d|%s|%s|%s|%s\n",
        new_user.user_id,
        new_user.username,
        new_user.password,
        new_user.name,
        new_user.email
    );

    fclose(file);

    printf("Registraion successfull! User ID: %d\n", new_user.user_id);

    return 1; // Success
}


// Login user
int login_user(){
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    struct User user;

    printf("\n=== User Login ===\n");

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Find user by username
    if (find_user_by_username(username, &user) != 1) {
        printf("Error: Username not found\n");
        return 0; // Login failed
    }

    // Check password
    if (strcmp(user.password, password) == 0) {
        printf("Login successful! Welcome, %s!\n", user.name);
        return user.user_id;
    } else {
        printf("Error: Invalid password!\n");
        return 0; // Login failed
    }
}

// Find user by username
int find_user_by_username(const char* username, struct User* user) {
    FILE* file;
    char line[500];
    
    file = fopen(USER_FILE, "r");
    if (file == NULL) {
        return 0;  // File doesn't exist or can't open
    }
    
    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        // Parse line: user_id|username|password|name|email
        sscanf(line, "%d|%49[^|]|%49[^|]|%99[^|]|%99[^\n]", 
               &user->user_id,
               user->username,
               user->password,
               user->name,
               user->email);
        
        // Check if username matches
        if (strcmp(user->username, username) == 0) {
            fclose(file);
            return 1;  // Found
        }
    }
    
    fclose(file);
    return 0;  // Not found
}

// Get next available user ID
int get_next_user_id() {
    FILE* file;
    int max_id = 0;
    int current_id;
    char line[500];
    
    file = fopen(USER_FILE, "r");
    if (file == NULL) {
        return 1;  // First user
    }
    
    // Read all users and find max ID
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|", &current_id);
        if (current_id > max_id) {
            max_id = current_id;
        }
    }
    
    fclose(file);
    return max_id + 1;  // Next ID
}
