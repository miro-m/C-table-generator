#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "header.h"

#define MAX_NUMBERS 100 

char* columnList = NULL;
int rowCount = 0;
char* fileName = NULL;
char *charArray = NULL;

int* userIDsForUser = NULL;
char** firstNamesForUser = NULL;
char** lastNamesForUser = NULL;
char** countryNamesForUser = NULL;
char** phoneNumbersForUser = NULL;
char** emailsForUser = NULL;
char** SINsForUser = NULL;
char** passwordsForUser = NULL;



void displayOption(){
    printf("Column Options\n");
    printf("--------------\n");
    printf("1. User ID          5. Phone Number\n");
    printf("2. First Name       6. Email adress\n");
    printf("3. Last Name        7. SIN\n");
    printf("4. Country          8. Password\n");
}

bool instructionRequires(int instr, int* instructions, int count) {
        for (int i = 0; i < count; i++) {
        if (instructions[i] == instr) {
            return true;
            }
        }
            return false;
        }


int main(void){

bool RUN = true;
int option;


 while(RUN){

    system("clear");
    printf("\nTable Menu\n");
    printf("----------\n");
    printf("1. Generate new Table\n");
    printf("2. Exit\n");
    printf("\nSelection: ");
    scanf("%d", &option);

    switch(option){
        
        case 1:

        system("clear");
        displayOption();

        

        int numbers[MAX_NUMBERS];//where instructions will be stored
        char input[256]; // buffer to hold the user's input
        int totalInstructions = 0;

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        //THIS PART IS TO GET INSTRUCTIONS NEEDED FROM THE USER
        printf("\nEnter column list (comma-separated, no spaces): ");
        fgets(input, sizeof(input), stdin);

        char *token = strtok(input, ",\n"); // breaking the input into tokens using comma as a delimiter
        
        while (token != NULL && totalInstructions < MAX_NUMBERS) {
        numbers[totalInstructions] = atoi(token); // convert string to integer and store in numbers array
        totalInstructions++;
        token = strtok(NULL, ",\n");
        }

        


        printf("Enter row count (1 to 1 million): ");
        scanf("%d", &rowCount);        

        while ((getchar()) != '\n');

        char fileName[256];
        printf("Enter the file name (without .csv): ");
        fgets(fileName, sizeof(fileName), stdin);

        // Remove the trailing newline character from the file name
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
        fileName[len - 1] = '\0';
        }

        // Check if the filename ends with ".csv". If not, append it.
        if (len < 4 || strcmp(fileName + len - 4, ".csv") != 0) {
        strcat(fileName, ".csv");
        }

       //INCLUDE SUMMARY HERE
        printf("\nSummary of properties:");
        printf("\n Columns: %s", input);
        printf("\n Row count: %d", rowCount);
        printf("\n File name: %s", fileName);
        

        /* all the functions wanted to be executed will done here*/
        if (instructionRequires(1, numbers, totalInstructions)) {
            userIDsForUser = generateUserID(rowCount);
        }
        if (instructionRequires(2, numbers, totalInstructions)) {
            firstNamesForUser = generateFirstNames(rowCount);
        }
        if (instructionRequires(3, numbers, totalInstructions)) {
            lastNamesForUser = generateLastNames(rowCount);
        }
        if (instructionRequires(4, numbers, totalInstructions)) {
            countryNamesForUser = generateCountryNames(rowCount);
        }
        if (instructionRequires(5, numbers, totalInstructions)) {
            phoneNumbersForUser = generatePhoneNumbers(rowCount);
        }
        if (instructionRequires(6, numbers, totalInstructions)) {
            emailsForUser = generateEmail(rowCount, firstNamesForUser, lastNamesForUser);
        }
        if (instructionRequires(7, numbers, totalInstructions)) {
            SINsForUser = generateSINs(rowCount);
        }
        if (instructionRequires(8, numbers, totalInstructions)) {
            passwordsForUser = generatePasswords(rowCount);
        }

        FILE *file = fopen(fileName, "w");
        
        if (!file) {
        perror("Failed to open file");
        return 1;
        }

        // Write the header
        for (int i = 0; i < totalInstructions; i++) {
        switch(numbers[i]) {
            case 1: fprintf(file, "UserID,"); break;
            case 2: fprintf(file, "FirstName,"); break;
            case 3: fprintf(file, "LastName,"); break;
            case 4: fprintf(file, "CountryName,"); break;
            case 5: fprintf(file, "PhoneNumber,"); break;
            case 6: fprintf(file, "Email,"); break;
            case 7: fprintf(file, "SIN,"); break;
            case 8: fprintf(file, "Password,"); break;
        }
        }
        fprintf(file, "\n"); // end of header line

        //sorting first array, look sorting file
        sortDataBasedOnInstruction(rowCount, numbers[0]);

        for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < totalInstructions; j++) {
            switch(numbers[j]) {
                case 1: 
                fprintf(file, "%d,", userIDsForUser[i]);
                break;
            case 2:
                fprintf(file, "%s,", firstNamesForUser[i]);
                break;
            case 3:
                fprintf(file, "%s,", lastNamesForUser[i]);
                break;
            case 4:
                fprintf(file, "%s,", countryNamesForUser[i]);
                break;
            case 5:
                fprintf(file, "%s,", phoneNumbersForUser[i]);
                break;
            case 6:
                fprintf(file, "%s,", emailsForUser[i]);
                break;
            case 7:
                fprintf(file, "%s,", SINsForUser[i]);
                break;
            case 8:
                fprintf(file, "%s,", passwordsForUser[i]);
                break;
            }
        }
        fprintf(file, "\n"); // end of data line
    }

    for (int i = 0; i < rowCount; i++) {
         for (int j = 0; j < totalInstructions; j++) {
        switch (numbers[j]) {
            case 1:
                break;
            case 2:
                if (firstNamesForUser[i]) {
                    free(firstNamesForUser[i]);
                    firstNamesForUser[i] = NULL;
                }
                break;
            case 3:
                if (lastNamesForUser[i]) {
                    free(lastNamesForUser[i]);
                    lastNamesForUser[i] = NULL;
                }
                break;
            case 4:
                if (countryNamesForUser[i]) {
                    free(countryNamesForUser[i]);
                    countryNamesForUser[i] = NULL;
                }
                break;
            case 5:
                if (phoneNumbersForUser[i]) {
                    free(phoneNumbersForUser[i]);
                    phoneNumbersForUser[i] = NULL;
                }
                break;
            case 6:
                if (emailsForUser[i]) {
                    free(emailsForUser[i]);
                    emailsForUser[i] = NULL;
                }
                break;
            case 7:
                if (SINsForUser[i]) {
                    free(SINsForUser[i]);
                    SINsForUser[i] = NULL;
                }
                break;
            case 8:
                if (passwordsForUser[i]) {
                    free(passwordsForUser[i]);
                    passwordsForUser[i] = NULL;
                }
                break;
            default:
                
                break;
        }
    }
}
    //free all memory if array for columns used
    for (int j = 0; j < totalInstructions; j++) {
        switch (numbers[j]) {
        case 1:
            if (userIDsForUser) {
                free(userIDsForUser);
                userIDsForUser = NULL;
            }
            break;
        case 2:
            if (firstNamesForUser) {
                free(firstNamesForUser);
                firstNamesForUser = NULL;
            }
            break;
        case 3:
            if (lastNamesForUser) {
                free(lastNamesForUser);
                lastNamesForUser = NULL;
            }
            break;
        case 4:
            if (countryNamesForUser) {
                free(countryNamesForUser);
                countryNamesForUser = NULL;
            }
            break;
        case 5:
            if (phoneNumbersForUser) {
                free(phoneNumbersForUser);
                phoneNumbersForUser = NULL;
            }
            break;
        case 6:
            if (emailsForUser) {
                free(emailsForUser);
                emailsForUser = NULL;
            }
            break;
        case 7:
            if (SINsForUser) {
                free(SINsForUser);
                SINsForUser = NULL;
            }
            break;
        case 8:
            if (passwordsForUser) {
                free(passwordsForUser);
                passwordsForUser = NULL;
            }
            break;
        default:
            
            break;
    }
}

        printf("\n\nTable written successfully to %s \n",fileName);

        char proceed;
        printf("\nPress 'c' or 'C' to continue ");
        do{
        scanf("%c", &proceed);
        } while ( (proceed != 'c') && (proceed != 'C'));
        fclose(file);
        break;
        case 2:
            printf("Goodbye and thanks for using TableGen\n");
            freetheArraysOfData();
            RUN = false;
            break;

        default:
            printf("you are at default\n");
   


       

        }

    
 

    }//while end








    return 0;
}//main end