#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> 
#include "semantic.h"

// References symbol table's function to find the item type for a scope
char* getItemType(char itemName[50], char scope[50]);

// NEW SEMANTIC CHANGE
// Checks to see if a variable has been declared globally first
void CheckGlobal(char* variableName, char* currentScope) {
    int nonGlobal = strcmp(currentScope, "global");
    if (nonGlobal != 0 && found(variableName, "global") == 1) {
        printf("SEMANTIC ERROR: Var %s is already declared globally\n", variableName);
        exit(1);
    }
}

// NEW SEMANTIC CHANGE
// Check to see if the number of parameters matches the function definition
void CheckNumParams(char* func, char* exprList, char* currentScope) {
    // Write code here
    // Traverse the AST at the point of the function name
    // Count how many Param nodes are below the function call itself
    // Check the count of ExprList items, and compare
    // If the number of items match, the check has been satisfied
    // Otherwise, throw an error
    struct Entry* params;
    int funcParams = 0;
    size_t callParams;
    params = getParams(func, currentScope);

    // funcParams = countParams(params);
    printf("\nExprList:\n");
    for(int i = 0; exprList[i] != '\0'; i++)
    {
        printf("%c ", exprList[i]);
    }

    callParams = sizeof(exprList)/sizeof(exprList[0]);

    printf("\nNum callParams: %d", callParams);
    // printf("\nNum funcParams: %d", funcParams);

    if (funcParams != callParams) {
        printf("\nSEMANTIC ERROR: Call parameters does not match the parameters of function \"%s\". The function contains %d parameters, and the function call contains %d parameters.\n", func, funcParams, callParams);
        exit(1);
    }

}

// Check to see if each parameter type matches the function definition
void CheckParamTypes(char* func, char* exprList, char* currentScope) {
    // Write code here
    // Use compareTypes and loop through each element in the ExprList and ParamList
    // If any type in either list doesn't match, throw an error
}

// Find an item's primary type using getItemType
// Returns the actual primary token
char* CheckPrimaryType(char*variableName, char*currentScope){
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
    if (strcmp(variableName, "function")==0){
        return "function";
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
    //printf("GetItemType\n");
    char* inscope = getItemType(identifier, currentScope);
    return inscope; 
}

/*
int checkDivisionError(int * num1, int * num2) {
    if (num1 == 0 && num1 == num2) {
        printf("Division Error: Cannot divide 0 by 0.");
        return 1;
    }
    return 0;
}
*/



