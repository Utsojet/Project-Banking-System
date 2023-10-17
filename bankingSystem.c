#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bankCapitalFile[20]="bankCapital.txt";
char acountDB[20]="acountDatabase.txt";
char tempFileName[20] = "tempFile.txt";
char fileType[5] = ".txt";

float setGetBankCapital(float floatValue, int operation) {
    float bankCapital = 0;
    FILE *file = fopen(bankCapitalFile, "r");
        if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
        }
    // Read the float value from the file
        fscanf(file, "%f", &bankCapital);
        fclose(file);
    // Modify the float value
    if(operation){
        bankCapital += floatValue;
    }else{
        bankCapital -= floatValue;
    }

    file = fopen("bankCapital.txt", "w");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }
    // Write the float value to the file
    fprintf(file, "%f", bankCapital);
    fclose(file);
    return bankCapital;
}


int searchDB (int number){
            FILE *file = fopen(acountDB, "r");//open the file in read mode
            if (file == NULL) {
            printf("Unable to open the file.\n");
            return 0;
            }
            int acountNumberTemporary; //temporary variable to store data here from the txt file
            char acountNameTemporary[50]; //temporary variable to store data here from the txt file
            char passwordTemporary[20]; //temporary variable to store data here from the txt file
            float balanceTemporary;
            int status=0;//

            //in this while loop we will loop from first to last of the txt file and every line we will check for the acountNumber it acount number matches user will need
            //give password otherwise he will need do it again
            while (fscanf(file, "%d %s %s %f", &acountNumberTemporary,&acountNameTemporary,&passwordTemporary,&balanceTemporary) == 4) {
                if (number == acountNumberTemporary) {
                    status=1;
                }
            }
            fclose(file);
            if(status==0){
                return 0;
            }else{
                return 1;
            }
}
void getDetailsDB (int number, char*acountPassword, char *acountName, float *acountBalance){

            FILE *file = fopen(acountDB, "r");//open the file in read mode
            if (file == NULL) {
            printf("Unable to open the file.\n");
            }
            int acountNumberTemporary; //temporary variable to store data here from the txt file
            char acountNameTemporary[50]; //temporary variable to store data here from the txt file
            char passwordTemporary[20]; //temporary variable to store data here from the txt file
            float balanceTemporary;
            //in this while loop we will loop from first to last of the txt file and every line we will check for the acountNumber it acount number matches user will need
            //give password otherwise he will need do it again
            while (fscanf(file, "%d %s %s %f", &acountNumberTemporary,&acountNameTemporary,&passwordTemporary,&balanceTemporary) == 4) {
                if (number == acountNumberTemporary) {
                    strcpy(acountName,acountNameTemporary);
                    *acountBalance=balanceTemporary;
                    strcpy(acountPassword,passwordTemporary);
                }
            }
            fclose(file);

}

void editAcountDatabase(int number,float amount, int type){

    FILE *file = fopen(acountDB, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");

    }

    FILE *tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        printf("Failed to create a temporary file.\n");
        fclose(file);

    }

    int acountNumberTemporary;
    char acountNameTemporary[30];
    int acountPasswordTemporary[20];
    float acountBalanceTemporary;
    int status =0;
    while (fscanf(file, "%d %s %s %f", &acountNumberTemporary, acountNameTemporary, acountPasswordTemporary, &acountBalanceTemporary) == 4) {
        if (number == acountNumberTemporary) {
            // Update the balance by adding the deposit amount
            if (type==1){
            acountBalanceTemporary += amount;
            setGetBankCapital(amount,1);
            }else{
            acountBalanceTemporary -= amount;
            setGetBankCapital(amount,0);
            }
            status =1;
        }
        fprintf(tempFile, "%d %s %s %f \n", acountNumberTemporary, acountNameTemporary, acountPasswordTemporary, acountBalanceTemporary);
    }

fclose(file);
fclose(tempFile);

    if (remove(acountDB) != 0) {
        printf("Failed to remove the original file.\n");

    }
    if (rename(tempFileName, acountDB) != 0) {
        printf("Failed to rename the temporary file.\n");

    }
    if (status){
        setGetBankCapital(number,type);

    }
}

void updateStatement(int number,float amount, int type, int receiver){
    //type 1 for deposit
    //type 0 for withdraw
    //type 2 for transfer
    //type 3 for received
    //type 4 for loan
    char acountNumberString[20]; //as we are creating ffiles according to acountNumber we have to convert acountNumber to string
    sprintf(acountNumberString,"%d",number); //acountnumber converted to string
    strcat(acountNumberString, fileType);
    FILE *file = fopen(acountNumberString, "a");
    switch (type){
        case 0:{
        fprintf(file, "%d  %s  %f  %s\n", number, "Withdraw", amount,"......");
        break;
        }
        case 1:{
        fprintf(file, "%d  %s  %f  %s\n", number, "Deposit", amount,"......");
        break;
        }
        case 2:{
        fprintf(file, "%d  %s  %f  %d\n", number, "Transferred", amount, receiver);
        break;
        }
        case 3:{
        fprintf(file, "%d  %s  %f  %d\n", receiver, "Received", amount, number);
        break;
        }
        case 4:{
        fprintf(file, "%d  %s  %f  %s\n", number, "Loan", amount, "......");
        break;
        }
        default:{
        break;
        }
    }
    fclose(file);

}


int main(){

int acountNumber;
char acountName[30];
char acountPassword[30];
float acountBalance;

    FILE *capital = fopen(bankCapitalFile, "a");
    fclose(capital);
    FILE *acountDBname=fopen(acountDB,"a");
    fclose(acountDBname);
    int choice;
    int loggedIn=0; // If 0 user dont see acount creation promt otherwise he sees the promt. Default value is ) that means user not logged in

    do{
        printf("\n");
        printf("Banking System Menu:\n");
        if(loggedIn){
            printf("User %s  Currently logged in \n",acountName);

        }else{
            printf("1. Create Account\n");
            printf("2. log in \n");
        }

        if(loggedIn){
            printf("3. Deposit Money\n");
            printf("4. Withdraw Money\n");
            printf("5. Transfer Money\n");
            printf("6. Take Loan \n");
            printf("7. Display Transaction History \n");
            printf("8. Show balance \n");
            printf("9. Log out \n");
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);

    switch (choice) {
        case 1:{
        printf("Enter acount number: ");
        scanf("%d", &acountNumber);

        if(searchDB(acountNumber)){
            printf("Acount already exist");
            break;
        }


        printf("Enter acount name: ");
        scanf("%s",acountName);

        printf("Enter acount password: ");
        scanf("%s",acountPassword);



        FILE *file = fopen(acountDB, "a"); //we will open acountDatabase file in append mode to add userDetails in a new line of the text file
        acountBalance=0;//initial acountBalance is 0
        fprintf(file, "%d %s %s %f\n", acountNumber, acountName, acountPassword, acountBalance);//done adding user details in the txt file
        fclose(file);//closing file


        char acountNumberString[20]; //as we are creating files according to acountNumber we have to convert acountNumber to string
        sprintf(acountNumberString,"%d",acountNumber); //acountnumber converted to string

        // char fileType[5] = ".txt";//this string is the file type in this case it is txt we will add this at the end of the acountAddress
        strcat(acountNumberString, fileType); //finallly we will get file address in which we will add transaction history out put of this function will be "AcountHistory/12345.txt"

        file = fopen(acountNumberString, "w");// creating a new file againts the users acountNumber
        fclose(file);

        loggedIn = 1; // As user acount created we automatically logged in the user by seeting this loggedIn variable to 1
        printf("Acount Created and logged in \n");

        break;
        }


        case 2:{
            char temporaryPassword[100];
            printf("Enter acount number: ");
            scanf("%d",&acountNumber);

            if(searchDB(acountNumber)){
            getDetailsDB(acountNumber,acountPassword,acountName,&acountBalance);
            printf("Enter password: ");
            scanf("%s",temporaryPassword);
            if(strcmp(acountPassword,temporaryPassword)==0){
                loggedIn=1;
                printf("\n");
                printf("User %s loggedIn",acountName);
                             printf("\n");
            }else{
                printf("Wrong password try again.... \n");
            }
            }else{
                printf("No acount found with that number.. \n");
            }
            break;
        }


        case 3:{
            if(!loggedIn){
            printf("Please log in first \n");
            break;
            }
            float deposit=0.00;
            printf("How much money you want to deposit(Taka): ");
            scanf("%f",&deposit);
            editAcountDatabase(acountNumber,deposit,1);
            updateStatement(acountNumber,deposit,1,0);
            getDetailsDB(acountNumber,acountPassword,acountName,&acountBalance);

            printf("%f (Taka) deposited \n",deposit);
            printf("New balance %f (Taka) \n",acountBalance);

            break;
        }


        case 4:{
            if(!loggedIn){
                printf("Please log in first \n");
                break;
            }
            float withdrawAmount=0;
            printf("Enter the amount you want to Withdraw: ");
            scanf("%f",&withdrawAmount);
            if(withdrawAmount<acountBalance){
                editAcountDatabase(acountNumber,withdrawAmount,0);
                updateStatement(acountNumber,withdrawAmount,0,0);
                getDetailsDB(acountNumber,acountPassword,acountName,&acountBalance);
                printf("%f (Taka) withdrawn \n",withdrawAmount);
            }else{
                printf("Not enough money in balance \n");
            }

            break;
        }


        case 5:{
            if(!loggedIn){
                printf("Please log in first \n");
                break;
            }
            int receiverAcount=0;
            float transferAmount=0;
            printf("Enter receiver acount number: ");
            scanf("%d",&receiverAcount);
            if(searchDB(receiverAcount)){
                printf("Enter amount to transfer (Taka)= ");
                scanf("%f",&transferAmount);

                editAcountDatabase(acountNumber,transferAmount,0);
                updateStatement(acountNumber,transferAmount,2,receiverAcount);

                editAcountDatabase(receiverAcount,transferAmount,1);
                updateStatement(receiverAcount,transferAmount,3,acountNumber);

                getDetailsDB(acountNumber,acountPassword,acountName,&acountBalance);

                printf("%f (Taka) transferred to acount %d", transferAmount,receiverAcount);
            }else{
                printf("No acount found matching the number.. \n");
                break;
            }


            break;
        }


        case 6:{
            if(!loggedIn){
                printf("Please log in first \n");
                break;
            }
            float loanAmount=0.000000;
            printf("Enter how much you want to take lone: ");
            scanf("%f",&loanAmount);
            float bankCapital =setGetBankCapital(0.0000000,1);

            if(loanAmount>((bankCapital*15)/100)){
                printf("Bank does't have enough capital to give that amount of loan \n");
                break;
            }
            editAcountDatabase(acountNumber,loanAmount,1);
            updateStatement(acountNumber,loanAmount,4,0);
            getDetailsDB(acountNumber,acountPassword,acountName,&acountBalance);
            printf("%f (Taka) Loan received \n",loanAmount);

           break;
        }


        case 7:{
            if(!loggedIn){
            printf("Please log in first \n");
            break;
            }
            printf("\n");
            char acountNumberStringS[20]; // Adjust the buffer size as needed
            sprintf(acountNumberStringS, "%d", acountNumber);
            strcat(acountNumberStringS, fileType);

            FILE *file = fopen(acountNumberStringS, "r");

            if (file == NULL) {
            return 1;
            }

            char line[256];
            // Read and print each line from the file
            while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            }
            fclose(file);
           break;
        }

        case 8:{
            getDetailsDB(acountNumber, acountPassword,acountName, &acountBalance);
            printf("\n");
            printf("Your Balance is %f (Taka) \n", acountBalance);
            break ;
        }
        case 9:{
            loggedIn = 0;
            printf("Logged out \n");
            break ;
        }

        default:{
            printf("\n Try again");
            break;
        }

    }
    }while(1);

    return 0;
}
