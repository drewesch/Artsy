// Set of functions to emit MIPS code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "codegen.h"

// Initialize MIPScode file, IRcode file, and other required variables
FILE * MIPScode;
int startASM = 0;
FILE * IRcode; // added for code generator 
char code[1000];

// Function to open the files for IRcodeOptimized.ir and MIPScode.asm
// Required before generating any MIPS code
void initAssemblyFile(){
  
 printf("\nOpening MIPS Code file\n\n"); // Creates a MIPS file with a generic header that needs to be in every file
 IRcode = fopen("IRcodeOptimized.ir", "r");
 MIPScode = fopen("MIPScode.asm", "w");
    
}

// Function to generate the data section in MIPS
// Using all declared variables in the IRcode (e.g. int x, int y, int z)
// Generate list of data variables for easier code generation
// Acts as a helper function for managing temp variable declarations
void generateDataSection(){
    // Print ".data"
    fprintf(MIPScode, ".data\n");

    // Check the whole IRCodeOptimized.ir file
    // For each variable declared, add a .word
    while ( fgets(code, 1000, IRcode) != NULL){
        if (strncmp(code, "type ", 5) == 0){
            char *variable = code + 9;
            variable[strlen(variable) - 1] = 0;
            fprintf(MIPScode, "%s: .word 0\n", variable);
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
    fprintf(MIPScode, "NewLine: .asciiz \"\\n\"\n");

}

// Standard function to generate a new line of code
// Used to print neater output in MIPS
void printNewLine(){
    fprintf(MIPScode, "#-------- Print New Line\n");
    fprintf(MIPScode, "la $a0, NewLine\n");
    fprintf(MIPScode, "li $v0, 4\n");   
    fprintf(MIPScode, "syscall\n");
    fprintf(MIPScode, "#-----------------------\n"); 
}

// Standard function to generate the main section and text section
// Required before generating any MIPS statements
void generateTextSection(){
    fprintf(MIPScode, ".text\n");
    fprintf(MIPScode, ".globl main\n");
    fprintf(MIPScode, "main:\n");
    fprintf(MIPScode, "# -----------------------\n");

    // Loop through each line in the code and generate MIPS for each valid statement
    do {
        // If the IRcode calls a write/output statement
        if (strncmp(code, "output ", 7) == 0){
            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;
            // printf("Variable: %s\n", variable);
            int value = 0;
            fprintf(MIPScode, "# %s \n", code);

            // If write statement uses a NUMBER
            if (isdigit(variable[0])){
                value = atoi(variable);
                // Find upper and lower using the variable value
                int lower = value & 0xffff;
                int upper = (value & 0xffff0000) >> 16;
                // fprintf(MIPScode, "syscall\n");
                // Print MIPS code using upper and lower value
                // By default, this will be an integer write statement. However, this approach will be updated for the next iteration.
                fprintf(MIPScode, "lui $a0, %d\n", upper);  
                fprintf(MIPScode, "ori $a0, $a0, %d\n", lower);  
                fprintf(MIPScode, "li $v0, 1\n");
                fprintf(MIPScode, "syscall\n");
                printNewLine();
            }
            // Else, the variable uses a temporary register
            // Print using the .word statement defined earlier in the MIPS file
            else{
                fprintf(MIPScode, "la $t0, %s\n", variable);
                fprintf(MIPScode, "lw $a0, 0($t0)\n");
                fprintf(MIPScode, "li $v0, 1\n");
                fprintf(MIPScode, "syscall\n");
                printNewLine();
            }
            // fprintf(MIPScode, "%s: .word\n", variable);
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
            // fprintf(MIPScode, "syscall\n");
            // Generate MIPS code using code, upper, lower, and variable
            fprintf(MIPScode, "#----------%s \n", code);
            fprintf(MIPScode, "lui $a0, %d\n", upper);  
            fprintf(MIPScode, "ori $a0, $a0, %d\n", lower);
            fprintf(MIPScode, "la $t0, %s\n", variable);
            fprintf(MIPScode, "sw $a0, 0($t0)\n");
            fprintf(MIPScode, "#---------- \n");
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
    fprintf(MIPScode, "li $v0, 10\n");
    fprintf(MIPScode, "syscall\n");
    fprintf(MIPScode, "# ----------------------- End of Main.\n");

    // Closes all files once complete
    fclose(IRcode);
    fclose(MIPScode);
}


// Main driver function to generate all MIPS code
void generateMIPScode(){
    initAssemblyFile();
    generateDataSection();
    generateTextSection();
    compleateAssemlyFile();
}

// OTHER TEST FUNCTIONS USED DURING THIS PROCESS

// void readMIPSFile() {
//     // Print final contents of the MIPS file
//     printf("\n\n--------------------MIPS Code Output------------------------\n\n");

//     char c;
//     c = fgetc(MIPScode);
//     while (c != EOF)
//     {
//         printf ("%c", c);
//         c = fgetc(MIPScode);
//     }

//     printf("\n\n--------------------MIPS Code End------------------------\n\n");
// }



// void emitMIPSAssignment(char * id1, char * id2){
//   // This is the temporary approach, until register management is implemented
//     if (startASM == 0) {
//         initAssemblyFile();
//         startASM = 1;
//     }

//     fprintf(MIPScode, "li $t1,%s\n", id1);
//     fprintf(MIPScode, "li $t2,%s\n", id2);
//     fprintf(MIPScode, "li $t2,$t1\n");
// }

// void emitMIPSConstantIntAssignment(char id1[50], char id2[50]){
//     // This is the temporary approach, until register management is implemented
//     // The parameters of this function should inform about registers
//     // For now, this is "improvised" to illustrate the idea of what needs to 
//     // be emitted in MIPS

//     // nextRegister = allocateRegister(id1);  // This is conceptual to inform what needs to be done later
//     if (startASM == 0) {
//         initAssemblyFile();
//         startASM = 1;
//     }

//     fprintf(MIPScode, "li $t0,%s\n", id2);
// }

// void emitMIPSWriteId(char * id){
//     // This is what needs to be printed, but must manage registers
//     // $a0 is the register through which everything is printed in MIPS
//     if (startASM == 0) {
//         initAssemblyFile();
//         startASM = 1;
//     }

//     fprintf(MIPScode, "li $a0,%s\n", id);
//     fprintf(MIPScode, "move $a0,%s\n", "$t0");
// }

// void emitMIPSAddOp(char * id1, char * id2) {
//     // Create an add statement
//     // Temporary approach until register management is implemented
//     if (startASM == 0) {
//         initAssemblyFile();
//         startASM = 1;
//     }

//     fprintf("add $t3, %s, %s", "$t1", "$t2");

// }

// void emitEndOfAssemblyCode(){
//     fprintf(MIPScode, "# -----------------\n");
//     fprintf(MIPScode, "#  Done, terminate program.\n\n");
//     fprintf(MIPScode, "li $v0,1   # call code for terminate\n");
//     fprintf(MIPScode, "syscall      # system call (terminate)\n");
//     fprintf(MIPScode, "li $v0,10   # call code for terminate\n");
//     fprintf(MIPScode, "syscall      # system call (terminate)\n");
//     fprintf(MIPScode, ".end main\n");
// }
    
\







//added for code Generator

    
// void generateMIPScode1() {
//     // Start MIPS file
//     initAssemblyFile();

//     // File reading variables
//     struct stat sb;
//     stat(IRcode, &sb);
//     char *file_contents = malloc(sb.st_size);

//     // String array variables
//     int maxWords = 1000;
//     char * strArr[maxWords];

//     // Read IRcode.ir
//     while (fscanf(IRcode, "%[^\n] ", file_contents) != EOF) {
//         printf("%s\n", file_contents);

//         // Set the delimiter for separating terms by word
//         int len = strlen(file_contents);
//         char delimiter[] = " ";
//         char *p = strtok(file_contents, delimiter);

//         // Add all words to a string array
//         int i = 0;
//         while(p != NULL) {
//             // Assign to string array
//             strArr[i] = p;
//             i++;
//             p = strtok(NULL, delimiter);
//         }

//         // Lowercase all chars in string
//         /*
//         int a = 0;
//         for (a = 0; a < 4; a++) {
//             // variable to iterate over ith string
//             int b = 0;
            
//             // jth character of string str[i] can be
//             // accessed from the location str[i]+j
//             while (*(strArr[a] + b) != '\0') {
//                 tolower(*(strArr[a]+b));
//                 b++;
//             }
//         }
//         */

//         // Form if statements to determine which MIPS operation should occur
//         if (strcmp(strArr[3], "+") == 0) {
//             // If a "+" exists, then call the MIPS add operation
//             printf("\nAdd Op\n");
//             emitMIPSAddOp(strArr[0], strArr[2], strArr[4]);
//         } else if (strcmp(strArr[0], "output") == 0) {
//             // If output and an expr exists, then call MIPS write operation 
//             printf("\nWrite Op\n");
//             emitMIPSWriteID(strArr[1], "1");
//         } else {
//             // Otherwise, it means that a temp variable, an "=" symbol, and some other expr is present
//             // Using this case, call the MIPS integer assignment
//             printf("\nInt Assign Op: %s\n", strArr[0]);
//             emitMIPSConstantIntAssignment(strArr[0], strArr[2]);
//         }
//     }

//     // End MIPS file
//     emitEndOfAssemblyCode();

//     // Confirm completed compilation
//     printf("\nCompiler completed!\n");
// }