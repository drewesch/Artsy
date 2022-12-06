// Set of functions to emit WAT code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "webgen.h"
#include "semantic.h"
#include "symbolTable.h"

// Initialize WATcode file, IRcode file, MAINcode file, and other required variables
FILE * WATcode;
FILE * IRcode;
FILE * MAINcode;
FILE * VARScode;
FILE * LOCALcode;
char code[10000];

// Function to open the files for IRcodeOptimized.ir and WATcode.asm
// Required before generating any WAT code
void initAssemblyFile() {
    printf("\nOpening WAT Code file\n\n"); // Creates a WAT file with a generic header that needs to be in every file
    IRcode = fopen("IRcodeOptimized.ir", "r");
    WATcode = fopen("WATcode.wat", "w");
    MAINcode = fopen("MAINcode.wat", "w");
    VARScode = fopen("VARScode.wat", "w");
    LOCALcode = fopen("LOCALcode.wat", "w");
}

// Function to generate the initial set of lines required for proper WebAssembly output
void generateModule() {
    fprintf(WATcode, "(module\n");
    fprintf(WATcode, "\t;; WAT Setup Declarations\n");
    fprintf(WATcode, "\t(import \"env\" \"jsprint\" (func $jsprint (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"newline\" (func $newline))\n");
    fprintf(WATcode, "\t(import \"env\" \"writeconsoleInt\" (func $writeconsoleInt (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"writeconsoleFloat\" (func $writeconsoleFloat (param f32)))\n");
	fprintf(WATcode, "\t(import \"env\" \"writeconsoleString\" (func $writeconsoleString (param i64)))\n");
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

// Standard function to generate the main section and text section
// Required before generating any WAT statements
void generateText() {
    // Variables to detect if declared types and params are within a function
    int isGlobal = 1;
    int inParams = 0;

    // Current operation variable
    char * currOp = "";

    // Global return type variable for a given function
    char * returnType = "";

    // Current scope variable
    char * currScope = "global";

    // Loop through each line in the code and generate WAT for each valid statement
    while (fgets(code, 10000, IRcode) != NULL) {
        // Case for type declarations
        printf("%s", code);
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

            // Print declaration to WATcode
            if (isGlobal) {
                char * placeholder = "0";
                if (strncmp(newType, "f32", 3) == 0) {
                    placeholder = "0.0";
                }

                fprintf(WATcode, "\t(global $%s (mut %s) (%s.const %s))\n", variable, newType, newType, placeholder);
            } else {
                if (strncmp(currScope, "global", 6) == 0) {
                    fprintf(VARScode, "\t\t(local $%s %s)\n", variable, newType);
                } else {
                    fprintf(WATcode, "\t\t(local $%s %s)\n", variable, newType);
                }
            }
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
            currScope = malloc(strlen(variable)*sizeof(char));
            strcpy(currScope, variable);

            // Start function declaration
            fprintf(WATcode, "\t(func $%s ", variable);
        }
        // Case for exiting functions
        else if (strncmp(code, "exit", 4) == 0) {
            // Set all types after this to global declarations
            isGlobal = 1;

            // Load in everything from the local file
            generateLocalOperations();

            // End function declaration
            fprintf(WATcode, "\t)\n");
            fprintf(WATcode, "\t(export \"%s\" (func $%s))\n", currScope, currScope);

            // Set scope back to global
            currScope = "global";
        }
        // Case for return statements in functions
        else if (strncmp(code, "return ", 7) == 0) {
            // Set function return type first if this is the first call in a function
            if (inParams) {
                inParams = 0;
                fprintf(WATcode, "(result %s)\n", returnType);
            }

            // Get variable name
            char * variable = code + 7;
            variable[strlen(variable) - 1] = 0;

            // Print function ending code
            
            // If it's not a variable, return the value as it's WAT type
            if (strncmp(getPrimaryType(variable), "var", 3) != 0) {
                // Get WAT Type for printing to the console
                char * WATType = getWATType(getPrimaryType(variable));
                fprintf(LOCALcode, "\t\t(return (%s.const %s))", WATType, variable);
            } else { // Else, it is a variable
                fprintf(LOCALcode, "\t\t(return (local.get $%s))", variable);      
            }
        }
        // If the IRcode calls a write/output statement
        else if (strncmp(code, "output ", 7) == 0) {
            // Set function return type first if this is the first call in a function
            if (inParams) {
                inParams = 0;
                fprintf(WATcode, "(result %s)\n", returnType);
            }

            

            char *variable = code + 7; 
            variable[strlen(variable) - 1] = 0;

            // If the write statement does not use a variable
            if (strncmp(getPrimaryType(variable), "var", 3) != 0) {
                // Get WAT Type for printing to the console
                char * WATType = getWATType(variable);

                if (!isGlobal) { // If its within a function, write to WATcode
                    if (strncmp(WATType, "i32", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleInt\n");
                    } else if (strncmp(WATType, "f32", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleFloat\n");
                    } else if (strncmp(WATType, "i64", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleString\n");
                    }
                    fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", WATType, variable);
                    fprintf(LOCALcode, "\t\t)\n");
                }
                // Else, write to the MAINcode file
                else {
                    if (strncmp(WATType, "i32", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleInt\n");
                    } else if (strncmp(WATType, "f32", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleFloat\n");
                    } else if (strncmp(WATType, "i64", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleString\n");
                    }
                    fprintf(MAINcode, "\t\t\t(%s.const %s)\n", WATType, variable);
                    fprintf(MAINcode, "\t\t)\n");
                }

            } else { // Else, the variable uses a variable
                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(variable, "global")) {
                    scopeType = "local";
                }

                char * WATType = getWATType(getItemType(variable, currScope));

                if (!isGlobal) { // If its within a function, write to WATcode
                    if (strncmp(WATType, "i32", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleInt\n");
                    } else if (strncmp(WATType, "f32", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleFloat\n");
                    } else if (strncmp(WATType, "i64", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $writeconsoleString\n");
                    }
                    fprintf(LOCALcode, "\t\t\t(%s.get $%s)\n", scopeType, variable);
                    fprintf(LOCALcode, "\t\t)\n");
                }
                // Else, write to the MAINcode file
                else {
                    if (strncmp(WATType, "i32", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleInt\n");
                    } else if (strncmp(WATType, "f32", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleFloat\n");
                    } else if (strncmp(WATType, "i64", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $writeconsoleString\n");
                    }
                    fprintf(MAINcode, "\t\t\t(%s.get $%s)\n", scopeType, variable);
                    fprintf(MAINcode, "\t\t)\n");
                }
            }
        }
        // If the code contains a writeln statement, print a new line
        else if (strncmp(code, "nextline", 8) == 0) {
            // Call print line function
            if (isGlobal) {
                fprintf(MAINcode, "\t\t(call $newline)\n");
            } else {
                fprintf(LOCALcode, "\t\t(call $newline)\n");
            }
        }
        // Case for handling suboperation states
        else if (strncmp(code, "subop ", 6) == 0) {
            // Get variable name
            char * variable = code + 6;
            variable[strlen(variable) - 1] = 0;

            // Set current operation
            currOp = malloc(strlen(variable)*sizeof(char));
            strcpy(currOp, variable);
        }
        // If the file contains a newline or a comment, ignore the statement
        else if (strncmp(code, "\n", 1) == 0 || strncmp(code, "#", 1) == 0){
        }
        // If the IRcode declares an assignment, operation, or call statement
        else {
            // Algorithm
            // Step 1: Break apart the line into an iterable array of strings
            // Set the delimiter for separating terms by word
            char ** strArr;
            int maxArrSize = 1000;
            strArr = malloc(maxArrSize * sizeof(char *));
            char delimiter[] = " ";
            char * token = strtok(code, delimiter);

            // Add all tokens to a string array
            int lenIndex = 0;
            while(token != NULL) {
                // Assign to string array
                strArr[lenIndex] = token;
                lenIndex++;
                token = strtok(NULL, delimiter);
            }

            // Remove "\n" character from the last string
            lenIndex--;
            strArr[lenIndex][strlen(strArr[lenIndex])-1] = '\0';

            // Build out case statements for the supported features

            // a. Assignment Statements
            // - Total Strings = 3
            // - STR1 = Var, STR2 = "=", STR3 = primary/variable

            // Assignment Operation
            if (strArr[3] == NULL) {
                // Set function return type first if this is the first call in a function
                if (inParams) {
                    inParams = 0;
                    fprintf(WATcode, "(result %s)\n", returnType);
                }

                // Declare all three variables
                char * assignVar = strArr[0];
                char * var2 = strArr[2];
                
                // Declare operation type variable
                char * opType;

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(strArr[0], "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Output the assignVar call line
                if (isGlobal) { // If it's a temp variable in global, print to MAINcode
                    fprintf(MAINcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                }
                // Else, print to WATcode
                else {
                    fprintf(LOCALcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (strncmp(getPrimaryType(strArr[2]), "var", 3) == 0) {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    if (isGlobal) { // If it's a temp variable in global, print to MAINcode
                        fprintf(MAINcode, "\t\t\t(%s.get $%s)\n", varScopeType, var2);
                    }
                    // Else, print to WATcode
                    else {
                        fprintf(LOCALcode, "\t\t\t(%s.get $%s)\n", varScopeType, var2);
                    }
                } else {
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t(%s.const %s)\n", opType, var2);
                    } else {
                        fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", opType, var2);
                    }
                }

                // End assignment statement
                if (isGlobal) { // If it's a temp variable in global, print to MAINcode
                    fprintf(MAINcode, "\t\t)\n");
                }
                // Else, print to WATcode
                else {
                    fprintf(LOCALcode, "\t\t)\n");
                }
            }

            // b. Function Calls
            // - Contains a "call" token at index 3
            // - Always acts as an assignment statement, but calls a function register with a set of parameters

            else if (strncmp(strArr[2], "call", 4) == 0) {
                // Declare all three variables
                char * assignVar = strArr[0];
                char * funcVar = strArr[3];
                
                // Declare operation type variable
                char * opType;

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(strArr[0], "global")) {
                    scopeType = "local";
                }

                // Determine the operation type
                opType = getWATType(currOp);

                // Set function return type first if this is the first call in a function
                if (inParams) {
                    inParams = 0;
                    fprintf(WATcode, "(result %s)\n", returnType);
                }
                // Else, print a temporary variable declaration line with the WAT type
                else {
                    if (isGlobal) {
                        fprintf(VARScode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                    } else {
                        fprintf(WATcode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                    }
                }

                // Output the assignVar call line
                if (isGlobal) {
                    fprintf(MAINcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                } else {
                    fprintf(LOCALcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                }

                // Output function call lines
                // If there are no arguments after the "args" token, generate the call on a single line
                if (strArr[5] == NULL) {
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t(call $%s)\n", funcVar);
                    } else {
                        fprintf(LOCALcode, "\t\t\t(call $%s)\n", funcVar);
                    }
                }
                // Otherwise, generate the call with the list of parameters
                else {
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t(call $%s\n", funcVar);
                    } else {
                        fprintf(LOCALcode, "\t\t\t(call $%s\n", funcVar);
                    }


                    // Loop through and add all available parameters as lines under the function call
                    // Determine if each one is a variable or not, and assign accordingly
                    int index = 5;
                    while (strArr[index] != NULL) {
                        char * callVar = strArr[index];
                        
                        // If var references an actual variable, add a dollar sign in front and build the line accordingly
                        if (strncmp(getPrimaryType(strArr[index]), "var", 3) == 0) {
                            // Determine if the variable is global or variable
                            char * varScopeType = "global";

                            if (!found(strArr[index], "global")) {
                                varScopeType = "local";
                            }

                            if (isGlobal) {
                                fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                            } else {
                                fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                            }
                            
                        } else {
                            opType = getWATType(getPrimaryType(strArr[index]));

                            if (isGlobal) {
                                fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, callVar);
                            } else {
                                fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, callVar);
                            }
                        }
                        index++;
                    }

                    // End the call statement with parameters
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t)\n");
                    } else {
                        fprintf(LOCALcode, "\t\t\t)\n");
                    }
                }

                // End assignment statement
                if (isGlobal) {
                    fprintf(MAINcode, "\t\t)\n");
                } else {
                    fprintf(LOCALcode, "\t\t)\n");
                }
                
            }

            // c. Basic Operations
            // - Total Strings = 5
            // - STR1 = Var, STR2 = "=", STR3 = primary/variable,
            // - STR4 = Operand, STR5 = primary/variable

            else if (strncmp(strArr[3], "+", 1) == 0 || strncmp(strArr[3], "-", 1) == 0 || strncmp(strArr[3], "*", 1) == 0 || strncmp(strArr[3], "/", 1) == 0) {
                // Declare all three variables
                char * assignVar = strArr[0];
                char * var1 = strArr[2];
                char * var2 = strArr[4];
                
                // Declare operation type variable
                char * opType;

                // Determine if the variable is global or variable
                char * scopeType = "global";

                if (!found(assignVar, "global")) {
                    scopeType = "local";
                }
                // Determine the operation type
                opType = getWATType(currOp);

                // If not in parameters, print a temporary variable declaration line with the WAT type
                if (!inParams) {
                    if (isGlobal) {
                        fprintf(VARScode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                    } else {
                        fprintf(WATcode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                    }
                    
                }

                // Output the variable set line
                if (isGlobal) {
                    fprintf(MAINcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                } else {
                    fprintf(LOCALcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
                }

                // Determine operation WAT call
                // "+" = "add", "-" = sub, "*" = mul, and "/" = "div" or "div_s" 
                char * opCall = "";
                char * specialOp = "";

                if (strncmp(strArr[3], "+", 1) == 0) {
                    opCall = "add";
                } else if (strncmp(strArr[3], "-", 1) == 0) {
                    opCall = "sub";
                } else if (strncmp(strArr[3], "*", 1) == 0) {
                    opCall = "mul";
                } else if (strncmp(strArr[3], "/", 1) == 0) {
                    opCall = "div";
                }

                // Special case for division
                // If the operation is an integer, specify "div_s"
                if (strncmp(opCall, "div", 3) == 0 && strncmp(opType, "i32", 3) == 0) {
                    specialOp = "_s";
                }

                // Start the operation call
                if (isGlobal) {
                    fprintf(MAINcode, "\t\t\t(%s.%s%s\n", opType, opCall, specialOp);
                } else {
                    fprintf(LOCALcode, "\t\t\t(%s.%s%s\n", opType, opCall, specialOp);
                }

                // Declare variables for the operation

                // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
                if (strncmp(getPrimaryType(strArr[2]), "var", 3) == 0) {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[2], "global")) {
                        varScopeType = "local";
                    }

                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var1);
                    } else {
                        fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var1);
                    }
                } else {
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, var1);   
                    } else {
                        fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, var1);
                    }
                }

                // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
                if (strncmp(getPrimaryType(strArr[4]), "var", 3) == 0) {
                    // Determine if the variable is global or variable
                    char * varScopeType = "global";

                    if (!found(strArr[4], "global")) {
                        varScopeType = "local";
                    }

                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var2);
                    } else {
                        fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var2);
                    }
                } else {
                    if (isGlobal) {
                        fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, var2);
                    } else {
                        fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, var2);
                    }
                }

                // End the operation call
                if (isGlobal) {
                    fprintf(MAINcode, "\t\t\t)\n");
                    fprintf(MAINcode, "\t\t)\n");
                } else {
                    fprintf(LOCALcode, "\t\t\t)\n");
                    fprintf(LOCALcode, "\t\t)\n");
                }
            }

            // Free specific string index for loop reuse
            strArr[3] = "\0";
            
        }
    }

}

void generateLocalOperations() {
    // Temp variable
    char tempLocal[10000];

    // Char pointer
    char ch = '0';

    // Open LOCALcode file in read mode
    fclose(LOCALcode);
    LOCALcode = fopen("LOCALcode.wat", "r");

    // Read all WAT code that was inserted into the local file
    while (ch != EOF) {
        ch = fgetc(LOCALcode);
        if (ch == EOF) {
            break;
        }
        fprintf(WATcode, "%c", ch);
    }

    // End the local function
    fprintf(WATcode, "\t\t\n");

    // Close file and reopen in write mode
    fclose(LOCALcode);
    LOCALcode = fopen("LOCALcode.wat", "w");
}

void generateMainVars() {
    // Temp variable
    char tempVars[10000];

    // Char pointer
    char ch = '0';

    // Open LOCALcode file in read mode
    fclose(VARScode);
    VARScode = fopen("VARScode.wat", "r");

    // Read all WAT code that was inserted into the vars file
    // while (fgets(tempVars, 10000, VARScode) != NULL) {
    //     fprintf(WATcode, "%s", tempVars);
    // }

    while (ch != EOF) {
        ch = fgetc(VARScode);
        if (ch == EOF) {
            break;
        }
        fprintf(WATcode, "%c", ch);
    }

    fprintf(WATcode, "\n");

    // Close file
    fclose(VARScode);
}

void generateMain() {
    // Char pointer
    char ch = '0';

    // Open MAINcode file in read mode
    fclose(MAINcode);
    MAINcode = fopen("MAINcode.wat", "r");

    // Generate the starting code for the main function
    fprintf(WATcode, "\t;; Start Main Function\n");
    fprintf(WATcode, "\t(func $main\n");

    // Generate main function vars
    generateMainVars();

    // Read all WAT code that was inserted into the main file
    // while (fgets(tempGlobal, 10000, MAINcode) != NULL) {
    //     fprintf(WATcode, "%s", tempGlobal);
    // }

    while (ch != EOF) {
        ch = fgetc(MAINcode);
        if (ch == EOF) {
            break;
        }
        fprintf(WATcode, "%c", ch);
    }

    // End the main function
    fprintf(WATcode, "\t)\n");
    fprintf(WATcode, "\t(start $main)\n");
}

// Function to end WAT generation once all commands are printed from the IRcodeOptimized.ir file
void completeFile() {
    // Print ending WAT commands to the file    
    fprintf(WATcode, ")\n");

    // Closes all files once complete
    fclose(IRcode);
    fclose(WATcode);
    fclose(MAINcode);
    fclose(LOCALcode);
}


// Main driver function to generate all WAT code
void generateWATcode() {
    initAssemblyFile();
    generateModule();
    generateText();
    generateMain();
    completeFile();
}