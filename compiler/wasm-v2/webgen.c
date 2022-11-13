// Set of functions to emit WAT code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "webgen.h"
#include "symbolTable.h"

// Initialize WATcode file, IRcode file, and other required variables
FILE * WATcode;
int startASM = 0;
FILE * IRcode; // added for code generator 
char code[10000];

// Function to open the files for IRcodeOptimized.ir and WATcode.asm
// Required before generating any WAT code
void initAssemblyFile() {
  
 printf("\nOpening WAT Code file\n\n"); // Creates a WAT file with a generic header that needs to be in every file
 IRcode = fopen("IRcodeOptimized.ir", "r");
 WATcode = fopen("WATcode.wat", "w");
    
}

// Function to generate the initial set of lines required for proper WebAssembly output
void generateModule() {
    fprintf(WATcode, "(module\n");
    fprintf(WATcode, "\t;; WAT Setup Declarations\n");
    fprintf(WATcode, "\t(import \"env\" \"jsprint\" (func $jsprint (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"newline\" (func $newline))\n");
    fprintf(WATcode, "\t(import \"env\" \"writeconsole\" (func $writeconsole (param i32)))\n");
    fprintf(WATcode, "\t(memory $0 1)\n");
    fprintf(WATcode, "\t(export \"pagememory\" (memory $0))\n\n");
    fprintf(WATcode, "\t;; Artsy Program in WAT\n");
}

// Helper function that maps IRcode to the corresponding WebAssembly type
char * getWATType(char * phrase) {
    char * watType = "";

    if (strncmp(phrase, "float", 5) == 0) {
        watType = "f32";
        return watType;
    } else if (strncmp(phrase, "int", 3) == 0) {
        watType = "i32";
        return watType;
    } else if (strncmp(phrase, "string", 6) == 0) {
        watType = "i64";
        return watType;
    }
}

// Helper function that returns the number of characters to move after finding the corresponding WebAssembly type
int getMoveAmount(char * phrase) {
    if (strncmp(phrase, "float", 5) == 0) {
        return 6;
    } else if (strncmp(phrase, "int", 3) == 0) {
        return 4;
    } else if (strncmp(phrase, "string", 6) == 0) {
        return 7;
    }
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

// Standard function to generate a new line of code
// Used to print neater output in WAT
void printNewLine() {
}

// Standard function to generate the main section and text section
// Required before generating any WAT statements
void generateText() {
    // Variables to detect if declared types and params are within a function
    int isGlobal = 1;
    int inParams = 0;

    // Current scope variable
    char * currScope = "global";

    // Current operation variable
    char * currOp = "";

    // Global return type variable for a given function
    char * returnType = "";

    // Loop through each line in the code and generate WAT for each valid statement
    while (fgets(code, 10000, IRcode) != NULL) {
        // Case for type declarations
        if (strncmp(code, "type ", 5) == 0){
            // Set function return type first if this is the first call in a function
            if (inParams) {
                inParams = 0;
                fprintf(WATcode, "(result %s)\n", returnType);
            }

            char * nextPart = code + 5;
            nextPart[strlen(nextPart) - 1] = 0;

            // Get the rest of the string
            char * newType = getWATType(nextPart);
            int moveAmount = getMoveAmount(nextPart);

            char * variable = nextPart + moveAmount;

            // Set scope to global by default
            char * scopeType = "(global";

            if (!isGlobal) { // If its within a function, set the scope to local
                scopeType = "\t(local";
            }

            fprintf(WATcode, "\t%s $%s %s)\n", scopeType, variable, newType);
        }
        // Case for parameter declarations in functions
        else if (strncmp(code, "param ", 6) == 0) {
            char * nextPart = code + 6;
            nextPart[strlen(nextPart) - 1] = 0;

            // Get the rest of the string
            char * newType = getWATType(nextPart);
            int moveAmount = getMoveAmount(nextPart);

            char * variable = nextPart + moveAmount;

            fprintf(WATcode, "(param $%s %s) ", variable, newType);
        }
        // Case for entering function declarations
        else if (strncmp(code, "entry ", 6) == 0) {
            // Set all types after this to local declarations
            isGlobal = 0;
            inParams = 1;

            char * nextPart = code + 6;
            nextPart[strlen(nextPart) - 1] = 0;

            // Get the rest of the string
            char * newType = getWATType(nextPart);
            int moveAmount = getMoveAmount(nextPart);

            char * variable = nextPart + moveAmount;

            // Set global return type variable, which is specific to this function
            returnType = newType;

            // Set new scope
            currScope = variable;

            fprintf(WATcode, "\t(export \"%s\" (func $%s))\n", variable, variable);
            fprintf(WATcode, "\t(func $%s ", variable);
        }
        // Case for exiting functions
        else if (strncmp(code, "exit", 4) == 0) {
            // Set all types after this to global declarations
            isGlobal = 1;

            // Set scope back to global
            currScope = "global";

            fprintf(WATcode, "\t)\n");
        }
        // Case for return statements in functions
        else if (strncmp(code, "return ", 7) == 0) {
            // Output comment
            fprintf(WATcode, "\t\t;; %s", code);

            // Get variable name
            char * variable = code + 7;
            variable[strlen(variable) - 1] = 0;

            // Print function ending code
            fprintf(WATcode, "\t\t(local.get $%s)\n", variable);
        }
        // If the IRcode calls a write/output statement
        else if (strncmp(code, "output ", 7) == 0) {
            // Set function return type first if this is the first call in a function
            if (inParams) {
                inParams = 0;
                fprintf(WATcode, "(result %s)\n", returnType);
            }

            // Determine if the operation assignment within global or within a function
            char * progScope = "";
            if (!isGlobal) { // If its within a function, add a tab
                progScope = "\t";
            }

            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;
            fprintf(WATcode, "\t\t;; %s \n", code);

            // If the write statement does not use a variable
            if (getPrimaryType(variable) != "var") {
                // Get WAT Type for printing to the console
                char * WATType = getWATType(variable);

                fprintf(WATcode, "\t%s(call $writeconsole\n", progScope);
                fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, WATType, variable);
                fprintf(WATcode, "\t%s)\n", progScope);
            } else { // Else, the variable uses a variable
                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(variable, "global")) {
                    scopeType = "local";
                }

                fprintf(WATcode, "\t%s(call $writeconsole\n", progScope);
                fprintf(WATcode, "\t\t%s(%s.get $%s)\n", progScope, scopeType, variable);
                fprintf(WATcode, "\t%s)\n", progScope);
                                
            }
        }
        // If the code contains a writeln statement, print a new line
        else if (strncmp(code, "nextline", 8) == 0) {
            // Call print line function
            // Determine if the operation assignment within global or within a function
            char * progScope = "";
            if (!isGlobal) { // If its within a function, add a tab
                progScope = "\t";
            }
            
            fprintf(WATcode, "\t%s;; Print New Line\n", progScope);
            fprintf(WATcode, "\t%s(call $newline)\n", progScope);
        }
        // Case for handling suboperation states
        else if (strncmp(code, "subop ", 6) == 0) {
            // Get variable name
            char * variable = code + 6;
            variable[strlen(variable) - 1] = 0;

            // Set current operation
            // TK ERROR HERE
            currOp = malloc(strlen(variable)*sizeof(char));
            strcpy(currOp, variable);
        }
        // If the file contains a newline or a comment, ignore the statement
        else if (strncmp(code, "\n", 1) == 0 || strncmp(code, "#", 1) == 0){
        }
        // If the IRcode calls an assignment statement
        else {
            // Algorithm
            // Step 1: Break apart the line into an iterable array of strings
            // Set the delimiter for separating terms by word
            char ** strArr;
            int maxArrSize = 100;
            strArr = malloc(maxArrSize * sizeof(char *));
            char delimiter[] = " ";
            char * token = strtok(code, delimiter);

            // Add all tokens to a string array
            int lenIndex = 0;
            printf("\nTokens:");
            while(token != NULL) {
                // Assign to string array
                printf("\n%s", token);
                strArr[lenIndex] = token;
                lenIndex++;
                token = strtok(NULL, delimiter);
            }

            // Remove "\n" character from the last string
            lenIndex--;
            strArr[lenIndex][strlen(strArr[lenIndex])-1] = '\0';

            // Step 2: Build out case statements for the supported features

            // a. Assignment Statements
            // - Total Strings = 3
            // - STR1 = Var, STR2 = "=", STR3 = primary/variable

            // Assignment Operation
            if (strArr[3] == NULL) {
                printf("Assign Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
            }

            // b. Basic Operations
            // - Total Strings = 5
            // - STR1 = Var, STR2 = "=", STR3 = primary/variable,
            // - STR4 = Operand, STR5 = primary/variable

            // Add operation
            else if (strcmp(strArr[3], "+") == 0) {
                printf("Add Op\n");
                
                // Declare all three variables
                char * assignVar = strArr[0];
                char * var1 = malloc(strlen("$") + strlen(strArr[2]) + 1);
                char * var2 = malloc(strlen("$") + strlen(strArr[4]) + 1);
                
                // Declare operation type variable
                char * opType;

                // Determine if the operation assignment within global or within a function
                char * progScope = "";
                if (!isGlobal) { // If its within a function, add a tab
                    progScope = "\t";
                }

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(assignVar, "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Output the variable set line
                fprintf(WATcode, "\t%s(%s $%s %s)\n", progScope, scopeType, assignVar, opType);
                fprintf(WATcode, "\t%s(%s.set $%s\n", progScope, scopeType, assignVar);

                // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[2]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var1, "$");
                    strcat(var1, strArr[2]);
                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var1);
                } else {
                    var1 = strArr[2];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var1);
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[4]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[4], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var2, "$");
                    strcat(var2, strArr[4]);

                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var2);
                } else {
                    var2 = strArr[4];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var2);
                }

                // Perform operation and end the call
                fprintf(WATcode, "\t\t%s%s.add\n", progScope, opType);
                fprintf(WATcode, "\t%s)\n", progScope);
            }
            // Sub operation
            else if (strcmp(strArr[3], "-") == 0) {
                printf("Sub Op\n");
                // Declare all three variables
                char * assignVar = strArr[0];
                char * var1 = malloc(strlen("$") + strlen(strArr[2]) + 1);
                char * var2 = malloc(strlen("$") + strlen(strArr[4]) + 1);
                
                // Declare operation type variable
                char * opType;

                // Determine if the operation assignment within global or within a function
                char * progScope = "";
                if (!isGlobal) { // If its within a function, add a tab
                    progScope = "\t";
                }

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(assignVar, "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Output the variable set line
                fprintf(WATcode, "\t%s(%s $%s %s)\n", progScope, scopeType, assignVar, opType);
                fprintf(WATcode, "\t%s(%s.set $%s\n", progScope, scopeType, assignVar);

                // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[2]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var1, "$");
                    strcat(var1, strArr[2]);
                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var1);
                } else {
                    var1 = strArr[2];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var1);
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[4]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[4], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var2, "$");
                    strcat(var2, strArr[4]);

                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var2);
                } else {
                    var2 = strArr[4];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var2);
                }

                // Perform operation and end the call
                fprintf(WATcode, "\t\t%s%s.sub\n", progScope, opType);
                fprintf(WATcode, "\t%s)\n", progScope);
            }
            // Mul operation
            else if (strcmp(strArr[3], "*") == 0) {
                printf("Mul Op\n");
                // Declare all three variables
                char * assignVar = strArr[0];
                char * var1 = malloc(strlen("$") + strlen(strArr[2]) + 1);
                char * var2 = malloc(strlen("$") + strlen(strArr[4]) + 1);
                
                // Declare operation type variable
                char * opType;

                // Determine if the operation assignment within global or within a function
                char * progScope = "";
                if (!isGlobal) { // If its within a function, add a tab
                    progScope = "\t";
                }

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(assignVar, "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Output the variable set line
                fprintf(WATcode, "\t%s(%s $%s %s)\n", progScope, scopeType, assignVar, opType);
                fprintf(WATcode, "\t%s(%s.set $%s\n", progScope, scopeType, assignVar);

                // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[2]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var1, "$");
                    strcat(var1, strArr[2]);
                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var1);
                } else {
                    var1 = strArr[2];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var1);
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[4]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[4], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var2, "$");
                    strcat(var2, strArr[4]);

                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var2);
                } else {
                    var2 = strArr[4];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var2);
                }

                // Perform operation and end the call
                fprintf(WATcode, "\t\t%s%s.mul\n", progScope, opType);
                fprintf(WATcode, "\t%s)\n", progScope);
            }
            // Div operation
            else if (strcmp(strArr[3], "/") == 0) {
                printf("Div Op\n");
                // Declare all three variables
                char * assignVar = strArr[0];
                char * var1 = malloc(strlen("$") + strlen(strArr[2]) + 1);
                char * var2 = malloc(strlen("$") + strlen(strArr[4]) + 1);
                
                // Declare operation type variable
                char * opType;

                // Determine if the operation assignment within global or within a function
                char * progScope = "";
                if (!isGlobal) { // If its within a function, add a tab
                    progScope = "\t";
                }

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(assignVar, "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Output the variable set line
                fprintf(WATcode, "\t%s(%s $%s %s)\n", progScope, scopeType, assignVar, opType);
                fprintf(WATcode, "\t%s(%s.set $%s\n", progScope, scopeType, assignVar);

                // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[2]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var1, "$");
                    strcat(var1, strArr[2]);
                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var1);
                } else {
                    var1 = strArr[2];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var1);
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (getPrimaryType(strArr[4]) == "var") {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[4], "global")) {
                        varScopeType = "local";
                    }

                    strcat(var2, "$");
                    strcat(var2, strArr[4]);

                    fprintf(WATcode, "\t\t%s(%s.get %s)\n", progScope, varScopeType, var2);
                } else {
                    var2 = strArr[4];
                    fprintf(WATcode, "\t\t%s(%s.const %s)\n", progScope, opType, var2);
                }

                // Special case for division
                // If the operation is an integer, specify "div_s"
                char * specialOp = "";
                if (opType == "i32") {
                    specialOp = "_s";
                }

                // Perform operation and end the call
                fprintf(WATcode, "\t\t%s%s.div%s\n", progScope, opType, specialOp);
                fprintf(WATcode, "\t%s)\n", progScope);
            }


            // c. Function Calls
            // - Contains a "call"

            // Free specific string index for loop reuse
            strArr[3] = "\0";

            // OLD CODE BELOW

            // Set function return type first if this is the first call in a function

            // Declare start and end chars
            // char*start = code+7;
            // char*end = start;
            
            // While a ":" is not encountered, loop through and assign the corresponding variable in WAT
            // while (*end != ':') end++;
            // char variable [256]; 
            // strncpy(variable, start, (end - start));
            // variable[end - start] = 0;
            // int value = atoi(++end);
            // Assign variable and number
            // int lower = value & 0xffff;
            // int upper = (value & 0xffff0000) >> 16;

            // Generate WAT code using code, upper, lower, and variable
            // fprintf(WATcode, "\t\t;; %s\n", code);
            // fprintf(WATcode, "\t\t(local.set $%s\n", variable);
            // fprintf(WATcode, "\t\t\t(i32.const %d)\n", lower);
            // fprintf(WATcode, "\t\t)\n");

        }
    }

}

// Function to end WAT generation once all commands are printed from the IRcodeOptimized.ir file
void completeFile() {
    // Print ending WAT commands to the file    
    fprintf(WATcode, ")\n");

    // Closes all files once complete
    fclose(IRcode);
    fclose(WATcode);
}


// Main driver function to generate all WAT code
void generateWATcode() {
    initAssemblyFile();
    generateModule();
    generateText();
    completeFile();
}