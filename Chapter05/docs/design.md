# Banking Management System - Design Document

## Overview

This document describes the detailed design of the Banking Management System, including data structures, file formats, module design, and algorithms.

## Data Structures

### User Structure

```c
struct User {
    int user_id;           // Unique identifier (auto-incrementing)
    char username[50];     // Login username (unique)
    char password[50];     // Login password (plain text for simplicity)
    char name[100];        // Full name
    char email[100];       // Email address
};
```

**Size:** Approximately 300 bytes per user  
**Storage:** `users.dat` file

### Account Structure

```c
struct Account {
    int account_id;        // Unique identifier (auto-incrementing)
    int user_id;          // Foreign key to User (links account to user)
    char account_type[20]; // Account type: "Savings" or "Checking"
    float balance;        // Current balance (non-negative)
    char created_date[20]; // Date in format: "YYYY-MM-DD"
};
```

**Size:** Approximately 60 bytes per account  
**Storage:** `accounts.dat` file

### Transaction Structure

```c
struct Transaction {
    int transaction_id;   // Unique identifier (auto-incrementing)
    int account_id;       // Foreign key to Account
    char type[20];        // Transaction type: "DEPOSIT" or "WITHDRAWAL"
    float amount;         // Transaction amount (positive)
    char date[20];        // Date in format: "YYYY-MM-DD"
    char description[100]; // Optional transaction description
};
```

**Size:** Approximately 180 bytes per transaction  
**Storage:** `transactions.dat` file

## File Formats

### Text Format (Recommended for Beginners)

Each file stores records as text, one record per line, fields separated by delimiters.

#### users.dat Format
```
user_id|username|password|name|email
1|john_doe|password123|John Doe|john@example.com
2|jane_smith|mypass456|Jane Smith|jane@example.com
```

#### accounts.dat Format
```
account_id|user_id|account_type|balance|created_date
1|1|Savings|1000.00|2024-01-15
2|1|Checking|500.00|2024-01-20
3|2|Savings|2000.00|2024-01-18
```

#### transactions.dat Format
```
transaction_id|account_id|type|amount|date|description
1|1|DEPOSIT|1000.00|2024-01-15|Initial deposit
2|1|WITHDRAWAL|100.00|2024-01-16|ATM withdrawal
3|2|DEPOSIT|500.00|2024-01-20|Account opening
```

**Advantages:**
- Human-readable
- Easy to debug
- Easy to implement
- Can edit with text editor

**Disadvantages:**
- Larger file size
- Slower for large datasets
- Requires parsing

### Binary Format (Alternative)

Stores structures directly as binary data. More efficient but less readable.

**Advantages:**
- Smaller file size
- Faster read/write
- Direct structure access

**Disadvantages:**
- Not human-readable
- Platform-dependent (endianness)
- More complex implementation

**Recommendation:** Start with text format for learning, can upgrade to binary later.

## Module Design

### 1. main.c
**Purpose:** Program entry point and main menu system

**Functions:**
- `main()` - Entry point, displays menu, handles user choice
- `display_main_menu()` - Shows main menu options
- `display_banking_menu()` - Shows banking menu (after login)

**Dependencies:** All other modules

### 2. auth.h / auth.c
**Purpose:** User authentication (registration and login)

**Functions:**
- `register_user()` - Register new user
- `login_user()` - Authenticate user login
- `validate_username()` - Check if username is unique
- `find_user_by_username()` - Search for user in file

**File Operations:**
- Read from `users.dat`
- Write to `users.dat`

### 3. account.h / account.c
**Purpose:** Account management

**Functions:**
- `create_account()` - Create new account for logged-in user
- `get_account_by_id()` - Retrieve account by ID
- `get_user_accounts()` - Get all accounts for a user
- `display_account()` - Display account information
- `generate_account_id()` - Generate unique account ID

**File Operations:**
- Read from `accounts.dat`
- Write to `accounts.dat`

### 4. transaction.h / transaction.c
**Purpose:** Transaction operations (deposit, withdrawal)

**Functions:**
- `deposit()` - Deposit money to account
- `withdraw()` - Withdraw money from account
- `validate_transaction()` - Validate transaction (sufficient balance, etc.)
- `update_account_balance()` - Update balance in accounts.dat
- `record_transaction()` - Save transaction to transactions.dat

**File Operations:**
- Read from `accounts.dat` (to get current balance)
- Update `accounts.dat` (to update balance)
- Append to `transactions.dat` (to log transaction)

### 5. statement.h / statement.c
**Purpose:** Generate account statements and transaction history

**Functions:**
- `get_transaction_history()` - Retrieve all transactions for an account
- `generate_statement()` - Generate formatted account statement
- `display_transactions()` - Display transaction list
- `calculate_summary()` - Calculate totals (deposits, withdrawals)

**File Operations:**
- Read from `transactions.dat`
- Read from `accounts.dat`

### 6. file_ops.h / file_ops.c
**Purpose:** Common file operation utilities

**Functions:**
- `file_exists()` - Check if file exists
- `create_file_if_not_exists()` - Create file if it doesn't exist
- `count_records()` - Count records in file
- `get_next_id()` - Get next available ID for auto-increment

**File Operations:**
- Generic file utilities used by all modules

### 7. utils.h / utils.c
**Purpose:** General utility functions

**Functions:**
- `clear_screen()` - Clear terminal screen
- `get_current_date()` - Get current date as string
- `trim_string()` - Remove whitespace from string
- `validate_input()` - Validate user input
- `pause_program()` - Wait for user to press enter

**Dependencies:** Standard library only

## System Flow

### Registration Flow
```
User selects "Register"
  → Prompt for username, password, name, email
  → Validate input
  → Check if username exists
  → If unique: Save to users.dat
  → If duplicate: Show error, retry
  → Confirm registration
```

### Login Flow
```
User selects "Login"
  → Prompt for username and password
  → Read users.dat
  → Search for username
  → Compare password
  → If match: Set logged_in_user, show banking menu
  → If no match: Show error, return to main menu
```

### Deposit Flow
```
User selects "Deposit"
  → Prompt for account ID and amount
  → Validate account exists and belongs to user
  → Read current balance from accounts.dat
  → Add amount to balance
  → Update accounts.dat
  → Record transaction in transactions.dat
  → Display confirmation and new balance
```

### Withdrawal Flow
```
User selects "Withdraw"
  → Prompt for account ID and amount
  → Validate account exists and belongs to user
  → Read current balance from accounts.dat
  → Check if balance >= withdrawal amount
  → If sufficient: Subtract amount, update accounts.dat
  → If insufficient: Show error
  → Record transaction in transactions.dat
  → Display confirmation and new balance
```

## Algorithms

### Finding User by Username
```
1. Open users.dat file
2. Read each line
3. Parse line to extract username field
4. Compare with search username
5. If match: Return user data
6. If end of file: Return "not found"
```

### Generating Unique ID
```
1. Open relevant data file (users.dat, accounts.dat, etc.)
2. Read all records
3. Find maximum ID value
4. Return (maximum ID + 1)
```

### Updating Account Balance
```
1. Read all accounts from accounts.dat into array
2. Find account with matching account_id
3. Update balance field
4. Write all accounts back to accounts.dat
```

### Retrieving Transaction History
```
1. Open transactions.dat file
2. Read each transaction
3. If transaction.account_id matches search account_id:
   - Add to result array
4. Continue until end of file
5. Return result array
```

## Error Handling Strategy

### Input Validation
- Check data types (integer, float, string)
- Check ranges (positive amounts, valid IDs)
- Check formats (date format, email format)

### File Operations
- Check if file exists before reading
- Create file if it doesn't exist (first run)
- Handle file open errors
- Handle file read/write errors

### Business Logic
- Verify user owns account before operations
- Verify sufficient balance before withdrawal
- Verify account exists before transactions

### Error Messages
- Clear, user-friendly messages
- Suggest corrective action
- Don't expose technical details

## Security Considerations (Basic)

**Note:** This is a learning project. Real banking systems require much stronger security.

- Passwords stored in plain text (for simplicity)
- No encryption
- No session management
- Single-user system

**For Production:** Would need encryption, hashed passwords, secure sessions, etc.

## Performance Considerations

- File-based system is acceptable for small datasets (< 1000 records)
- Linear search is acceptable for learning
- No indexing needed for small scale
- All data loaded into memory for operations (simple approach)

## Testing Strategy

1. **Unit Testing:** Test each function individually
2. **Integration Testing:** Test modules working together
3. **System Testing:** Test complete user workflows
4. **Error Testing:** Test error handling and edge cases

---

**Design Status:** Approved  
**Implementation Start:** Chapter 3

