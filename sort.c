#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "header.h"


 

int compareByFirstName(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareByLastName(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareByCountryName(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareByPhoneNumber(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareByEmail(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareBySIN(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

int compareByPassword(const void* a, const void* b) {
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strcmp(str1, str2);
}

void sortDataBasedOnInstruction(int rowCount, int instruction) {
    switch(instruction) {
        case 2: 
            qsort(firstNamesForUser, rowCount, sizeof(char*), compareByFirstName);
            break;
        case 3: 
            qsort(lastNamesForUser, rowCount, sizeof(char*), compareByLastName);
            break;
        case 4: 
            qsort(countryNamesForUser, rowCount, sizeof(char*), compareByCountryName);
            break;
        case 5: 
            qsort(phoneNumbersForUser, rowCount, sizeof(char*), compareByPhoneNumber);
            break;
        case 6: 
            qsort(emailsForUser, rowCount, sizeof(char*), compareByEmail);
            break;
        case 7: 
            qsort(SINsForUser, rowCount, sizeof(char*), compareBySIN);
            break;
        case 8: 
            qsort(passwordsForUser, rowCount, sizeof(char*), compareByPassword);
            break;
    }
}