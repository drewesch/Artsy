#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "ircode.h"
#include "parser.h"
#include "codegen.h"




// Starts the whole program
int main(int argc, char**argv){
  // If the program initialization is valid, allow the program to run
  if (argc > 1){
    FILE*fd=fopen(argv[1],"r");
    // What does this do?----------------
    // Albert
    if(parser_main(fd) != 0){
      return 1;
    }

    // Call the ircode generator
     //generateIRCode();

    // Call the optimizer to generate optimized IRcode
    // Use this function to generate IRcode that the MIPS code generator will actually use
    // Moreover, use this function to compare unoptimized IRcode to optimized IRcode
    // generateIRCodeOptimized(); 

    // Generate optimized MIPS code as a .asm file
    // This function is in codegen.c and codegen.h
    //generateMIPScode();

    // End the program
    return 0;
  }
}