#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> 
#include "semantic.h"

// References symbol table's function to find the time type for a scope
char* getItemType(char itemName[50], char scope[50]);

// Find an item's primary type using getItemType
// Returns the actual primary token
char* CheckPrimaryType(char*variableName, char*currentScope){
    // By default, return int
    if (strcmp(variableName, "int")==0){
        return "int";
    }

    // If this item is not in the symbol table, return a semantic error. Else, return the primary type
    char*inscope = getItemType(variableName, currentScope);
    if (strcmp(inscope, "nope") == 0){
        printf("SEMANTIC ERROR: Variable %s not defined in scope\n", variableName);

        exit(1);
    }
    return inscope;
}


// Checks the assignment type for a given item by checking its type
// Returns the actual type
char* CheckAssignmentType(char*identifier, char* exp, char* currentScope){
    printf("GetItemType\n");
    char* inscope = getItemType(identifier, currentScope);
    return inscope; 
}






