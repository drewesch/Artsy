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
char code[1000];

// Function to open the files for IRcodeOptimized.ir and WATcode.asm
// Required before generating any WAT code
void initAssemblyFile() {
  
 printf("\nOpening WAT Code file\n\n"); // Creates a WAT file with a generic header that needs to be in every file
 IRcode = fopen("IRcodeOptimized.ir", "r");
 WATcode = fopen("WATcode.wat", "w");
    
}

void generateModule() {
    fprintf(WATcode, "(module\n");
    fprintf(WATcode, "\t(import \"env\" \"jsprint\" (func $jsprint (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"newline\" (func $newline))\n");
    fprintf(WATcode, "\t(import \"env\" \"writeconsole\" (func $writeconsole (param i32)))\n");
    fprintf(WATcode, "\t(memory $0 1)\n");
    fprintf(WATcode, "\t(export \"pagememory\" (memory $0))\n\n");
    fprintf(WATcode, "\t(func $main\n");
}

// Function to generate the data section in WAT
// Using all declared variables in the IRcode (e.g. int x, int y, int z)
// Generate list of data variables for easier code generation
// Acts as a helper function for managing temp variable declarations
void generateDataVariables() {
    // Check the whole IRCodeOptimized.ir file
    // For each variable declared, add a .word
    while ( fgets(code, 1000, IRcode) != NULL){
        if (strncmp(code, "type ", 5) == 0){
            char *variable = code + 9;
            variable[strlen(variable) - 1] = 0;
            fprintf(WATcode, "\t\t(local $%s i32)\n", variable);
        }
        else if (strncmp(code, "#", 1) == 0){ // do nothing
            
        }
        else if (strncmp(code, "\n", 1) == 0){ // ignore 

        }
        else {
            // Don't add anything if it isn't a variable declaration
            break;
        }
    }

}

// Standard function to generate a new line of code
// Used to print neater output in WAT
void printNewLine() {
    fprintf(WATcode, "\t\t;; Print New Line\n");
    fprintf(WATcode, "\t\t(call $newline)\n");
    fprintf(WATcode, "\t\t;; ---------\n"); 
}

// Standard function to generate the main section and text section
// Required before generating any WAT statements
void generateTextSection() {
    // Loop through each line in the code and generate WAT for each valid statement
    do {
        // If the IRcode calls a write/output statement
        if (strncmp(code, "output ", 7) == 0){
            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;
            // printf("Variable: %s\n", variable);
            int value = 0;
            fprintf(WATcode, "\t\t;; %s \n", code);

            // If write statement uses a NUMBER
            if (isdigit(variable[0])){
                value = atoi(variable);
                // Find upper and lower using the variable value
                int lower = value & 0xffff;
                int upper = (value & 0xffff0000) >> 16;

                // Print WAT code using upper and lower value
                // By default, this will be an integer write statement. However, this approach will be updated for the next iteration.

                fprintf(WATcode, "\t\t(call $writeconsole\n");
                fprintf(WATcode, "\t\t\t(i32.const %s)\n", lower);
                fprintf(WATcode, "\t\t)\n");

                printNewLine();
            }
            // Else, the variable uses a temporary register
            else{
                fprintf(WATcode, "\t\t(call $writeconsole\n");
                fprintf(WATcode, "\t\t\t(local.get $%s)\n", variable);
                fprintf(WATcode, "\t\t)\n");
                printNewLine();
            }
        }
        // If the file contains a newline, ignore the statement
        else if (strncmp(code, "\n", 1) == 0){//ignore
        }
        // If the file contains a comment, ignore the statement
        else if (strncmp(code, "#", 1) == 0){//ignore
        }
        // If the IRcode calls an assignment statement
        else if (strncmp(code, "assign ", 7) == 0){
            // Declare start and end chars
            char*start = code+7;
            char*end = start;
            
            // While a ":" is not encountered, loop through and assign the corresponding variable in WAT
            while (*end != ':') end++;
            char variable [256]; 
            strncpy(variable, start, (end - start));
            variable[end - start] = 0;
            int value = atoi(++end);
            // Assign variable and number
            int lower = value & 0xffff;
            int upper = (value & 0xffff0000) >> 16;

            // Generate WAT code using code, upper, lower, and variable
            fprintf(WATcode, "\t\t;; %s\n", code);
            fprintf(WATcode, "\t\t(local.set $%s\n", variable);
            fprintf(WATcode, "\t\t\t(i32.const %d)\n", lower);
            fprintf(WATcode, "\t\t)\n");

        }
        else { //assignment statement //handles these things for printing //handle the last statment 
            printf("code: %s", code);
        }
    // Loop element for all lines in code[]
    } while (fgets(code, 1000, IRcode) != NULL);

}

// Function to end WAT generation once all commands are printed from the IRcodeOptimized.ir file
void completeFile() {
    // Print ending WAT commands to the file    
    fprintf(WATcode, "\t)\n");
    fprintf(WATcode, "\t(export \"main\" (func $main))\n");
    fprintf(WATcode, ")\n");

    // Closes all files once complete
    fclose(IRcode);
    fclose(WATcode);
}


// Main driver function to generate all WAT code
void generateWATcode() {
    initAssemblyFile();
    generateModule();
    generateDataVariables();
    generateTextSection();
    completeFile();
}