#ifndef HEADER_H
#define HEADER_H

extern char* columnList;
extern int rowCount;
extern char* fileName;

extern int* userIDsForUser;
extern char** firstNamesForUser;
extern char** lastNamesForUser;
extern char** countryNamesForUser;
extern char** phoneNumbersForUser;
extern char** emailsForUser;
extern char** SINsForUser;
extern char** passwordsForUser;

int* generateUserID();
char** generateFirstNames();
char** generateLastNames();
char** generateCountryNames();
char** generatePhoneNumbers();
char** generateEmail();
char** generateSINs();
char** generatePasswords();

int compareByFirstName();
int compareByLastName();
int compareByCountryName();
int compareByPhoneNumber();
int compareByEmail();
int compareBySIN();
int compareByPassword();
void sortDataBasedOnInstruction();
void freetheArraysOfData();

#endif