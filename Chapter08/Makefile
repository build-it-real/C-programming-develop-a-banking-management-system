# Makefile for Banking Management System

# Compiler

CC = gcc

# Compiler flags

CFLAGS = -Wall -Wextra -std=c11

# Target executable

TARGET = banking_system

# Source files

SRC = src/main.c src/auth.c src/account.c src/transaction.c src/statement.c src/utils.c

# Default target

all: $(TARGET)

# Buld the executable

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean build files
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the program
run: $(TARGET)
	./$(TARGET)

help:
	@echo "Available targets:"
	@echo "   make           - Build the program"
	@echo "   make run       - Buld and run the prorga"
	@echo "   make clean - Remove buuld files"
	