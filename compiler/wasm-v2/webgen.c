// Set of functions to emit WAT code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "webgen.h"

// Initialize WATcode file, IRcode file, and other required variables
FILE * WATcode;
int startASM = 0;
FILE * IRcode; // added for code generator 
char code[10000];

// Variables to detect if declared types and params are within a function
int isGlobal = 1;
int inParams = 0;

// Global return type variable for a given function
char * returnType = "";

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

// Standard function to generate a new line of code
// Used to print neater output in WAT
void printNewLine() {
    fprintf(WATcode, "\t\t;; Print New Line\n");
    fprintf(WATcode, "\t\t(call $newline)\n");
}

// Standard function to generate the main section and text section
// Required before generating any WAT statements
void generateText() {
    // Loop through each line in the code and generate WAT for each valid statement
    while (fgets(code, 10000, IRcode) != NULL) {
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
        else if (strncmp(code, "param ", 6) == 0) {
            char * nextPart = code + 6;
            nextPart[strlen(nextPart) - 1] = 0;

            // Get the rest of the string
            char * newType = getWATType(nextPart);
            int moveAmount = getMoveAmount(nextPart);

            char * variable = nextPart + moveAmount;

            fprintf(WATcode, "(param $%s %s) ", variable, newType);
        }
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

            fprintf(WATcode, "\t(export \"%s\" (func $%s))\n", variable, variable);
            fprintf(WATcode, "\t(func $%s ", variable);
        }
        else if (strncmp(code, "exit", 4) == 0) {
            // Set all types after this to global declarations
            isGlobal = 1;

            fprintf(WATcode, "\t)\n");
        }
        else if (strncmp(code, "return ", 7) == 0) {
            // Output comment
            fprintf(WATcode, "\t\t;; %s", code);

            // Get variable name
            char * variable = code + 7;
            variable[strlen(variable) - 1] = 0;

            // Print function ending code
            fprintf(WATcode, "\t\t(local.get $%s)\n", variable);
        }
        else if (strncmp(code, "output ", 7) == 0) { // If the IRcode calls a write/output statement
            // Set function return type first if this is the first call in a function
            if (inParams) {
                inParams = 0;
                fprintf(WATcode, "(result %s)\n", returnType);
            }

            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;
            // printf("Variable: %s\n", variable);
            int value = 0;
            fprintf(WATcode, "\t\t;; %s \n", code);

            // If write statement uses a NUMBER
            if (isdigit(variable[0])) {
                value = atoi(variable);
                // Find upper and lower using the variable value
                int lower = value & 0xffff;
                int upper = (value & 0xffff0000) >> 16;

                // Print WAT code using upper and lower value
                // By default, this will be an integer write statement. However, this approach will be updated for the next iteration.

                fprintf(WATcode, "\t\t(call $writeconsole\n");
                fprintf(WATcode, "\t\t\t(i32.const %s)\n", lower);
                fprintf(WATcode, "\t\t)\n");
            } else { // Else, the variable uses a temporary register
                fprintf(WATcode, "\t\t(call $writeconsole\n");
                fprintf(WATcode, "\t\t\t(local.get $%s)\n", variable);
                fprintf(WATcode, "\t\t)\n");
                                
            }
        }
        else if (strncmp(code, "nextline", 8) == 0) { // If the code contains a writeln statement, print a new line
            // Call print line function
            printNewLine();
        }
        // If the file contains a newline or a comment, ignore the statement
        else if (strncmp(code, "\n", 1) == 0 || strncmp(code, "#", 1) == 0){
        }
        // If the IRcode calls an assignment statement
        else {
            // Algorithm
            // Step 1: Break apart the line into an iterable array of strings
            // Set the delimiter for separating terms by word
            char **strArr;
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
                // If a "+" exists, then call the MIPS add operation
                printf("Add Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
            }
            // Sub operation
            else if (strcmp(strArr[3], "-") == 0) {
                // If a "+" exists, then call the MIPS add operation
                printf("Sub Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
            }
            // Mul operation
            else if (strcmp(strArr[3], "*") == 0) {
                // If a "+" exists, then call the MIPS add operation
                printf("Mul Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
            }
            // Div operation
            else if (strcmp(strArr[3], "/") == 0) {
                // If a "+" exists, then call the MIPS add operation
                printf("Div Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
            }
            // Exponent operation
            else if (strcmp(strArr[3], "^") == 0) {
                // If a "+" exists, then call the MIPS add operation
                printf("Exponent Op\n");
                // emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
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