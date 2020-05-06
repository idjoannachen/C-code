#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INTEREST_RATE 0.5
#define OVERDRAFT_CHARGE 30

typedef struct
{
    int id;
    char owner[30];
    double balance;
}Account;

typedef struct
{
    int month;
    int day;
    int year;
}Date;

typedef struct
{
    Account array[30];
    int length;
    int count;
}AccountArray;

typedef struct
{
    int id;
    int account_id;
    int date;
    char type;
    double amount;
}Transaction;

typedef struct
{
    Transaction array [30];
    int length;
    int count;
}TransactionArray;

//Define the function prototype
//General function
int display_menu();
int compare_dates(Date a, Date b);
void print_date(Date date, char s[]);
double round_dbl(double d, int i);

//Function operating on Accounts
void print_account(Account acct);

//Functions operating on AccountArrays
void print_array_account(AccountArray acctArr);
void read_accounts(char file_name[], AccountArray *acctArr);
void sort_accounts(AccountArray *acctArr);
void swap_accounts(AccountArray *acctArr,int i, int j);
void insert_account(AccountArray *acctArr, int id, char owner[], double balance);
void save_accounts(AccountArray acctArr, char fileName[]);
int search_account_owner(AccountArray acctArr,char owner[]);
int search_account_id(AccountArray acctArr, int id);

// Functions operating on Transactions
void print_transaction(Transaction trans);
int compare_transactions(Transaction a, Transaction b);

// Functions operating on TransactionArrays
void read_transactions(char file_name[], TransactionArray *transArr);
void insert_transaction(TransactionArray *transArr,int id, int account, int month, int day, int year, char type, double amount);
void print_transaction_array(TransactionArray transArr);
int find_first_transaction(TransactionArray transArr, int acctNo);
void sort_transactions(TransactionArray *transArr);
void sort_transactions_id(TransactionArray *transArr);
void swap_transactions(TransactionArray *transArr, int i, int j);
void save_transactions(TransactionArray transArr, char fileName[]);

// Functions operating on TransactionArrays and AccountArrays
void reconcile(AccountArray *acctArr, TransactionArray *transArr);
void print_account_id(AccountArray acctArr, TransactionArray transArr, int acctNo);
void print_account_owner(AccountArray acctArr, TransactionArray transArr, char owner[]);
void print_account_transactions(AccountArray acctArr, TransactionArray transArr, int acctIdx);
void print_summary_report(AccountArray acctArr, TransactionArray transArr);
void print_detail_report(AccountArray acctArr, TransactionArray transArr);


int main(){
    Account acct;
    AccountArray acctArr;
    Transaction trans;
    TransactionArray transArr;
    acctArr.count = 0;
    acctArr.length  = 30;
    transArr.count = 0;
    transArr.length = 30;
    
    
    int acctNo;
    int acctIdx;
    int choice = 0;
    int id;
    char owner[30];
    
    //Display menu and case
    do{
        choice  = display_menu();
        switch(choice){
            case 1:
                read_accounts("accounts.txt", &acctArr);
                read_transactions("trans.txt", &transArr);
                sort_accounts(&acctArr);
                sort_transactions(&transArr);
                break;
                
            case 2:
                reconcile(&acctArr, &transArr);
                break;
                
            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);
                search_account_id(acctArr, id);
                print_account_id(acctArr, transArr, id);
                break;
                
            case 4:
                printf("Enter the Owner: ");
                scanf("%s", &owner);
                search_account_owner(acctArr, owner);
                print_account_owner(acctArr, transArr, owner);
                break;
                
            case 5:
                printf("Account summary report");
                print_summary_report(acctArr, transArr);
                break;
                
            case 6:
                printf("Account detail report");
                print_detail_report(acctArr, transArr);
                break;
                
            case 7:
                print_array_account(acctArr);
                break;
                
            case 8:
                print_transaction_array(transArr);
                break;
                
            case 9:
                save_accounts(acctArr, "accounts1.txt");
                save_transactions(transArr, "trans1.txt");
                break;
                
            case 10:
                break;
        }
    }while(choice!=10);
    
    return 0;
}


//Display the menu
int display_menu(){
    int number;
    printf("1-Read and sort account and transaction files\n");
    printf("2-Reconcile accounts\n");
    printf("3-Find account by ID-Binary Search-List Transactions\n");
    printf("4-Find account by owner-Selection Search-List Transactions\n");
    printf("5-Print account summary report\n");
    printf("6-Print account detail report\n");
    printf("7-Print all accounts\n");
    printf("8-Print all transactions\n");
    printf("9-Save account and transactions to file\n");
    printf("10-Exit\n");
    printf("Enter a choice: \n");
    scanf("%d", &number);
    return number;
}


//Display the date
void print_date(Date date, char s[]){
    sprintf(s, "%d/%d/%d", date.month, date.day, date.year);
}

//Compare the date
int compare_dates(Date a, Date b){
    if(a.year < b.year)
        return -1;
    else if(a.year > b.year)
        return 1;
    else{
        if(a.month < b.month)
            return -1;
        else if(a.month > b.month)
            return 1;
        else{
            if(a.day < b.day)
                return -1;
            else if(a.day > b.day)
                return 1;
            else
                return 0;
        }
    }
}


double round_dbl(double d, int i)
{
    int n = (int)(d * pow(10, i + 1));
    n += 5;
    n /= 10;
    d = (double)n;
    d /= pow(10, i);
    return d;
}

void print_account(Account acct)
{
    printf("ID: %d\n", acct.id);
    printf("Owner: %s\n", acct.owner);
    printf("Balance: %1.2f\n", acct.balance);
}

void print_array_account(AccountArray acctArr)
{
    int i;
    for (i = 0; i<acctArr.count; i++){
        print_account(acctArr.array[i]);
        printf("\n");
    }
}

//Copy the id, owner, balance and increment count
void insert_account(AccountArray *acctArr, int id, char owner[], double balance)
{
    (*acctArr).array[(*acctArr).count].id = id;
    strcpy((*acctArr).array[(*acctArr).count].owner, owner);
    (*acctArr).array[(*acctArr).count].balance = balance;
    (*acctArr).count++;
}

//Open the file and read the account
void read_accounts(char file_name[], AccountArray *acctArr)
{
    int id;
    char a[200];
    char owner[30];
    double balance;
    printf("\nReading file %s\n", file_name);
    FILE *in_file = fopen(file_name, "r");
    if(in_file != NULL)
    {
        while(fgets(a, 200, in_file) != NULL)
        {
            id = atoi(strtok(a, ","));
            strcpy(owner, strtok(NULL, ","));
            balance = atof(strtok(NULL, ","));
            insert_account(acctArr, id, owner, balance);
        }
        fclose(in_file);
    }
    else
        printf("ERROR: File not open...\n");
}

void swap_accounts(AccountArray *acctArr, int i, int j)
{
    Account temp = (*acctArr).array[i];
    (*acctArr).array[i] = (*acctArr).array[j];
    (*acctArr).array[j] = temp;
}

void sort_accounts(AccountArray *acctArr)
{
    int i, j;
    for (i = 0;i < acctArr->count - 1; i++){
        for (j = acctArr->count - 1; j > i; j--){
            if ((*acctArr).array[j].id < (*acctArr).array[j-1].id){
                swap_accounts(acctArr, j, j-1);
            }
        }
    }
}

//Search the account id to find the array index
int search_account_id(AccountArray acctArr, int id)
{
    int begin = 0;
    int end = acctArr.count - 1;
    int mid;
    while (begin <= end){
        mid = (end + begin)/2;
        if (id > acctArr.array[mid].id){
        	return begin = (mid + 1);
        }
        else if (id == acctArr.array[mid].id){
        	return mid;
        }
        else{
        	return end = (mid - 1);
        }
    }
}

int search_account_owner(AccountArray acctArr, char owner[])
{
    int i;
    for(i = 0; i < acctArr.count; i++)
        if(strcmp(acctArr.array[i].owner, owner) == 0)
            return i;
    return -1;
}


//Save account
void save_accounts(AccountArray acctArr, char fileName[])
{
    printf("\nWriting file %s ...\n", fileName);
    FILE *out_file = fopen(fileName, "w");
    int i;
    if(out_file != NULL){
        for(i = 0; i < acctArr.count; i++)
            fprintf(out_file, "%d,%s,%1.2f\n", acctArr.array[i].id, acctArr.array[i].owner, acctArr.array[i].balance);
        fclose(out_file);
    }
}

//Print the transaction information
void print_transaction(Transaction trans)
{
    char date[20];
    print_date(trans.date, date);
    printf("ID: %d\n", trans.id);
    printf("Account: %d\n", trans.account_id);
    printf("Date: %s\n", date);
    printf("Type: %c\n", trans.type);
    printf("Amount: %1.2f\n", trans.amount);
}

//Compare the transaction
int compare_transactions(Transaction a, Transaction b)
{
    if(a.account_id < b.account_id)
        return -1;
    else if(a.account_id > b.account_id)
        return 1;
    else
        return compare_dates(a.date, b.date);
}

void print_transaction_array(TransactionArray transArr)
{
    int i;
    for (i = 0;i < transArr.count; i++){
        print_transaction(transArr.array[i]);
        printf("\n");
    }
}

//Insert the transaction array
void insert_transaction(TransactionArray *transArr, int id, int account_id, int month, int day, int year, char type, double amount)
{
    (*transArr).array[(*transArr).count].id = id;                          // Copy id
    (*transArr).array[(*transArr).count].account_id = account_id;          // Copy account_id
    (*transArr).array[(*transArr).count].date.day = day;                   // Copy date
    (*transArr).array[(*transArr).count].date.month = month;
    (*transArr).array[(*transArr).count].date.year = year;
    (*transArr).array[(*transArr).count].type = type;                      // Copy type
    (*transArr).array[(*transArr).count].amount = amount;                  // Copy amount
    (*transArr).count++;                                                   // Increment count
}


//Read the transaction information
void read_transactions(char file_name[], TransactionArray *transArr)
{
    int id;
    int account;
    char date[30];
    int day;
    int month;
    int year;
    char type[3];
    char a[200];
    double amount;
    printf("\nReading file %s...\n", file_name);
    FILE *in_file = fopen(file_name, "r");
    if(in_file != NULL){
        while(fgets(a, 200, in_file) != NULL){
            a[strlen(a)-1] = '\0';
            id = atoi(strtok(a, ","));
            account = atoi(strtok(NULL, ","));
            strcpy(date, strtok(NULL, ","));
            strcpy(type, strtok(NULL, ","));
            amount = atof(strtok(NULL, ","));
            month = atoi(strtok(date, "/"));
            day = atoi(strtok(NULL, "/"));
            year = atoi(strtok(NULL, "/"));
            insert_transaction(transArr, id, account, month, day, year, type[0], amount);
        }
        fclose(in_file);
    }
}


//Swap the transaction
void swap_transactions(TransactionArray *transArr, int i, int j)
{
    Transaction temp = (*transArr).array[i];
    (*transArr).array[i] = (*transArr).array[j];
    (*transArr).array[j] = temp;
}


//Transaction sort
void sort_transactions(TransactionArray *transArr)
{
    int i, j;
    printf("count = %d\n", (*transArr).count);
    for (i = 0;i < (*transArr).count - 1; i++)
    {
        for (j = (*transArr).count - 1; j > i; j--)
        {
            if (compare_transactions((*transArr).array[j], (*transArr).array[j-1]) < 0)
            {
                swap_transactions(transArr, j, j-1);
            }
        }
    }
}

//Find the first transaction
int find_first_transaction(TransactionArray transArr, int acctNo)
{
    int i;
    char owner[30];
    for(i = 0; i < transArr.count; i++)
        if(transArr.array[i].account_id == acctNo)
            return i;
    return -1;
}

//Sort transaction id
void sort_transactions_id(TransactionArray *transArr)
{
    int i, j, temp;
    for (i = 0;i < (*transArr).count - 1; i++)
    {
        for (j = (*transArr).count - 1; j > i; j--)
        {
            if ((*transArr).array[j - 1].id > (*transArr).array[j].id)
            {
                swap_transactions(transArr, j, j-1);
            }
        }
    }
}

//Save transactions
void save_transactions(TransactionArray transArr, char fileName[])
{
    printf("\nWriting file %s...\n", fileName);
    FILE *out_file = fopen(fileName, "w");
    int i;
    if(out_file != NULL)
    {
        for(i = 0; i < transArr.count; i++)
            fprintf(out_file, "%d,%d,%d/%d/%d,%c,%1.2f\n", transArr.array[i].id, transArr.array[i].account_id, transArr.array[i].date.month, transArr.array[i].date.day, transArr.array[i].date.year, transArr.array[i].type, transArr.array[i].amount);
        fclose(out_file);
    }
}

// Reconcile accounts
void reconcile(AccountArray *acctArr, TransactionArray *transArr)
{
    int acctIdx=0, transIdx=0, count=0;
    double balance = 0.0;
    double interest = 0.0;
    char date[30];
    
    //Get date from user
    printf("Enter date (m/d/yyyy): ");
    scanf("%s", date);
    
    //Define the month, day and year
    int month = atoi(strtok(date, "/"));
    int day = atoi(strtok(NULL, "/"));
    int year = atoi(strtok(NULL, "/"));
    
    // acctIdx starts at 0 and ends at -1
    while(acctIdx < (*acctArr).count)
    {
        //Account balance
        balance = (*acctArr).array[acctIdx].balance;
        //Account transaction
        while((*acctArr).array[acctIdx].id == (*transArr).array[transIdx].account_id)
        {
            //Deposit amount
            if((*transArr).array[transIdx].type == 'd')
                balance += (*transArr).array[transIdx].amount;
            //Withdrawl
            else if((*transArr).array[transIdx].type == 'w')
                balance -= (*transArr).array[transIdx].amount;
            //Charge fee of overdraft charge
            if(balance < 0.0)
            {
                //Insert the fee into trasaction
                insert_transaction(transArr, (*transArr).count+1, (*acctArr).array[acctIdx].id,
                                   month, day, year, 'o', OVERDRAFT_CHARGE);
                
                //Substract the overdraft charge from balance
                balance -= OVERDRAFT_CHARGE;
            }
            //Go to next transaction
            transIdx++;
            //Record there is an account update
            count++;
            //Break loop
            if(transIdx >= (*transArr).count)
                break;
        }
        // Update
        if(count>0)
        {
            //The interest
            if(balance > 0.0)
            {
                // Calculate the interest and insert it into transaction
                interest = round_dbl(balance*(INTEREST_RATE/12.0), 2);
                insert_transaction(transArr, (*transArr).count+1,
                                   (*acctArr).array[acctIdx].id, month, day, year, 'i', interest);
                // Update the account balance
                (*acctArr).array[acctIdx].balance = round_dbl(balance + interest, 2);
            }
            else
                (*acctArr).array[acctIdx].balance = round_dbl(balance, 2);
        }
        // Go to the next account
        acctIdx++;
        // Reset update count when account goes to zero
        count = 0;
    }
    // Sort transactions by account and date
    sort_transactions(transArr);
}


//Search the array index
void print_account_id(AccountArray acctArr, TransactionArray transArr, int acctNo)
{
    int acctIdx = search_account_id(acctArr, acctNo);
    print_account_transactions(acctArr, transArr, acctIdx);
}

//Prints the account and transaction
void print_account_owner(AccountArray acctArr, TransactionArray transArr, char owner[])
{
    int acctIdx = search_account_owner(acctArr, owner);
    print_account_transactions(acctArr, transArr, acctIdx);
}

//Array index
void print_account_transactions(AccountArray acctArr, TransactionArray transArr, int acctIdx)
{
    char date[20];
    print_account(acctArr.array[acctIdx]);
    int transIdx = find_first_transaction(transArr, acctArr.array[acctIdx].id);
    if(transIdx >= 0){
        printf("ID	Date  Type  Amount\n");
        while(transArr.array[transIdx].account_id == acctArr.array[acctIdx].id){
            print_date(transArr.array[transIdx].date, date);
            printf(" %4d %15s %c %10.2f\n", transArr.array[transIdx].id, date, transArr.array[transIdx].type, transArr.array[transIdx].amount);
            transIdx++;
            if (transIdx >= transArr.count)
                break;
        }
    }
    else
        printf("No transactions found.\n");
    
}

//Print summary report
void print_summary_report(AccountArray acctArr, TransactionArray transArr)
{
    int acctIdx = 0;
    // Print header
    printf("Account Summary Report\n");
    printf("	ID            	Owner 	Balance\n");
    // Loop to print account
    for(acctIdx=0; acctIdx<acctArr.count; acctIdx++){
        printf("%6d %20s %10.2f\n",
               acctArr.array[acctIdx].id,
               acctArr.array[acctIdx].owner,
               acctArr.array[acctIdx].balance);
    }
}

//Print detail report
void print_detail_report(AccountArray acctArr, TransactionArray transArr)
{
    int acctIdx = 0;
    printf("Account Detail Report\n");
    // Loop to print account
    for(acctIdx=0; acctIdx<acctArr.count; acctIdx++)
    {
        print_account_transactions(acctArr, transArr, acctIdx);
        printf("\n");
    }
}
