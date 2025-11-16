# Banking Management System - User Guide

## Getting Started

### Prerequisites
- C compiler (GCC) installed
- Make utility (optional, for using Makefile)

### Compilation

**Using Makefile (Recommended):**
```bash
make
```

**Manual Compilation:**
```bash
gcc -Wall -Wextra -std=c11 -o banking_system src/main.c src/auth.c src/account.c src/transaction.c src/statement.c src/utils.c
```

### Running the Program

```bash
./banking_system        # Linux/Mac
banking_system.exe      # Windows
```

Or using Makefile:
```bash
make run
```

## Features

### 1. User Registration

- **Access:** Main Menu → Option 1
- **Requirements:**
  - Username (must be unique)
  - Password (minimum 6 characters)
  - Full Name
  - Email Address
- **Note:** Username must be unique. If username exists, registration will fail.

### 2. User Login

- **Access:** Main Menu → Option 2
- **Requirements:**
  - Username (must be registered)
  - Password (must match)
- **After Login:** You'll see the Banking Menu with account management options.

### 3. Account Management

#### Create Account
- **Access:** Banking Menu → Option 1
- **Steps:**
  1. Select account type (Savings or Checking)
  2. Enter initial balance (must be positive or zero)
- **Result:** Account is created with unique Account ID

#### View Accounts
- **Access:** Banking Menu → Option 2
- **Displays:** All your accounts with:
  - Account ID
  - Account Type
  - Current Balance
  - Creation Date

### 4. Transactions

#### Deposit Money
- **Access:** Banking Menu → Option 3
- **Steps:**
  1. Enter Account ID
  2. Enter deposit amount (must be positive)
  3. Enter description (optional)
- **Result:** Balance increases, transaction is logged

#### Withdraw Money
- **Access:** Banking Menu → Option 4
- **Steps:**
  1. Enter Account ID
  2. Enter withdrawal amount (must be positive)
  3. Enter description (optional)
- **Requirements:**
  - Account must have sufficient balance
  - Withdrawal amount cannot exceed current balance
- **Result:** Balance decreases, transaction is logged

### 5. Account Statements

- **Access:** Banking Menu → Option 5
- **Steps:**
  1. Enter Account ID
- **Displays:**
  - Account Information
  - Complete Transaction History
  - Summary Statistics:
    - Total Deposits
    - Total Withdrawals
    - Net Change
    - Current Balance

### 6. Logout

- **Access:** Banking Menu → Option 6
- **Result:** Returns to Main Menu, ends your session

## Data Storage

All data is stored in the `data/` directory:

- **users.dat** - User account information
- **accounts.dat** - Bank account information
- **transactions.dat** - Transaction history

**Important:** 
- Do not manually edit these files while the program is running
- Data persists between program sessions
- Create the `data/` directory if it doesn't exist

## Error Messages

### Common Errors

**"Username already exists"**
- Solution: Choose a different username

**"Invalid password"**
- Solution: Check password spelling, ensure it matches registration

**"Account not found"**
- Solution: Verify Account ID is correct and belongs to you

**"Insufficient balance"**
- Solution: Check current balance, withdraw less or deposit more

**"Invalid choice"**
- Solution: Enter a number corresponding to a menu option

## Tips

1. **Remember Your Account IDs** - You'll need them for transactions and statements
2. **Use Descriptions** - Helpful for tracking transaction purposes
3. **Check Statements Regularly** - Verify all transactions are correct
4. **Keep Data Files Safe** - They contain all your account information

## Troubleshooting

### Program Won't Compile
- Check GCC is installed: `gcc --version`
- Verify all source files are present
- Check for syntax errors in code

### Program Crashes
- Ensure `data/` directory exists
- Check file permissions
- Verify input format (numbers where expected)

### Data Not Saving
- Check `data/` directory exists and is writable
- Verify program has write permissions
- Check disk space

## Support

For issues or questions:
1. Check this user guide
2. Review error messages carefully
3. Verify all inputs are in correct format
4. Check that data directory exists and is accessible

---

**Version:** 1.0  
**Last Updated:** [Current Date]
