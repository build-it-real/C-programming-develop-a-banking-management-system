# Banking Management System - Requirements Document

## Project Overview

**Project Name:** Banking Management System  
**Version:** 1.0  
**Date:** [Current Date]  
**Language:** C Programming Language  
**Storage:** File-based (no database)

## Purpose

This document specifies the functional and non-functional requirements for the Banking Management System. This system allows users to manage bank accounts, perform transactions, and view account information using a file-based storage system.

## Functional Requirements

### FR1: User Management

#### FR1.1: User Registration
- **Description:** System shall allow new users to register
- **Input:** 
  - Username (string, max 50 characters)
  - Password (string, min 6 characters)
  - Full Name (string, max 100 characters)
  - Email (string, max 100 characters)
- **Validation:**
  - Username must be unique (not already exists)
  - Password must be at least 6 characters
  - Email format validation (basic)
- **Output:** User account created, confirmation message
- **Storage:** User data saved to `users.dat` file

#### FR1.2: User Login
- **Description:** System shall allow registered users to login
- **Input:**
  - Username (string)
  - Password (string)
- **Validation:**
  - Username must exist in system
  - Password must match stored password
- **Output:** 
  - If valid: Access granted, show banking menu
  - If invalid: Error message, return to main menu
- **Storage:** Read from `users.dat` file

### FR2: Account Management

#### FR2.1: Create Account
- **Description:** System shall allow logged-in users to create bank accounts
- **Input:**
  - Account Type (string: "Savings" or "Checking")
  - Initial Balance (float, must be >= 0)
- **Processing:**
  - System generates unique account ID
  - System links account to logged-in user
  - System records creation date
- **Output:** Account created, display account ID
- **Storage:** Account data saved to `accounts.dat` file

#### FR2.2: View Account Information
- **Description:** System shall allow users to view their account details
- **Input:** Account ID (optional - if not provided, show all user's accounts)
- **Output:** Display:
  - Account ID
  - Account Type
  - Current Balance
  - Creation Date
- **Storage:** Read from `accounts.dat` file

### FR3: Transaction Operations

#### FR3.1: Deposit Money
- **Description:** System shall allow users to deposit money into their accounts
- **Input:**
  - Account ID (integer)
  - Deposit Amount (float, must be > 0)
  - Description (optional string)
- **Processing:**
  - Verify account exists and belongs to logged-in user
  - Add amount to account balance
  - Record transaction
- **Output:** Deposit successful, new balance displayed
- **Storage:** 
  - Update `accounts.dat` (balance)
  - Append to `transactions.dat`

#### FR3.2: Withdraw Money
- **Description:** System shall allow users to withdraw money from their accounts
- **Input:**
  - Account ID (integer)
  - Withdrawal Amount (float, must be > 0)
  - Description (optional string)
- **Processing:**
  - Verify account exists and belongs to logged-in user
  - Verify sufficient balance (balance >= withdrawal amount)
  - Subtract amount from account balance
  - Record transaction
- **Output:** 
  - If successful: Withdrawal successful, new balance displayed
  - If insufficient funds: Error message
- **Storage:**
  - Update `accounts.dat` (balance)
  - Append to `transactions.dat`

### FR4: Transaction History

#### FR4.1: View Transaction History
- **Description:** System shall display transaction history for an account
- **Input:** Account ID (integer)
- **Processing:**
  - Verify account exists and belongs to logged-in user
  - Retrieve all transactions for the account
  - Sort by date (newest first)
- **Output:** Display list of transactions:
  - Transaction ID
  - Date
  - Type (DEPOSIT/WITHDRAWAL)
  - Amount
  - Description
- **Storage:** Read from `transactions.dat` file

### FR5: Account Statements

#### FR5.1: Generate Account Statement
- **Description:** System shall generate a formatted account statement
- **Input:** Account ID (integer)
- **Processing:**
  - Retrieve account information
  - Retrieve all transactions for the account
  - Format statement
- **Output:** Formatted statement showing:
  - Account Information (ID, Type, Balance)
  - Transaction History
  - Summary (Total Deposits, Total Withdrawals, Current Balance)
- **Storage:** Read from `accounts.dat` and `transactions.dat`

## Non-Functional Requirements

### NFR1: Data Persistence
- **Description:** All data must persist between program sessions
- **Implementation:** Use file-based storage (text or binary files)
- **Files:**
  - `users.dat` - User data
  - `accounts.dat` - Account data
  - `transactions.dat` - Transaction history

### NFR2: Error Handling
- **Description:** System must handle common error cases gracefully
- **Error Cases:**
  - Invalid user input (non-numeric where number expected)
  - File access errors (file not found, permission denied)
  - Invalid account ID
  - Insufficient balance for withdrawal
  - Duplicate username during registration
- **Behavior:** Display clear error messages, do not crash

### NFR3: User Interface
- **Description:** System shall have a simple text-based menu interface
- **Features:**
  - Clear menu options
  - User-friendly prompts
  - Formatted output (tables, alignment)
  - Clear error messages

### NFR4: Code Organization
- **Description:** Code must be organized into logical modules
- **Structure:**
  - Separate source files for different features
  - Header files for function declarations
  - Utility functions in separate modules
  - Main program in main.c

### NFR5: Performance
- **Description:** System should respond to user actions within reasonable time
- **Note:** For file-based system with small datasets, performance is acceptable if operations complete within 1-2 seconds

## Constraints

1. **Technology:** Must use only C programming language
2. **Storage:** File-based only (no database systems)
3. **Platform:** Should work on Windows, Linux, and Mac
4. **Dependencies:** Standard C library only (no external libraries)

## Assumptions

1. Single-user system (one user logged in at a time)
2. Data files are stored locally
3. No concurrent access (one instance of program running)
4. File system is reliable
5. User has read/write permissions to data directory

## Future Enhancements (Out of Scope)

- Multi-user concurrent access
- Database integration
- Network/remote access
- Graphical user interface
- Interest calculations
- Account transfers between users
- Password encryption
- Transaction limits

## Acceptance Criteria

The system is considered complete when:
1. All functional requirements (FR1-FR5) are implemented
2. All non-functional requirements (NFR1-NFR5) are met
3. System handles all specified error cases
4. Code is organized into modules
5. Documentation is complete

---

**Document Status:** Approved  
**Next Review:** After implementation completion

