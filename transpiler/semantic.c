#include <stdio.h>
#include <ctype.h>
#include <string.h> 
#include "semantic.h"

char* CheckPrimaryType(char*variableName, char*currentScope){

    if (isdigit(variableName[0])){
        return "int";
    }

    char*inscope = getItemType(variableName, currentScope);
    if (strcmp(inscope, "nope") == 0){
        printf("SEMANTIC ERROR: Variable %s not defined in scope\n", variableName);
        exit(1);
    }

    return inscope;
}


char* CheckAssignmentType(char*identifier, char* exp, char* currentScope){

    char*inscope = getItemType(identifier, currentScope);

    return inscope; 
}

//3 rules







