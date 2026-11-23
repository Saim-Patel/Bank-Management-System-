#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "accounts.dat"

struct Account {
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount(void)
{
    struct Account a, temp;
    FILE *fp = fopen(FILE_NAME, "ab+");

    if (fp == NULL) {
        printf("Unable to open account file.\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &a.accountNumber);

    rewind(fp);
    while (fread(&temp, sizeof(temp), 1, fp) == 1) {
        if (temp.accountNumber == a.accountNumber) {
            printf("That account number already exists.\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter account holder name: ");
    scanf(" %49[^\n]", a.name);
    printf("Enter opening balance: Rs. ");
    scanf("%f", &a.balance);

    if (a.accountNumber <= 0 || a.balance < 0) {
        printf("Invalid account number or opening balance.\n");
    } else if (fwrite(&a, sizeof(a), 1, fp) == 1) {
        printf("Account created successfully.\n");
    } else {
        printf("Could not save account.\n");
    }

    fclose(fp);
}

void showAccounts(void)
{
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("No accounts found yet.\n");
        return;
    }

    printf("\n-------- ACCOUNT LIST --------\n");
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        printf("Account: %d | Name: %s | Balance: Rs. %.2f\n",
               a.accountNumber, a.name, a.balance);
    }
    fclose(fp);
}

void updateBalance(int accountNumber, float amount, int isDeposit)
{
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("No account file found. Create an account first.\n");
        return;
    }

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accountNumber == accountNumber) {
            if (!isDeposit && amount > a.balance) {
                printf("Insufficient balance.\n");
            } else {
                if (isDeposit)
                    a.balance += amount;
                else
                    a.balance -= amount;

                fseek(fp, -(long)sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);
                printf("Transaction successful. New balance: Rs. %.2f\n",
                       a.balance);
            }
            fclose(fp);
            return;
        }
    }

    printf("Account not found.\n");
    fclose(fp);
}

void checkBalance(int accountNumber)
{
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("No account file found.\n");
        return;
    }

    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accountNumber == accountNumber) {
            printf("Account holder: %s\n", a.name);
            printf("Current balance: Rs. %.2f\n", a.balance);
            fclose(fp);
            return;
        }
    }

    printf("Account not found.\n");
    fclose(fp);
}

int main(void)
{
    int choice, accountNumber;
    float amount;

    do {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create account\n");
        printf("2. Deposit money\n");
        printf("3. Withdraw money\n");
        printf("4. Check balance\n");
        printf("5. Display all accounts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Restart the program.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter deposit amount: Rs. ");
                scanf("%f", &amount);
                if (amount <= 0)
                    printf("Enter an amount greater than zero.\n");
                else
                    updateBalance(accountNumber, amount, 1);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter withdrawal amount: Rs. ");
                scanf("%f", &amount);
                if (amount <= 0)
                    printf("Enter an amount greater than zero.\n");
                else
                    updateBalance(accountNumber, amount, 0);
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                checkBalance(accountNumber);
                break;
            case 5:
                showAccounts();
                break;
            case 0:
                printf("Thank you for using the demo system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
