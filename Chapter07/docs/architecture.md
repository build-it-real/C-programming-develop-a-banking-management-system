# Banking Management System - Architecture Document

## System Architecture Overview

The Banking Management System follows a **layered architecture** with clear separation of concerns. The system is organized into modules that interact through well-defined interfaces.

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────┐
│                    Presentation Layer                    │
│  ┌───────────────────────────────────────────────────┐  │
│  │           Main Menu System (main.c)               │  │
│  │  - Display menus                                  │  │
│  │  - Handle user input                              │  │
│  │  - Route to appropriate modules                   │  │
│  └───────────────────────────────────────────────────┘  │
└───────────────────────┬─────────────────────────────────┘
                        │
        ┌───────────────┼───────────────┐
        │               │               │
┌───────▼──────┐ ┌──────▼──────┐ ┌──────▼──────────┐
│  Business    │ │  Business    │ │   Business      │
│  Logic       │ │  Logic       │ │   Logic         │
│  Layer       │ │  Layer       │ │   Layer         │
├──────────────┤ ├──────────────┤ ├─────────────────┤
│ auth.c       │ │ account.c    │ │ transaction.c   │
│ - Register   │ │ - Create     │ │ - Deposit       │
│ - Login      │ │ - View       │ │ - Withdraw      │
│              │ │ - Manage     │ │                 │
└───────┬──────┘ └──────┬───────┘ └──────┬──────────┘
        │               │                │
        └───────────────┼────────────────┘
                        │
                ┌───────▼────────┐
                │  Business       │
                │  Logic          │
                ├─────────────────┤
                │ statement.c     │
                │ - History       │
                │ - Statements    │
                └───────┬─────────┘
                        │
        ┌───────────────┼───────────────┐
        │               │               │
┌───────▼──────┐ ┌──────▼──────┐ ┌──────▼──────┐
│   Utility    │ │   Utility    │ │   Utility   │
│   Layer      │ │   Layer      │ │   Layer     │
├──────────────┤ ├──────────────┤ ├─────────────┤
│ file_ops.c   │ │ utils.c      │ │ (Standard   │
│ - File       │ │ - Screen     │ │  Library)   │
│   utilities  │ │ - Date       │ │             │
│              │ │ - Input      │ │             │
└───────┬──────┘ └──────────────┘ └─────────────┘
        │
        │
┌───────▼───────────────────────────────────────┐
│            Data Access Layer                  │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │users.dat │  │accounts. │  │transact. │   │
│  │          │  │  dat     │  │  .dat    │   │
│  └──────────┘  └──────────┘  └──────────┘   │
└───────────────────────────────────────────────┘
```

## Layer Descriptions

### 1. Presentation Layer

**Component:** `main.c`

**Responsibilities:**
- User interface (text-based menus)
- User input handling
- Navigation between features
- Display output to user

**Characteristics:**
- No business logic
- Delegates all operations to business logic layer
- Handles user interaction only

### 2. Business Logic Layer

**Components:**
- `auth.c` - Authentication logic
- `account.c` - Account management logic
- `transaction.c` - Transaction processing logic
- `statement.c` - Statement generation logic

**Responsibilities:**
- Implement business rules
- Validate data
- Process operations
- Coordinate with data access

**Characteristics:**
- Contains core application logic
- Independent of user interface
- Uses utility layer for common operations

### 3. Utility Layer

**Components:**
- `file_ops.c` - File operation utilities
- `utils.c` - General utilities

**Responsibilities:**
- Provide reusable functions
- Handle common operations
- Abstract file operations
- Provide helper functions

**Characteristics:**
- No business logic
- Reusable across modules
- Low-level operations

### 4. Data Access Layer

**Components:**
- File system (users.dat, accounts.dat, transactions.dat)

**Responsibilities:**
- Persistent data storage
- Data retrieval
- Data updates

**Characteristics:**
- Simple file-based storage
- No database abstraction
- Direct file I/O

## Module Interactions

### Authentication Flow
```
main.c
  → calls auth.c::login_user()
    → calls file_ops.c::read_users()
      → reads users.dat
    → validates credentials
  → returns to main.c with result
```

### Deposit Flow
```
main.c
  → calls transaction.c::deposit()
    → calls account.c::get_account_by_id()
      → calls file_ops.c::read_accounts()
        → reads accounts.dat
    → validates transaction
    → calls file_ops.c::update_account()
      → updates accounts.dat
    → calls file_ops.c::append_transaction()
      → appends to transactions.dat
  → returns to main.c with result
```

## Data Flow

### Reading Data
```
User Request
  → Business Logic Module
    → File Operations Module
      → Open File
      → Read Data
      → Parse Data
      → Return to Business Logic
    → Process Data
    → Return to Presentation
  → Display to User
```

### Writing Data
```
User Input
  → Presentation Layer
    → Business Logic Module
      → Validate Data
      → File Operations Module
        → Open File
        → Format Data
        → Write to File
        → Return Status
      → Return Result
    → Display Confirmation
```

## Component Dependencies

```
main.c
  ├── depends on: auth.h
  ├── depends on: account.h
  ├── depends on: transaction.h
  ├── depends on: statement.h
  └── depends on: utils.h

auth.c
  ├── depends on: file_ops.h
  └── depends on: utils.h

account.c
  ├── depends on: file_ops.h
  └── depends on: utils.h

transaction.c
  ├── depends on: account.h
  ├── depends on: file_ops.h
  └── depends on: utils.h

statement.c
  ├── depends on: file_ops.h
  └── depends on: utils.h

file_ops.c
  └── depends on: utils.h (minimal)
```

## State Management

### Global State
- `current_user_id` - ID of logged-in user (set after login, cleared on logout)
- `logged_in` - Boolean flag indicating login status

### Session State
- User remains logged in until:
  - User explicitly logs out
  - Program terminates
  - New user logs in (replaces current user)

### Data State
- All data persisted in files
- No in-memory caching (simple approach)
- Data read from files when needed
- Data written to files immediately after changes

## Error Handling Architecture

### Error Propagation
```
File Operation Error
  → Returns error code to Business Logic
    → Business Logic handles/validates
      → Returns error message to Presentation
        → Presentation displays to user
```

### Error Types
1. **File Errors:** File not found, permission denied, read/write failures
2. **Input Errors:** Invalid format, out of range, missing required fields
3. **Business Logic Errors:** Insufficient balance, account not found, invalid operation
4. **System Errors:** Memory issues, unexpected failures

## Scalability Considerations

### Current Design (Learning Project)
- Suitable for: < 1000 users, < 5000 accounts, < 10000 transactions
- File-based storage
- Linear search algorithms
- All data in memory during operations

### Future Enhancements (If Needed)
- Database integration (SQLite, MySQL)
- Indexing for faster searches
- Caching for frequently accessed data
- Pagination for large result sets
- Binary file format for efficiency

## Security Architecture (Basic)

### Current Implementation
- Plain text password storage (for learning)
- No encryption
- File-based access control (OS level)
- Single-user system

### Security Layers (If Enhanced)
1. **Authentication:** Password hashing, session tokens
2. **Authorization:** Role-based access, permission checks
3. **Data Protection:** Encryption at rest, secure file permissions
4. **Input Validation:** Sanitization, injection prevention

## Build Architecture

### Compilation Structure
```
Source Files (*.c)
  → Compiled to Object Files (*.o)
    → Linked into Executable
      → banking_system.exe (or banking_system)
```

### Makefile Structure
```
Targets:
  - all: Build executable
  - clean: Remove object files and executable
  - run: Build and run program
  - debug: Build with debug symbols
```

## Deployment Architecture

### File Structure
```
banking_system/
├── banking_system.exe (executable)
├── src/ (source files - optional for distribution)
├── data/ (data files - created at runtime)
│   ├── users.dat
│   ├── accounts.dat
│   └── transactions.dat
└── README.md (user documentation)
```

### Runtime Requirements
- C runtime library
- File system read/write permissions
- Terminal/console for text interface

## Architecture Principles Applied

1. **Separation of Concerns:** Each module has single responsibility
2. **Modularity:** Code organized into logical modules
3. **Layered Architecture:** Clear layers with defined interfaces
4. **Simplicity:** Straightforward design for learning
5. **Maintainability:** Easy to understand and modify

---

**Architecture Status:** Approved  
**Implementation:** Follows this architecture starting Chapter 3

