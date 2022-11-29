#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> 
#include "semantic.h"

// References symbol table's function to find the time type for a scope
char* getItemType(char itemName[50], char scope[50]);
int found(char itemName[50], char scope[50]);

// NEW SEMANTIC CHANGE
// Checks to see if a variable has been declared globally first
void CheckGlobal(char* variableName, char* currentScope) {
    int nonGlobal = strcmp(currentScope, "global");
    if (nonGlobal != 0 && found(variableName, "global") == 1) {
        printf("SEMANTIC ERROR: Var %s is already declared globally\n", variableName);
        exit(1);
    }
}

// Find an item's primary type using getItemType
// Returns the actual primary token
char* CheckPrimaryType(char * variableName, char * currentScope){
    // By default, return int
    if (strcmp(variableName, "int")==0){
        return "int";
    }
    if (strcmp(variableName, "string")==0){
        return "string";
    }

    if (strcmp(variableName, "float")==0){
        return "float";
    }

    // If this item is not in the symbol table, return a semantic error. Else, return the primary type
    char * inscope = getItemType(variableName, currentScope);
    if (strcmp(inscope, "nope") == 0){
        printf("SEMANTIC ERROR: Variable %s not defined in scope\n", variableName);
        exit(1);
    }
    return inscope;
}


// Checks the assignment type for a given item by checking its type
// Returns the actual type
char* CheckAssignmentType(char*identifier, char* exp, char* currentScope){
    //printf("GetItemType\n");
    char* inscope = getItemType(identifier, currentScope);
    return inscope; 
}

// Helper function to check if a string is alphanumeric
int isAlpha(char * phrase) {
    // Get length of string
    int len;
    for (len = 0; phrase[len] != '\0'; ++len);

    // Loop through each character
    // If there is an alphabetical character, return true
    for (int i = 0; i < len; i++) {
        if (isalpha(phrase[i])) {
            return 1;
        }
    }
    // If nothing is caught, return false
    return 0;
}

// Helper function to determine if the string is an integer
int isInt(char * phrase) {
    // Get length of string
    int len;
    for (len = 0; phrase[len] != '\0'; ++len);

    // Loop through each character
    // If there is a non-numerical character, return false
    for (int i = 0; i < len; i++) {
        if (!isdigit(phrase[i])) {
            return 0;
        }
    }

    // If nothing is caught, return true
    return 1;
}

// Helper function to determine if the string is a float
int isFloat(char * phrase) {
    // Get length of string
    int len;
    for (len = 0; phrase[len] != '\0'; ++len);

    // Set a var for float condition (must require one and only one "." symbol)
    int condition = 0;

    // Loop through each character
    for (int i = 0; i < len; i++) {
        if (!isdigit(phrase[i]) && phrase[i] != '.') {
            // If there is a non-numerical character, return false
            return 0;
        } else if (phrase[i] == '.' && condition == 0) {
            // Set float condition to true, requirement for string to be a float
            condition = 1;
        } else if (phrase[i] == '.' && condition == 1) {
            // Return false if string has two "." symbols
            return 0;
        }
    }

    // If condition is true and nothing is caught, return true
    if (condition == 1) {
        return 1;
    }
    // Else return false
    return 0;
}

// Helper function to determine the type of a token
// within a given assignment or operation statement
char * getPrimaryType(char * phrase) {
    // If the phrase is a type of string or char
    if (phrase[0] == '\"' || phrase[0] == '\'') {
        // If it has three characters, it must be a char
        // Commented out for now until we implement chars
        // if (strlen(phrase) == 3) {
        //     return "char";
        // }
        // Otherwise, return as a string
        return "string";
    }
    // Check if the phrase is an float
    else if (isFloat(phrase)) {
        return "float";
    }
    // Check if the phrase is an int
    else if (isInt(phrase)) {
        return "int";
    }
    // If all cases fail, the type must be a variable
    else {
        return "var";
    }
}

int isNotVar(char phrase[50]) {
    if (phrase[0] == '\"' || phrase[0] == '\'' || isFloat(phrase) || isInt(phrase)) {
        return 1;
    }
    return 0;
}

void checkIntDivisionError(int numerator, int denominator) {
    if (denominator == 0) {
        printf("\nDivision Error: Cannot divide %d by 0.\n", numerator);
        exit(1);
    }
}

void checkFloatDivisionError(float numerator, float denominator) {
    if (denominator == 0.0) {
        printf("\nDivision Error: Cannot divide %f by 0.0.\n", numerator);
        exit(1);
    }
}





