// Set of functions to emit MIPS code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "codegen.h"

// Initialize WATcode file, IRcode file, and other required variables
FILE * WATcode;
int startASM = 0;
FILE * IRcode; // added for code generator 
char code[1000];

// Function to open the files for IRcodeOptimized.ir and WATcode.asm
// Required before generating any MIPS code
void initAssemblyFile(){
  
 printf("\nOpening WAT Code file\n\n"); // Creates a MIPS file with a generic header that needs to be in every file
 IRcode = fopen("IRcodeOptimized.ir", "r");
 WATcode = fopen("WATcode.wat", "w");
    
}

// Function to generate the data section in MIPS
// Using all declared variables in the IRcode (e.g. int x, int y, int z)
// Generate list of data variables for easier code generation
// Acts as a helper function for managing temp variable declarations
void generateDataSection(){
    // Print ".data"
    fprintf(WATcode, ".data\n");

    // Check the whole IRCodeOptimized.ir file
    // For each variable declared, add a .word
    while ( fgets(code, 1000, IRcode) != NULL){
        if (strncmp(code, "type ", 5) == 0){
            char *variable = code + 9;
            variable[strlen(variable) - 1] = 0;
            fprintf(WATcode, "%s: .word 0\n", variable);
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

    // End by printing a standard variable called NewLine as a asciiz type
    fprintf(WATcode, "NewLine: .asciiz \"\\n\"\n");

}

// Standard function to generate a new line of code
// Used to print neater output in MIPS
void printNewLine(){
    fprintf(WATcode, "#-------- Print New Line\n");
    fprintf(WATcode, "la $a0, NewLine\n");
    fprintf(WATcode, "li $v0, 4\n");   
    fprintf(WATcode, "syscall\n");
    fprintf(WATcode, "#-----------------------\n"); 
}

// Standard function to generate the main section and text section
// Required before generating any MIPS statements
void generateTextSection(){
    fprintf(WATcode, ".text\n");
    fprintf(WATcode, ".globl main\n");
    fprintf(WATcode, "main:\n");
    fprintf(WATcode, "# -----------------------\n");

    // Loop through each line in the code and generate MIPS for each valid statement
    do {
        // If the IRcode calls a write/output statement
        if (strncmp(code, "output ", 7) == 0){
            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;
            // printf("Variable: %s\n", variable);
            int value = 0;
            fprintf(WATcode, "# %s \n", code);

            // If write statement uses a NUMBER
            if (isdigit(variable[0])){
                value = atoi(variable);
                // Find upper and lower using the variable value
                int lower = value & 0xffff;
                int upper = (value & 0xffff0000) >> 16;
                // fprintf(WATcode, "syscall\n");
                // Print MIPS code using upper and lower value
                // By default, this will be an integer write statement. However, this approach will be updated for the next iteration.
                fprintf(WATcode, "lui $a0, %d\n", upper);  
                fprintf(WATcode, "ori $a0, $a0, %d\n", lower);  
                fprintf(WATcode, "li $v0, 1\n");
                fprintf(WATcode, "syscall\n");
                printNewLine();
            }
            // Else, the variable uses a temporary register
            // Print using the .word statement defined earlier in the MIPS file
            else{
                fprintf(WATcode, "la $t0, %s\n", variable);
                fprintf(WATcode, "lw $a0, 0($t0)\n");
                fprintf(WATcode, "li $v0, 1\n");
                fprintf(WATcode, "syscall\n");
                printNewLine();
            }
            // fprintf(WATcode, "%s: .word\n", variable);
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
            
            // While a ":" is not encountered, loop through and assign the corresponding variable in MIPS
            while (*end != ':') end++;
            char variable [256]; 
            strncpy(variable, start, (end - start));
            variable[end - start] = 0;
            int value = atoi(++end);
            // Assign variable and number
            int lower = value & 0xffff;
            int upper = (value & 0xffff0000) >> 16;
            // fprintf(WATcode, "syscall\n");
            // Generate MIPS code using code, upper, lower, and variable
            fprintf(WATcode, "#----------%s \n", code);
            fprintf(WATcode, "lui $a0, %d\n", upper);  
            fprintf(WATcode, "ori $a0, $a0, %d\n", lower);
            fprintf(WATcode, "la $t0, %s\n", variable);
            fprintf(WATcode, "sw $a0, 0($t0)\n");
            fprintf(WATcode, "#---------- \n");
        }
        else { //assignment statement //handles these things for printing //handle the last statment 
            printf("code: %s", code);
        }
    // Loop element for all lines in code[]
    } while (fgets(code, 1000, IRcode) != NULL);

}

// Function to end MIPS generation once all commands are printed from the IRcodeOptimized.ir file
void compleateAssemlyFile(){
    // Print ending MIPS commands to the file
    fprintf(WATcode, "li $v0, 10\n");
    fprintf(WATcode, "syscall\n");
    fprintf(WATcode, "# ----------------------- End of Main.\n");

    // Closes all files once complete
    fclose(IRcode);
    fclose(WATcode);
}


// Main driver function to generate all MIPS code
void generateWATcode(){
    initAssemblyFile();
    generateDataSection();
    generateTextSection();
    compleateAssemlyFile();
}