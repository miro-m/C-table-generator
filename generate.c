#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "header.h"

#define MAX_NAME_LENGTH 25
#define MAX_NAMES 1000

#define MAX_COUNTRY 195
#define MAX_COUNTRY_LENGTH 40

#define MAX_SUFFIX_LENGTH 25
#define MAX_EMAIL_SUFFIXES 100

#define MAX_DIGIT 9

#define MIN_PASSWORD_LENGTH 6
#define MAX_PASSWORD_LENGTH 16

static char* firstNames[MAX_NAMES];
static int numNames = 0;

static char* lastNames[MAX_NAMES];
static int numLNames = 0;

static char* countryNames[MAX_COUNTRY];
static int numCountry = 0;

static int phoneIndexes[] = {398, 270, 925, 867, 209, 429, 908, 997, 444, 219};
static int numIndexes = sizeof(phoneIndexes) / sizeof(phoneIndexes[0]);

static char* emailSuffixes[MAX_EMAIL_SUFFIXES];
static int numSuffixes = 0;

int* generateUserID(int x){
    /*x will be the rowCount, it will create an array of length for the numbers of row*/
    int* array = (int*)malloc(x * sizeof(int));

    if (array == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
     
    for(int i = 0; i < x; i++){
        array[i] = i + 1;
    }

    return array;

}

/*Will read the file with  First names and will store them in an array.*/
static void readFirstNameFile() {
    FILE *file = fopen("first_names.txt", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char tempName[MAX_NAME_LENGTH]; // Temporary buffer to read names

    while (numNames < MAX_NAMES && fgets(tempName, sizeof(tempName), file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(tempName);
        if (len > 0 && tempName[len - 1] == '\n') {
            tempName[len - 1] = '\0';
        }

        // Check for excessively long names
        if (strlen(tempName) >= MAX_NAME_LENGTH) {
            fprintf(stderr, "Name too long: %s\n", tempName);
            exit(EXIT_FAILURE);
        }

        firstNames[numNames] = strdup(tempName);
        if (!firstNames[numNames]) {
            perror("Failed to allocate memory for name");
            exit(EXIT_FAILURE);
        }
        numNames++;
    }

    fclose(file);
}

char** generateFirstNames(int x){
    readFirstNameFile();

    char** resultFirstNames = (char**)malloc(x * sizeof(char*));

    for (int i = 0; i < x; i++) {
        int randomIndex = rand() % numNames;
        resultFirstNames[i] = strdup(firstNames[randomIndex]);
    }

    return resultFirstNames;
}


/*Will read the file with Last names and will store them in an array.*/
static void readLastNameFile() {
    FILE *file = fopen("last_names.txt", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char tempName[MAX_NAME_LENGTH];
    while (numLNames < MAX_NAMES && fgets(tempName, sizeof(tempName), file) != NULL) {
        size_t len = strlen(tempName);
        if (len > 0 && tempName[len - 1] == '\n') {
            tempName[len - 1] = '\0';
        }

        // Check for names too long just like before
        if (strlen(tempName) >= MAX_NAME_LENGTH) {
            fprintf(stderr, "Name too long: %s\n", tempName);
            exit(EXIT_FAILURE);
        }

        lastNames[numLNames] = strdup(tempName);
        if (!lastNames[numLNames]) {
            perror("Failed to allocate memory for name");
            exit(EXIT_FAILURE);
        }
        numLNames++;
    }

    fclose(file);
}


char** generateLastNames(int x){
    readLastNameFile();

    char** resultLastNames = (char**)malloc(x * sizeof(char*));
    if (resultLastNames == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < x; i++) {
        int randomIndex = rand() % numLNames;
        resultLastNames[i] = strdup(lastNames[randomIndex]);
    }

    return resultLastNames;
}

/*Will read the file with countries names and will store them in an array.*/
static void readCountryFile() {
    FILE *file = fopen("countries.txt", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char tempCountry[MAX_COUNTRY_LENGTH]; // Assuming you have defined a suitable maximum length for country names
    while (numCountry < MAX_COUNTRY && fgets(tempCountry, sizeof(tempCountry), file) != NULL) {
        size_t len = strlen(tempCountry);
        if (len > 0 && tempCountry[len - 1] == '\n') {
            tempCountry[len - 1] = '\0';
        }

        // Check for country names too long
        if (strlen(tempCountry) >= MAX_COUNTRY_LENGTH) {
            fprintf(stderr, "Country name too long: %s\n", tempCountry);
            exit(EXIT_FAILURE);
        }

        countryNames[numCountry] = strdup(tempCountry);
        if (!countryNames[numCountry]) {
            perror("Failed to allocate memory for country name");
            exit(EXIT_FAILURE);
        }
        numCountry++;
    }

    fclose(file);
}


char** generateCountryNames(int x){
    readCountryFile();

    char** resultCountryNames = (char**)malloc(x * sizeof(char*));
    if (resultCountryNames == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < x; i++) {
        int randomIndex = rand() % numCountry;
        resultCountryNames[i] = strdup(countryNames[randomIndex]);
    }

    return resultCountryNames;
}

static int generateRandomIndex() {
    int randomIndex = rand() % numIndexes;
    return phoneIndexes[randomIndex];
}

static int generateRandomLine() {
    return rand() % 10000; // Generate a random 4-digit number
}

char** generatePhoneNumbers(int x) {
    /* x is the number of rows*/

    char** phoneNumbers = (char**)malloc(x * sizeof(char*));

    if (phoneNumbers == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < x; i++) {
        int index = generateRandomIndex();
        int line = generateRandomLine();

        // Allocate memory for individual phone number
        phoneNumbers[i] = (char*)malloc(9 * sizeof(char)); // 7 characters for phone number + 1 for '\0'

        if (!phoneNumbers[i]) {
            perror("Memory allocation failed for individual phone number");
            exit(EXIT_FAILURE);
        }

        snprintf(phoneNumbers[i], 9, "%03d-%04d", index, line);
    }

    return phoneNumbers;
}

static void readEmailSuffixes() {
    FILE *file = fopen("email_suffixes.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char tempSuffix[MAX_SUFFIX_LENGTH]; // Temporary buffer to read suffixes. Make sure to define MAX_SUFFIX_LENGTH appropriately.

    while (numSuffixes < MAX_EMAIL_SUFFIXES && fgets(tempSuffix, sizeof(tempSuffix), file) != NULL) {
        // Remove newline character from the end if it exists
        size_t len = strlen(tempSuffix);
        if (len > 0 && tempSuffix[len - 1] == '\n') {
            tempSuffix[len - 1] = '\0';
        }

        emailSuffixes[numSuffixes] = strdup(tempSuffix);
        if (!emailSuffixes[numSuffixes]) {
            perror("Failed to allocate memory for email suffix");
            exit(EXIT_FAILURE);
        }

        numSuffixes++;
    }

    fclose(file);
}

char** generateEmail(int x, char* firstNames[], char* lastNames[]) {
    readEmailSuffixes();

    char** emailAddresses = (char**)malloc(x * sizeof(char*));
    if (emailAddresses == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < x; i++) {
        char firstInitial = tolower(firstNames[i][0]);
        char* lastName = lastNames[i];
        int randomSuffixIndex = rand() % numSuffixes;
        char* emailSuffix = emailSuffixes[randomSuffixIndex];

        char email[MAX_NAME_LENGTH + MAX_NAME_LENGTH + MAX_SUFFIX_LENGTH + 2];
        sprintf(email, "%c%s@%s", firstInitial, lastName, emailSuffix);
        emailAddresses[i] = strdup(email);
    }

    return emailAddresses;
}

static int generateRandomDigit() {
    return rand() % (MAX_DIGIT + 1); // Generate a random digit between 0 and 9
}

char** generateSINs(int rowCount) {
    char** sins = (char**)malloc(rowCount * sizeof(char*));
    if (sins == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rowCount; i++) {
        sins[i] = (char*)malloc(10 * sizeof(char));
        for (int j = 0; j < 9; j++) {
            int digit = generateRandomDigit();
            sins[i][j] = '0' + digit; 
        }
        sins[i][9] = '\0'; // Add null terminator to make it a valid string
    }

    return sins;
}


static char generateRandomChar() {
    const char exclusions[] = { ',', ' ', '\0' };  // Characters to exclude
    char ch;
    do {
        ch = 33 + rand() % (126 - 33 + 1);  // Generate a character between '!' and '~'
    } while (strchr(exclusions, ch));  // Keep generating until it's not an excluded character
    return ch;
}

static void generatePassword(char* password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = generateRandomChar();
    }
    password[length] = '\0';  // Add null terminator to make it a valid string
}

char** generatePasswords(int rowCount) {
    char** passwords = (char**)malloc(rowCount * sizeof(char*)); 

    if (passwords == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rowCount; i++) {
        passwords[i] = (char*)malloc((MAX_PASSWORD_LENGTH + 1) * sizeof(char));
        if (!passwords[i]) {
            perror("Memory allocation for password failed");
            exit(EXIT_FAILURE);
        }
        int length = MIN_PASSWORD_LENGTH + rand() % (MAX_PASSWORD_LENGTH - MIN_PASSWORD_LENGTH + 1);
        generatePassword(passwords[i], length);
    }

    return passwords;
}

void freetheArraysOfData(){
    for (int i = 0; i < numSuffixes; i++) {
        free(emailSuffixes[i]);  // free each string
    }
    
    for (int i = 0; i < MAX_COUNTRY; i++) {
        free(countryNames[i]);  // free each string
    }

    for (int i = 0; i < MAX_NAMES; i++) {
        free(firstNames[i]);  // free each string
    }

    for (int i = 0; i < MAX_NAMES; i++) {
        free(lastNames[i]);  // free each string
    }
    
}
