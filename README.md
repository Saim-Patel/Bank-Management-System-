#  – Bank Management System

**Level:** Intermediate  
**Language:** C  
**Concepts:** Structures, Functions, File Handling

## Features
- Create a bank account with a unique account number.
- Deposit and withdraw in the demonstration system.
- Check an account balance.
- Display all saved accounts.
- Save account records in `accounts.dat`, so they remain after closing the program.

## Compile and run
```bash
gcc main.c -o bank
./bank
```
On Windows:
```bash
gcc main.c -o bank.exe
bank.exe
```

## Important
This is a beginner college demonstration, not real banking software. It has no authentication, encryption, audit trail or banking integration. Do not enter real personal or financial information. The `accounts.dat` file is created automatically in the program's working folder.
