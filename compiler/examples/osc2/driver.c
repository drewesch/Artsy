#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "ircode.h"
#include "parser.h"
#include "webgen.h"

// Starts the whole program
int main(int argc, char**argv){
  // If the program initialization is valid, allow the program to run
  if (argc > 1){
    FILE*fd=fopen(argv[1],"r");

    // Run the parser
    // If it returns an error, exit the program with a warning number
    if(parser_main(fd) != 0){
      return 1;
    }

    // Call the ircode generator
    generateIRCode();

    // Call the optimizer to generate optimized IRcode
    // Use this function to generate IRcode that the WAT code generator will actually use
    // Moreover, use this function to compare unoptimized IRcode to optimized IRcode
    // generateIRCodeOptimized(); 

    // Generate optimized WAT code as a .wat file
    // This function is in webgen.c and webgen.h
    // Once this process completes, the next command in the makefile compiles the .wat to a .wasm file
    // After the .wasm file is generated, the changes will be immediately live
    // on testProg.html using the LiveServer extension or on artsy-project.com
    // generateWATcode();

    // End the program
    return 0;
  }
}