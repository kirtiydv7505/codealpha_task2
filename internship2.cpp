#include <stdio.h>
#include <stdlib.h>

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main()
{
    int choice;

    while (1)
    {
        printf("\n========== BANKING SYSTEM ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            deposit();
            break;

        case 3:
            withdraw();
            break;

        case 4:
            balanceEnquiry();
            break;

        case 5:
            printf("Thank you for using the Banking System!\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}


void createAccount()
{
    struct Account a;

    FILE *fp = fopen("bank.dat", "ab");

    if (fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accountNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);

    fclose(fp);

    printf("Account created successfully!\n");
}



void deposit()
{
    struct Account a;
    int accountNumber;
    float amount;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accountNumber == accountNumber)
        {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            a.balance = a.balance + amount;

            fseek(fp, -sizeof(a), SEEK_CUR);

            fwrite(&a, sizeof(a), 1, fp);

            found = 1;

            printf("Amount deposited successfully!\n");
            printf("New Balance: %.2f\n", a.balance);

            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}



void withdraw()
{
    struct Account a;
    int accountNumber;
    float amount;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accountNumber == accountNumber)
        {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > a.balance)
            {
                printf("Insufficient balance!\n");
            }
            else
            {
                a.balance = a.balance - amount;

                fseek(fp, -sizeof(a), SEEK_CUR);

                fwrite(&a, sizeof(a), 1, fp);

                printf("Withdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", a.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}


/* BALANCE ENQUIRY */
void balanceEnquiry()
{
    struct Account a;
    int accountNumber;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("No accounts found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accountNumber == accountNumber)
        {
            printf("\n========== ACCOUNT DETAILS ==========\n");
            printf("Account Number: %d\n", a.accountNumber);
            printf("Name: %s\n", a.name);
            printf("Balance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}
