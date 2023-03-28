// Set of functions to emit WAT code
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "webgen.h"
#include "helper.h"
#include "semantic.h"
#include "symbolTable.h"

// All file variables

// The WATcode file has the following purposes:
// 1. To place code directly first within the final file first (e.g., start module code)
// 2. To start functions, hold function parameters, and the function result parameter
// 3. To end functions with an export line
// 4. To declare global variables
// 5. To place temporary variables at the top of a local scope
// 6. Once the compilation process is complete, the other files will copy their contents into this file

FILE * WATcode; // Generates WATcode.wat

// All other files are helper files used in the compilation process
FILE * MAINcode; // File used to place code within the main function
FILE * VARScode; // File used to place variables at the top of the main function
FILE * LOCALcode; // File used to place code within a local scope
FILE * IRcode; // Optimized IRcode file

// Standard program variables
#define MAX_LINE_LENGTH 10000
#define MAX_ARRAY_LENGTH 5000
char varDelimiter[] = "[], ";
char * currScope;
char * prevScope;

// Variables to detect if declared types and params are within a function
int isMain = 1;
int inParams = 0;

// File functions

// Function to open the files for the WebAssembly Generator
// Required before generating any WAT code
void initAssemblyFile() {
    printf("\n----Generating WebAssembly Text File----\n\n"); // Creates a WAT file with a generic header that needs to be in every file
    IRcode = fopen("IRcodeOptimized.ir", "r");
    // IRcode = fopen("IRcode.ir", "r");
    WATcode = fopen("WATcode.wat", "w"); 
    MAINcode = fopen("MAINcode.wat", "w"); 
    VARScode = fopen("VARScode.wat", "w"); 
    LOCALcode = fopen("LOCALcode.wat", "w"); 
}

// Function to get file type from string
FILE * getFileType(char * fileType) {
    if (strncmp(fileType, "MAINcode", 8) == 0) {
        return MAINcode;
    } else if (strncmp(fileType, "LOCALcode", 9) == 0) {
        return LOCALcode;
    } else if (strncmp(fileType, "VARScode", 8) == 0) {
        return VARScode;
    } else if (strncmp(fileType, "WATcode", 7) == 0) {
        return WATcode;
    }
    return 0;
}

// Function to get file type from string
FILE * getHelperFileType(char * fileType) {
    if (strncmp(fileType, "MAINcode", 8) == 0) {
        return VARScode;
    } else if (strncmp(fileType, "LOCALcode", 9) == 0) {
        return WATcode;
    }
    return 0;
}

// String hash table functions

// Define iterator and default variables for updating array index calls by dedicated memory index
#define TABLE_SIZE 256
#define MAX_KEY_LENGTH 32
int currMaxStringIndex = 0;

// Define StringEntry struct for each table
struct StringEntry {
    char key[MAX_KEY_LENGTH];
    int value;
};

// Define the hash table
struct StringHashTable {
    struct StringEntry table[TABLE_SIZE];
};

// Get hash value from key
unsigned int hash(char* key) {
    unsigned int value = 0;
    for (int i = 0; i < strlen(key); i++) {
        value = value * 31 + key[i];
    }
    return value % TABLE_SIZE;
}

// Function to initialize a string hash table
void init(struct StringHashTable* dict) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        dict->table[i].key[0] = '\0';
        dict->table[i].value = 0;
    }
}

// Function to set an entry in a string hash table
void set(struct StringHashTable* dict, char* key, int value) {
    unsigned int index = hash(key);
    strcpy(dict->table[index].key, key);
    dict->table[index].value = value;
}

// Function to get an entry from a string hash table
int get(struct StringHashTable* dict, char* key) {
    unsigned int index = hash(key);
    if (strcmp(dict->table[index].key, key) == 0) {
        return dict->table[index].value;
    }
    return -1;
}

// Create String Hash Tables
struct StringHashTable stringAddresses;
struct StringHashTable stringSizes;

// Temporary Variable Table implementation

// Generate a struct for a temporary variable type
struct TempVar {
    char * name;
    char * type;
    char * kind;
};

// Generate a table of temporary variables
struct TempVar tempVarTable[TABLE_SIZE];

// Current temporary variable table index
int tempVarIndex = 0;

// Iterator variable for curr print string
int currPrintStrings = 0;

// Add temporary variable item to the table
char * addTempVarItem(char * name, char * type, char * kind) {
    // Assign memory to each item field
    tempVarTable[tempVarIndex].name = malloc(sizeof(char)*100);
    tempVarTable[tempVarIndex].type = malloc(sizeof(char)*100);
    tempVarTable[tempVarIndex].kind = malloc(sizeof(char)*100);
    
    // Copy string contents to struct field
    strncpy(tempVarTable[tempVarIndex].name, name, 100);
    strncpy(tempVarTable[tempVarIndex].type, type, 100);
    strncpy(tempVarTable[tempVarIndex].kind, kind, 100);

    // Increase Temp Variable Table Index
    tempVarIndex++;
}

// Check if item name is in the temporary variable table
int isTempVar(char * name) {
    for (int i = 0; i < tempVarIndex; i++) {
        if (strncmp(tempVarTable[i].name, name, 1000) == 0) {
            return 1;
		}
	}
    return 0;
}

// Get the temporary variable type based on the name
char * getTempVarType(char * name) {
    for (int i = 0; i < tempVarIndex; i++){
        if (strcmp(tempVarTable[i].name, name) == 0) {
            return tempVarTable[i].type;
		}
	}
    return 0;
}

// Get the temporary variable kind based on the name
char * getTempVarKind(char * name) {
    for (int i = 0; i < tempVarIndex; i++){
        if (strcmp(tempVarTable[i].name, name) == 0) {
            return tempVarTable[i].kind;
		}
	}
    return 0;
}

// Helper function to find scopeType
char * getScopeType(char * varName) {
    // Goal: Remove any "[]" characters from the string, create a new variable as a token
    char * varToken = malloc(100*sizeof(char));
    strcpy(varToken, varName);
    varToken = strtok(varToken, varDelimiter);

    // Return based on whether it is found in global or not
    return found(varToken, "global", 0) ? "global" : "local";
}

// WAT CODE PRINT MODULES

// Function to generate the initial set of lines required for proper WebAssembly output
void generateStartModule() {
    fprintf(WATcode, "(module\n");
    fprintf(WATcode, "\t;; WAT Setup Declarations\n");
    fprintf(WATcode, "\t(import \"env\" \"printInt\" (func $printInt (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"printFloat\" (func $printFloat (param f32)))\n");
	fprintf(WATcode, "\t(import \"env\" \"printString\" (func $printString (param i32)))\n");
    fprintf(WATcode, "\t(import \"env\" \"newline\" (func $newline))\n");
    fprintf(WATcode, "\t(memory $0 100)\n");
    fprintf(WATcode, "\t(export \"pagememory\" (memory $0))\n");
    fprintf(WATcode, "\t(func $create_array (param $size i32) (result i32) (local $ptr i32) (set_local $ptr (i32.const 0)) (block (loop $loop (br_if $loop (i32.eq (get_local $size) (i32.const 0))) (set_local $ptr (i32.add (get_local $ptr) (i32.const 4))) (set_local $size (i32.sub (get_local $size) (i32.const 1))))) (get_local $ptr))\n");
    fprintf(WATcode, "\t(export \"create_array\" (func $get_element))\n");
    fprintf(WATcode, "\t(func $get_element (param $ptr i32) (param $index i32) (result i32)(i32.load (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4)))))\n");
    fprintf(WATcode, "\t(export \"get_element\" (func $get_element))\n");
    fprintf(WATcode, "\t(func $set_element (param $ptr i32) (param $index i32) (param $value i32) (i32.store (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))) (get_local $value)))\n");
    fprintf(WATcode, "\t(export \"set_element\" (func $set_element))\n\n");
    fprintf(WATcode, "\t;; Artsy Program in WAT\n");
}

// Function module for handling addline statements
void generateAddLineWAT(FILE * printFile) {
    fprintf(printFile, "\t\t(call $newline)\n");
}

// Function module for declaring a variable
void generateVarDeclareStatementWAT(char * fileType, char * varType, char * varName) {
    // Step 1: Get the WAT Type, current scope, and files
    char * scopeType = getScopeType(varName);
    char * WATType = getWATType(getItemType(varName, currScope, 1));
    char * printFile = getFileType(fileType);
    char * helperFile = getHelperFileType(fileType);

    // Step 2: Handle standard variable declarations
    char * placeholder = calloc(100, sizeof(char));
    if (isMain) {
        // Find the placeholder value, based on whether its a float or int
        placeholder = strncmp(WATType, "f32", 3) == 0 ? "0.0" : "0";

        // Output the type to the global section
        fprintf(WATcode, "\t(global $%s (mut %s) (%s.const %s))\n", varName, WATType, WATType, placeholder);
    } else {
        fprintf(helperFile, "\t\t(local $%s %s)\n", varName, WATType);
    }
}

void generateArrayDeclareStatementWAT(char * fileType, char * varType, char * varName, char * arrSize) {
    // Step 1: Get file type
    char * printFile = getFileType(fileType);
    
    // Step 2: Create string variable in hash table
    int indexEntry = currMaxStringIndex;
    set(&stringAddresses, varName, indexEntry);
    set(&stringSizes, varName, atoi(arrSize));

    // Step 3: Update max string index for the next array entry
    currMaxStringIndex += atoi(arrSize);

    // Step 4: Generate WAT code for creating the new array
    fprintf(printFile, "\t\t(global.set $%s (call $create_array (i32.const %s)))", varName, arrSize);
}

// Function module for printing get statements for all variable types in WAT
void generateGetStatementWAT(FILE * printFile, char * varName) {
    // Step 1: Get the primary type, the length, and the scope type of the variable name
    char * primaryType = getPrimaryType(varName);
    int len = strlen(varName);
    char * scopeType = getScopeType(varName);

    // Step 2a: Print a const get statement if it's not a variable
    if (strncmp(primaryType, "var", 3) != 0) {
        // Get WAT Type
        char * WATType = getWATType(getPrimaryType(varName));

        // Print the statement
        fprintf(printFile, " (%s.const %s)", WATType, varName);
    }

    // Step 2b: Print an array index get statement if it's a variable with a "[]"
    else if (varName[len - 1] == ']') {
        // Goal: Return the get_element statement
        
        // Get the array variable and the index number
        char * arrName = calloc(100, sizeof(char));
        char * arrIndex = calloc(100, sizeof(char));

        // Assign variable name
        strcpy(arrName, varName);
        arrName = strtok(arrName, varDelimiter);

        // Assign array index variable
        strcpy(arrIndex, varName);
        arrIndex = strtok(arrIndex, varDelimiter);
        arrIndex = strtok(NULL, varDelimiter);
        sprintf(arrIndex, "%d", get(&stringAddresses, arrName) + arrIndex);

        // Print array index return statement
        fprintf(printFile, " (call $get_element (%s.get $%s) (i32.const %s))\n", scopeType, arrName, arrIndex);   
    }
    
    // Step 2c: Print a standard scope.get statment using the variable name
    else {
        fprintf(printFile, " (%s.get $%s)", scopeType, varName); 
    }
}

// Function module for handling parameter statements
void generateParameterWAT(FILE * printFile, char * type, char * varName) {
    fprintf(printFile, "(param $%s %s) ", varName, getWATType(type));
}

// Function module for handling return parameters
void generateResultWAT(FILE * printFile, char * returnType) {
    if (strncmp(returnType, "void", 4) != 0) {
        fprintf(printFile, "(result %s)\n", returnType);
    } else {
        fprintf(printFile, "\n");
    }
}

void generateReturnWAT(char * varName, char * scopeType) {
    // Create starting return statement in WAT
    fprintf(LOCALcode, "\t\t(return");

    // Generate the Get Statement in WAT
    generateGetStatementWAT(LOCALcode, varName);

    // Generate the return ending statement in WAT
    fprintf(LOCALcode, ")\n");    
}

void generateFunctionEndWAT(char * currScope) {
    fprintf(WATcode, "\t)\n\t(export \"%s\" (func $%s))\n", currScope, currScope);
}

// Function module for handling set_element statements in WAT strings
void setStringElementWAT(FILE * printFile, char * scopeType, char * arrName, int arrIndex, int arrVal) {
    fprintf(printFile, "\t\t(call $set_element (%s.get $%s) (i32.const %d) (i32.const %d))\n", scopeType, arrName, arrIndex, arrVal);
}

// Function module for handling printing solo string in Artsy code
void generatePrintStringWAT(char * strVal, char * fileType) {
    // Step 1: Generate a unique print variable name
    char * printVar = malloc(sizeof(char)*100);
    snprintf(printVar, 100, "_printstr_%d", currPrintStrings);
    currPrintStrings++; // Iterate current number of solo print strings in the program

    // Step 2: Convert the strVal to a usable format that supports escape characters
    int numEscapeCharacters = countEscapeChars(strVal);
    int printStrArrSize = strlen(strVal)-3-numEscapeCharacters; // Iterator variable to keep track of size
    char ** printStrArr = (char **) malloc(printStrArrSize * 10 * sizeof(char)); // Create string array variable

    // Allocate memory for each string
    for (int i = 0; i < printStrArrSize; i++){
        printStrArr[i] = (char *) malloc(20 * sizeof(char));
    }

    // Populate printStrArr variable
    int loopEscapeChars = 0; // Tracks total escape chars encountered
    for (int i = 1; i < printStrArrSize + 1; i++) {
        // Declare insertStr variable
        char * insertStr = malloc(sizeof(char)*20);

        // Form insertStr variable
        if (strVal[i+loopEscapeChars] == '\\') { // Case for an escape character
            snprintf(insertStr, 20, "\"%s\"", escapeCharType(strVal[i+1+loopEscapeChars]));
            loopEscapeChars++;
        } else { // Standard case (no escape character)
            snprintf(insertStr, 20, "\"%c\"", strVal[i+loopEscapeChars]);
        }

        // Put the insertStr variable into the string array
        strncpy(printStrArr[i-1], insertStr, 20);
    }

    // Step 3: Add the string to the string hash table
    int indexEntry = currMaxStringIndex;
    int strSize = printStrArrSize;
    set(&stringAddresses, printVar, indexEntry);
    set(&stringSizes, printVar, strSize);
    currMaxStringIndex += strSize; // Update max string index for the next array entry

    // Step 4: Print the whole string in one area

    // Step 4A: Determine filetype
    FILE * printFile = getFileType(fileType);
    FILE * helperFile = getHelperFileType(fileType);

    // Step 4B: Declare the new array variable
    char * scopeType = "local"; // Declare scope variable
    fprintf(helperFile, "\t\t(%s $%s i32)\n", scopeType, printVar);

    // Step 4C: Generate WAT code for creating the new array
    fprintf(printFile, "\t\t(%s.set $%s (call $create_array (i32.const %d)))\n", scopeType, printVar, strlen(strVal));

    // Step 4D: Set each element from the string into the new array using a for-loop
    for (int currArrIndex = 0; currArrIndex < strSize; currArrIndex++) {
        setStringElementWAT(printFile, scopeType, printVar, indexEntry + currArrIndex, atoi(convertToASCII(printStrArr[currArrIndex])));
    }

    // Step 4E: Print each element in the new string array using a for-loop
    for (int currArrIndex = 0; currArrIndex < strSize; currArrIndex++) {
        fprintf(printFile, "\t\t(call $printString (call $get_element (%s.get $%s) (i32.const %d)))\n", scopeType, printVar, indexEntry + currArrIndex);
    }

}

void generateComparisonWAT(FILE * printFile, char * leftTerm, char * compareType, char * rightTerm) {
    // Step 1: Determine WAT Type
    char * compareWATType = calloc(10, sizeof(char));
    if (found(leftTerm, currScope, 1)) {
        compareWATType = getWATType(getItemType(leftTerm, currScope, 1));
    } else {
        compareWATType = getWATType(getPrimaryType(leftTerm));
    }

    // Step 2: Determine the WAT operation type from the compareType variable
    char * compareOpWAT = getCompareWATType(compareType, compareWATType);

    // Step 3a: Print the starting statement in WAT
    fprintf(printFile, " (%s.%s", compareWATType, compareOpWAT);

    // Step 3b: Print out the WAT format for both the terms
    generateGetStatementWAT(printFile, leftTerm);
    generateGetStatementWAT(printFile, rightTerm);

    // Step 3c: Finish the comparison statement in WAT
    fprintf(printFile, ")");
}

void generateWhileStartWAT(FILE * printFile) {
    fprintf(printFile, "\t\t(block (loop\n\t\t(br_if 1");
}

// Function module for handling exiting from While Loops
void generateWhileExitWAT(FILE * printFile) {
    fprintf(printFile, "\t\t(br 0)\n\t\t))");
}

// Standard function to generate the main section and text section
// Required before generating any WAT statements
void generateText() {
    // Line variable
    char line[10000];
    int lineNumber = 1;

    // Current operation variable
    char * currOp = calloc(100, sizeof(char));

    // Global return type variable for a given function
    char * returnType = calloc(100, sizeof(char));

    // Current scope and previous scope variables
    currScope = calloc(100, sizeof(char));
    strcpy(currScope, "global");
    prevScope = calloc(100, sizeof(char));

    // Loop through each line in the code and generate WAT for each valid statement
    while (fgets(line, MAX_LINE_LENGTH, IRcode) != NULL) {
        // Ensure the line from fgets isn't beyond the max
        // Avoids buffer overflow attacks
        if (strlen(line) == MAX_LINE_LENGTH - 1 && line[MAX_LINE_LENGTH - 2] != '\n') 	  {
            printf("SEMANTIC ERROR: Line %d is too long.\n", lineNumber);
            exit(1);
        }
        printf("%s", line);

        // While-Loop Algorithm
        // Step 1: Break apart the line into an iterable array of strings
        // Set the varDelimiter for separating terms by word
        char ** strArr;
        strArr = malloc(MAX_ARRAY_LENGTH * sizeof(char *));
        char progDelimiter[] = " ";
        char * token = strtok(line, progDelimiter);

        // Free specific string index for loop reuse
        strArr[3] = "\0";
        strArr[7] = "\0";

        // Add all tokens to a string array
        int lenIndex = 0;
        while(token != NULL) {
            // Assign to string array
            strArr[lenIndex] = token;
            lenIndex++;
            token = strtok(NULL, progDelimiter);
        }

        // Remove "\n" character from the last string
        lenIndex--;
        strArr[lenIndex][strlen(strArr[lenIndex])-1] = '\0';

        // Case for ignoring file comments
        if (strncmp(strArr[0], "\n", 1) == 0 || strncmp(strArr[0], "#", 1) == 0) { }

        // Case for entering function declarations
        else if (strncmp(strArr[0], "entry", 5) == 0) {
            // Set all types after this to local declarations
            isMain = 0;
            inParams = 1;

            // Get WAT Type for Action
            char * newType = getWATType(strArr[1]);

            // Set global return type variable, which is specific to this function
            returnType = newType;

            // Set new scope
            currScope = malloc(strlen(strArr[2])*sizeof(char));
            strcpy(currScope, strArr[2]);

            // Start function declaration
            fprintf(WATcode, "\t(func $%s ", strArr[2]);
        }

        // Case for handling suboperation states
        else if (strncmp(strArr[0], "subop", 5) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            // Set current operation
            strcpy(currOp, strArr[1]);
        }

        // Case for end of strings
        else if (strncmp(strArr[0], "endstring", 9) == 0) {
            // Get the variable scopeType, fileType, and arrIndex
            char * scopeType = getScopeType(strArr[1]);
            FILE* printFile = isMain ? MAINcode : LOCALcode;
            int arrIndex = atoi(strArr[2]) + get(&stringAddresses, strArr[1]);

            // Assign the NULL character to the last value
            setStringElementWAT(printFile, scopeType, strArr[1], arrIndex, 0);
        }

        // Case for addline statement
        else if (strncmp(strArr[0], "addline", 7) == 0) {
            // Call print line module
            generateAddLineWAT(isMain ? MAINcode : LOCALcode);
        }

        // Case for parameter declarations in functions
        else if (strncmp(strArr[0], "param", 5) == 0) {
            // Call parameter module
            generateParameterWAT(WATcode, strArr[1], strArr[2]);
        }

        // Case for exiting functions
        else if (strncmp(strArr[0], "exit", 4) == 0) { 
            isMain = 1; // Set flag back to global
            generateLocalOperations(); // Load in everything from the local file
            generateFunctionEndWAT(currScope); // Generate WAT function ending code
            currScope = "global"; // Set scope back to global
        }

        // Case for return statements in functions
        else if (strncmp(strArr[0], "return", 6) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            // Get variable scopeType
            char * scopeType = getScopeType(strArr[1]);
            
            // Print function ending code
            generateReturnWAT(strArr[1], scopeType);
        }

        // Case for output statements
        else if (strncmp(strArr[0], "output", 6) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            char * variable = strArr[1];
            char * varType = getPrimaryType(variable);

            // If the write statement does not use a variable
            if (strncmp(varType, "var", 3) != 0) {
                
                if (!isMain) { // If its within a function, write to WATcode
                    if (strncmp(varType, "int", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $printInt\n");
                        fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", getWATType(varType), variable);
                        fprintf(LOCALcode, "\t\t)\n");
                    } else if (strncmp(varType, "float", 3) == 0) {
                        fprintf(LOCALcode, "\t\t(call $printFloat\n");
                        fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", getWATType(varType), variable);
                        fprintf(LOCALcode, "\t\t)\n");
                    } else if (strncmp(varType, "string", 3) == 0) {
                        // Concatenate the rest of the tokens into one string variable to get the whole string
                        char * strVar = calloc(MAX_ARRAY_LENGTH, sizeof(char));
                        for (int i = 1; i < lenIndex + 1; i++) {
                            strcat(strVar, strArr[i]);
                            strcat(strVar, " ");
                        }

                        // Generate WAT Code for the whole string
                        generatePrintStringWAT(strVar, "LOCALcode");
                    }

                }
                // Else, write to the MAINcode file
                else {
                    if (strncmp(varType, "int", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $printInt\n");
                        fprintf(MAINcode, "\t\t\t(%s.const %s)\n", getWATType(varType), variable);
                        fprintf(MAINcode, "\t\t)\n");
                    } else if (strncmp(varType, "float", 3) == 0) {
                        fprintf(MAINcode, "\t\t(call $printFloat\n");
                        fprintf(MAINcode, "\t\t\t(%s.const %s)\n", getWATType(varType), variable);
                        fprintf(MAINcode, "\t\t)\n");
                    } else if (strncmp(varType, "string", 3) == 0) {
                        // Concatenate the rest of the tokens into one string variable to get the whole string
                        char * strVar = calloc(MAX_ARRAY_LENGTH, sizeof(char));
                        for (int i = 1; i < lenIndex + 1; i++) {
                            strcat(strVar, strArr[i]);
                            strcat(strVar, " ");
                        }

                        // Generate WAT Code for the whole string
                        generatePrintStringWAT(strVar, "MAINcode");
                    }
                }

            } else { // Else, the write statement uses a variable
                // Determine if the variable is global or variable
                char * scopeType = "global";
                char ** scopeStack = { "global", currScope };
                int scopePointer = 0;

                if (!found(variable, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    scopeType = "local";
                }

                // Get primary type and item kind of the output
                char * token;
                char * primaryType;
                char * itemKind;
                token = strtok(variable, varDelimiter);

                // Case 1: It uses a temporary variable
                if (isTempVar(token)) {
                    primaryType = getTempVarType(token);
                    itemKind = getTempVarKind(token);
                }
                // Case 2: It's a regular variable in the global scope
                else if (strncmp(scopeType, "global", 6) == 0) {
                    primaryType = getItemType(token, "global", scopePointer);
                    itemKind = getItemKind(token, "global", scopePointer);
                }
                // Case 3: It's a regular variable in the local scope
                else {
                    primaryType = getItemType(token, currScope, scopePointer);
                    itemKind = getItemKind(token, currScope, scopePointer);
                }

                // Declare a write string variable
                char * writeStr = malloc(200*sizeof(char));

                // Start call statement with primary type
                if (strncmp(primaryType, "int", 3) == 0) {
                    strcpy(writeStr, "\t\t(call $printInt");
                } else if (strncmp(primaryType, "float", 3) == 0) {
                    strcpy(writeStr, "\t\t(call $printFloat");
                } else if (strncmp(primaryType, "string", 6) == 0) {
                    strcpy(writeStr, "\t\t(call $printString");
                }

                if (!isMain) { // If its within a function, write to WATcode
                    // If the type is an array index, get the array index val and write to the console
                    int len = strlen(variable);
                    if (variable[len - 1] == ']' && strncmp(itemKind, "Array", 5) == 0) {
                        // Get the array variable and the index number
                        char * arrayName = malloc(100*sizeof(char));
                        char * arrIndex = malloc(100*sizeof(char));

                        // Assign variable name
                        strcpy(arrayName, token);

                        // Assign array index variable
                        token = strtok(NULL, varDelimiter);
                        sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(token));

                        // Print get_element call
                        fprintf(LOCALcode, "%s (call $get_element (%s.get $%s) (i32.const %s)))\n", writeStr, scopeType, arrayName, arrIndex);

                    } else if (strncmp(itemKind, "Array", 5) == 0 || strncmp(primaryType, "string", 6) == 0) {
                        // Else if the type is a full array, end the current statement and write out all available indexes

                        // Get the array variable and the index number
                        int arrIndex = 0;

                        // Assign array index variable
                        arrIndex = get(&stringAddresses, variable);
                        
                        // Print out all available indexes using a for-loop
                        for (int newIndex = 0; newIndex < get(&stringSizes, variable); newIndex++) {
                            fprintf(LOCALcode, "%s (call $get_element (%s.get $%s) (i32.const %d)))\n", writeStr, scopeType, variable, arrIndex + newIndex);
                        }
                    } else {
                        // Else, print out the standard variable call
                        fprintf(LOCALcode, "%s (%s.get $%s))\n", writeStr, scopeType, variable);
                    }
                }
                // Else, write to the MAINcode file
                else {
                    // If the type is an array index, get the array index val and write to the console
                    int len = strlen(variable);
                    if (variable[len - 1] == ']' && strncmp(itemKind, "Array", 5) == 0) {
                        // Get the array variable and the index number
                        char * arrayName = malloc(100*sizeof(char));
                        char * arrIndex = malloc(100*sizeof(char));

                        // Assign variable name
                        strcpy(arrayName, token);

                        // Assign array index variable
                        token = strtok(NULL, varDelimiter);
                        sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(token));

                        fprintf(MAINcode, "%s (call $get_element (%s.get $%s) (i32.const %s)))\n", writeStr, scopeType, arrayName, arrIndex);
                    } else if (strncmp(itemKind, "Array", 5) == 0 || strncmp(primaryType, "string", 6) == 0) {
                        // Else if the type is a full array, end the current statement and write out all available indexes

                        // Get the array variable and the index number
                        int arrIndex = 0;

                        // Assign array index variable
                        arrIndex = get(&stringAddresses, variable);
                        
                        // Print out all available indexes using a for-loop
                        for (int newIndex = 0; newIndex < get(&stringSizes, variable); newIndex++) {
                            fprintf(MAINcode, "%s (call $get_element (%s.get $%s) (i32.const %d)))\n", writeStr, scopeType, variable, arrIndex + newIndex);
                        }
                    } else {
                        // Else, print out the standard variable call
                        fprintf(MAINcode, "%s (%s.get $%s))\n", writeStr, scopeType, variable);
                    }
                }
            }
        }

        // Case for type declarations
        else if (strncmp(strArr[0], "type", 4) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            // Get the type and variable
            char * varType = strArr[1];
            char * varName = strArr[2];

            // Generate Declare Statement
            char * printFile = isMain ? "MAINcode" : "LOCALcode";
            generateVarDeclareStatementWAT(printFile, varType, varName);

            // If the variable is an array, generate the $create_array statement
            if (strncmp(strArr[3], "array", 5) == 0) {
                char * arrSize = strArr[4];
                generateArrayDeclareStatementWAT(printFile, varType, varName, arrSize);
            }
        }

        // Case for While Statements
        else if (strncmp(strArr[0], "while", 5) == 0) {
            FILE * printFile = isMain ? MAINcode : LOCALcode;
            generateWhileStartWAT(printFile);

            // Determine if uses a single statement
            if (lenIndex == 3) {
                generateComparisonWAT(printFile, strArr[1], strArr[2], strArr[3]);
            }

            // End While Condition Line
            fprintf(printFile, ")\n");

            // Set new scope and retain history using previous scope
            strcpy(prevScope, currScope);
            strcpy(currScope, "while global 0");
        }

        // Case for While Statements
        else if (strncmp(strArr[0], "endwhile", 3) == 0) {
            generateWhileExitWAT(isMain ? MAINcode : LOCALcode);

            // Switch the previous scope and the current scope
            char * tempScope = calloc(100, sizeof(char));
            strcpy(tempScope, currScope);
            strcpy(currScope, prevScope);
            strcpy(prevScope, tempScope);
        }

        // Case for Void Function Calls
        else if (strncmp(strArr[0], "call", 4) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            // Declare all three variables
            char * funcVar = strArr[1];

            // Output function call lines
            // If there are no arguments after the "args" token, generate the call on a single line
            if (strArr[3] == NULL || strncmp(strArr[3], "\0", 1) == 0) {
                if (isMain) {
                    fprintf(MAINcode, "\t\t(call $%s)\n", funcVar);
                } else {
                    fprintf(LOCALcode, "\t\t(call $%s)\n", funcVar);
                }
            }
            // Otherwise, generate the call with the list of parameters
            else {
                if (isMain) {
                    fprintf(MAINcode, "\t\t(call $%s\n", funcVar);
                } else {
                    fprintf(LOCALcode, "\t\t(call $%s\n", funcVar);
                }

                // Loop through and add all available parameters as lines under the function call
                // Determine if each one is a variable or not, and assign accordingly
                int index = 3;
                while (strArr[index] != NULL) {
                    // Double check and break if it's the end of sequence
                    if (strncmp(strArr[index], "\0", 1) == 0) {
                        break;
                    }

                    char * callVar = strArr[index];
                    
                    // If var references an actual variable, add a dollar sign in front and build the line accordingly
                    if (strncmp(getPrimaryType(strArr[index]), "var", 3) == 0) {
                        // Determine if the variable is global or variable
                        char * varScopeType = "global";
                        char ** scopeStack = { "global", currScope };
                        int scopePointer = 0;

                        if (!found(strArr[index], scopeStack, scopePointer)) {
                            scopePointer = 1;
                            varScopeType = "local";
                        }

                        if (isMain) {
                            fprintf(MAINcode, "\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                        } else {
                            fprintf(LOCALcode, "\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                        }
                        
                    } else {
                        char * opType = getWATType(getPrimaryType(strArr[index]));

                        if (isMain) {
                            fprintf(MAINcode, "\t\t\t(%s.const %s)\n", opType, callVar);
                        } else {
                            fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", opType, callVar);
                        }
                    }
                    index++;
                }

                // End the call statement with parameters
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t)\n");
                } else {
                    fprintf(LOCALcode, "\t\t\t)\n");
                }
            }
        }

        // Assignment Statements
        // Total Strings = 3
        // STR1 = Assigned Variable, STR2 = "=", STR3 = Primary Variable

        // Assignment Operation
        else if (strArr[3] == NULL || strncmp(strArr[3], "\0", 1) == 0 || strncmp(strArr[3], "\"", 1) == 0) {
            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }

            // Declare all three variables
            char * assignVar = strArr[0];
            char * primaryVar = strArr[2];
            
            // Declare operation type variable
            char * opType;

            // Determine if the variable is global or local
            char * scopeType = "global";
            char ** scopeStack = { "global", currScope };
            int scopePointer = 0;

            if (!found(strArr[0], scopeStack, scopePointer)) {
                scopePointer = 1;
                scopeType = "local";
            }

            // If a current operation has not been assigned, get the current operation from the assignment statement
            if (strncmp(currOp, "\0", 1) == 0 || currOp == NULL) {
                currOp = getPrimaryType(primaryVar);
            }

            // Determine the operation type
            opType = getWATType(currOp);

            // Output the assignVar call line
            // If the assigned variable is an array index
            int lenArr0 = strlen(assignVar);
            if (assignVar[lenArr0 - 1] == ']' && isMain) {
                // Declare a size variable
                char * size = strtok(strArr[0], "[], ");

                // Redetermine if the scope is global or local
                scopePointer = 0;
                if (!found(size, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    scopeType = "local";
                } else {
                    scopeType = "global";
                }

                // Get the size number from the assignVar
                while (isInt(size) != 1) {
                    size = strtok(NULL, "[], ");
                }

                // Declare a new array index variable
                char * arrIndex = malloc(50*sizeof(char));
                sprintf(arrIndex, "%d", get(&stringAddresses, assignVar) + atoi(size));

                // Start the declaration statement
                fprintf(MAINcode, "\t\t(call $set_element\n");
                fprintf(MAINcode, "\t\t\t(%s.get $%s)\n", scopeType, assignVar);
                fprintf(MAINcode, "\t\t\t(i32.const %s)\n", arrIndex);
            } else if (assignVar[lenArr0 - 1] == ']') {
                // Declare a size variable
                char * size = strtok(strArr[0], "[], ");

                // Redetermine if the scope is global or local
                scopePointer = 0;
                if (!found(size, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    scopeType = "local";
                } else {
                    scopeType = "global";
                }

                // Get the size number from the assignVar
                while (isInt(size) != 1) {
                    size = strtok(NULL, "[], ");
                }

                // Declare a new array index variable
                char * arrIndex = malloc(50*sizeof(char));
                sprintf(arrIndex, "%d", get(&stringAddresses, assignVar) + atoi(size));

                // Start the declaration statement
                fprintf(LOCALcode, "\t\t(call $set_element\n");
                fprintf(LOCALcode, "\t\t\t(%s.get $%s)\n", scopeType, assignVar);
                fprintf(LOCALcode, "\t\t\t(i32.const %s)\n", arrIndex);

            } else if (isMain) { // If it's a temp variable in global, print to MAINcode
                fprintf(MAINcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
            }
            // Else, print to WATcode
            else {
                fprintf(LOCALcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
            }

            char * primaryToken = malloc(100*sizeof(char));
            strcpy(primaryToken, primaryVar);
            primaryToken = strtok(primaryToken, varDelimiter);
            int lenArr2 = strlen(primaryVar);

            // If primaryVar references an actual variable, add a dollar sign in front and build the line accordingly
            if (strncmp(getPrimaryType(primaryToken), "var", 3) == 0) {
                // Determine if the variable is global or variable
                char * varScopeType = "global";
                scopePointer = 0;

                if (!found(primaryToken, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    varScopeType = "local";
                }

                // If var is an array index callout, generate a call to the appropriate index
                if (primaryVar[lenArr2 - 1] == ']' && isMain) {
                    // If it's array call in global, print to MAIN code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, primaryToken);

                    // Assign array index variable
                    primaryToken = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(primaryToken));

                    // Print array index code
                    fprintf(MAINcode, "\t\t\t(call $get_element\n");
                    fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(MAINcode, "\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(MAINcode, "\t\t\t)\n");
                    
                } else if (primaryVar[lenArr2 - 1] == ']') {
                    // If it's array call in a function, print to LOCAL code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, primaryToken);

                    // Assign array index variable
                    primaryToken = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(primaryToken));

                    // Print array index code
                    fprintf(LOCALcode, "\t\t\t(call $get_element\n");
                    fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(LOCALcode, "\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(LOCALcode, "\t\t\t)\n");

                } else if (isMain) { // If it's a temp variable in global, print to MAINcode
                    fprintf(MAINcode, "\t\t\t(%s.get $%s)\n", varScopeType, primaryVar);
                }
                // Else, print to WATcode
                else {
                    fprintf(LOCALcode, "\t\t\t(%s.get $%s)\n", varScopeType, primaryVar);
                }
            } else {
                // Check if primaryVar references a char
                // If it does, convert it to an ASCII value
                if (strncmp(getPrimaryType(primaryVar), "string", 6) == 0) {
                    primaryVar = convertToASCII(primaryVar);
                }

                // Check if primaryVar equals zero (unidentified value)
                // If so, convert it to a space in ASCII
                if (strncmp(primaryVar, "0", 1) == 0) {
                    primaryVar = "32";
                }
                
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t(%s.const %s)\n", opType, primaryVar);
                } else {
                    fprintf(LOCALcode, "\t\t\t(%s.const %s)\n", opType, primaryVar);
                }
            }

            // End assignment statement
            if (isMain) { // If it's a temp variable in global, print to MAINcode
                fprintf(MAINcode, "\t\t)\n");
            }
            // Else, print to WATcode
            else {
                fprintf(LOCALcode, "\t\t)\n");
            }
            
            // Reset currOp variable
            currOp = calloc(100, sizeof(char));
        }

        // Case for Standard Function Calls
        // Contains a "call" token at index 3
        // Always acts as an assignment statement, but calls a function register with a set of parameters
        else if (strncmp(strArr[2], "call", 4) == 0) {
            // Declare all three variables
            char * assignVar = strArr[0];
            char * funcVar = strArr[3];
            
            // Declare operation type variable
            char * opType;

            // Determine if the variable is global or variable
            char * scopeType = "global";
            char ** scopeStack = { "global", currScope };
            int scopePointer = 0;

            if (!found(strArr[0], scopeStack, scopePointer)) {
                scopePointer = 1;
                scopeType = "local";
            }

            // Determine the operation type
            opType = getWATType(currOp);

            // Set function return type
            if (inParams) {
                inParams = 0;
                generateResultWAT(WATcode, returnType);
            }
            // Else, print a temporary variable declaration line with the WAT type
            // Save the temporary variable to the table
            else {
                // Add the temporary variable to the table
                addTempVarItem(assignVar, currOp, "Var");

                // Insert into either global or local scope
                if (isMain) {
                    fprintf(VARScode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                } else {
                    fprintf(WATcode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                }
            }

            // Output the assignVar call line
            if (isMain) {
                fprintf(MAINcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
            } else {
                fprintf(LOCALcode, "\t\t(%s.set $%s\n", scopeType, assignVar);
            }

            // Output function call lines
            // If there are no arguments after the "args" token, generate the call on a single line
            if (strArr[5] == NULL) {
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t(call $%s)\n", funcVar);
                } else {
                    fprintf(LOCALcode, "\t\t\t(call $%s)\n", funcVar);
                }
            }
            // Otherwise, generate the call with the list of parameters
            else {
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t(call $%s\n", funcVar);
                } else {
                    fprintf(LOCALcode, "\t\t\t(call $%s\n", funcVar);
                }


                // Loop through and add all available parameters as lines under the function call
                // Determine if each one is a variable or not, and assign accordingly
                int index = 5;
                while (strArr[index] != NULL) {
                    // Double check and break if it's the end of sequence
                    if (strncmp(strArr[index], "\0", 1) == 0) {
                        break;
                    }

                    char * callVar = strArr[index];
                    
                    // If var references an actual variable, add a dollar sign in front and build the line accordingly
                    if (strncmp(getPrimaryType(strArr[index]), "var", 3) == 0) {
                        // Determine if the variable is global or variable
                        char * varScopeType = "global";
                        scopePointer = 0;

                        if (!found(strArr[index], scopeStack, scopePointer)) {
                            scopePointer = 1;
                            varScopeType = "local";
                        }

                        if (isMain) {
                            fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                        } else {
                            fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, callVar);
                        }
                        
                    } else {
                        opType = getWATType(getPrimaryType(strArr[index]));

                        if (isMain) {
                            fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, callVar);
                        } else {
                            fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, callVar);
                        }
                    }
                    index++;
                }

                // End the call statement with parameters
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t)\n");
                } else {
                    fprintf(LOCALcode, "\t\t\t)\n");
                }
            }

            // End assignment statement
            if (isMain) {
                fprintf(MAINcode, "\t\t)\n");
            } else {
                fprintf(LOCALcode, "\t\t)\n");
            }
            
            // Reset currOp variable
            currOp = calloc(100, sizeof(char));
        }

        // c. Basic Operations
        // - Total Strings = 5
        // - STR1 = Assign Variable, STR2 = "=", STR3 = Primary Variable 1,
        // - STR4 = Operand, STR5 = Primary Variable 2

        else if (strncmp(strArr[3], "+", 1) == 0 || strncmp(strArr[3], "-", 1) == 0 || strncmp(strArr[3], "*", 1) == 0 || strncmp(strArr[3], "/", 1) == 0) {
            // Declare all three variables
            char * assignVar = strArr[0];
            char * var1 = strArr[2];
            char * var2 = strArr[4];
            
            // Declare operation type variable
            char * opType;

            // Determine if the variable is global or variable
            char * scopeType = "global";
            char ** scopeStack = { "global", currScope };
            int scopePointer = 0;

            if (!found(assignVar, scopeStack, scopePointer)) {
                scopePointer = 1;
                scopeType = "local";
            }
            // Determine the operation type
            opType = getWATType(currOp);

            // If not in parameters, print a temporary variable declaration line with the WAT type
            // Save the temporary variable to the table
            if (!inParams) {
                // Add the temporary variable to the table
                addTempVarItem(assignVar, currOp, "Var");

                // Insert into either global or local scope
                if (isMain) {
                    fprintf(VARScode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                } else {
                    fprintf(WATcode, "\t\t(%s $%s %s)\n", scopeType, assignVar, opType);
                }
                
            }

            // Output the variable set line
            if (isMain) {
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
            if (isMain) {
                fprintf(MAINcode, "\t\t\t(%s.%s%s\n", opType, opCall, specialOp);
            } else {
                fprintf(LOCALcode, "\t\t\t(%s.%s%s\n", opType, opCall, specialOp);
            }

            // Declare variables for the operation
            char * tokenVar1 = malloc(100*sizeof(char));
            strcpy(tokenVar1, var1);
            tokenVar1 = strtok(tokenVar1, varDelimiter);
            int lenVar1 = strlen(var1);

            // If var1 references an actual variable, add a dollar sign in front and build the line accordingly
            if (strncmp(getPrimaryType(tokenVar1), "var", 3) == 0) {
                // Determine if the variable is global or variable
                char * varScopeType = "global";
                char ** scopeStack = { "global", currScope };
                int scopePointer = 0;

                if (!found(tokenVar1, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    varScopeType = "local";
                }

                // If var1 is an array index callout, generate a call to the appropriate index
                if (var1[lenVar1 - 1] == ']' && isMain) {
                    // If it's in global, print to MAIN code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, tokenVar1);

                    // Assign array index variable
                    tokenVar1 = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(tokenVar1));

                    // Print array index code
                    fprintf(MAINcode, "\t\t\t\t(call $get_element\n");
                    fprintf(MAINcode, "\t\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(MAINcode, "\t\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(MAINcode, "\t\t\t\t)\n");

                } else if (var1[lenVar1 - 1] == ']') {
                    // If it's in a function, print to LOCAL code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, tokenVar1);

                    // Assign array index variable
                    tokenVar1 = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(tokenVar1));

                    // Print array index code
                    fprintf(LOCALcode, "\t\t\t\t(call $get_element\n");
                    fprintf(LOCALcode, "\t\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(LOCALcode, "\t\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(LOCALcode, "\t\t\t\t)\n");

                } else if (isMain) {
                    fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var1);
                } else {
                    fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var1);
                }
            } else {
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, var1);   
                } else {
                    fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, var1);
                }
            }

            // Declare variables for the operation
            char * tokenVar2 = malloc(100*sizeof(char));
            strcpy(tokenVar2, var2);
            tokenVar2 = strtok(tokenVar2, varDelimiter);
            int lenVar2 = strlen(var2);

            // If var2 references an actual variable, add a dollar sign in front and build the line accordingly
            if (strncmp(getPrimaryType(tokenVar2), "var", 3) == 0) {
                // Determine if the variable is global or variable
                char * varScopeType = "global";
                char ** scopeStack = { "global", currScope };
                int scopePointer = 0;

                if (!found(tokenVar2, scopeStack, scopePointer)) {
                    scopePointer = 1;
                    varScopeType = "local";
                }

                // If var2 is an array index callout, generate a call to the appropriate index
                if (var2[lenVar2 - 1] == ']' && isMain) {
                    // If it's in global, print to MAIN code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, tokenVar2);

                    // Assign array index variable
                    tokenVar2 = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(tokenVar2));

                    // Print array index code
                    fprintf(MAINcode, "\t\t\t\t(call $get_element\n");
                    fprintf(MAINcode, "\t\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(MAINcode, "\t\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(MAINcode, "\t\t\t\t)\n");

                } else if (var2[lenVar2 - 1] == ']') {
                    // If it's in a function, print to LOCAL code
                    // Get the array variable and the index number
                    char * arrayName = malloc(100*sizeof(char));
                    char * arrIndex = malloc(100*sizeof(char));

                    // Assign variable name
                    strcpy(arrayName, tokenVar2);

                    // Assign array index variable
                    tokenVar2 = strtok(NULL, varDelimiter);
                    sprintf(arrIndex, "%d", get(&stringAddresses, arrayName) + atoi(tokenVar2));

                    // Print array index code
                    fprintf(LOCALcode, "\t\t\t\t(call $get_element\n");
                    fprintf(LOCALcode, "\t\t\t\t\t(%s.get $%s)\n", varScopeType, arrayName);
                    fprintf(LOCALcode, "\t\t\t\t\t(i32.const %s)\n", arrIndex);
                    fprintf(LOCALcode, "\t\t\t\t)\n");

                } else if (isMain) {
                    fprintf(MAINcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var2);
                } else {
                    fprintf(LOCALcode, "\t\t\t\t(%s.get $%s)\n", varScopeType, var2);
                }
            } else {
                if (isMain) {
                    fprintf(MAINcode, "\t\t\t\t(%s.const %s)\n", opType, var2);
                } else {
                    fprintf(LOCALcode, "\t\t\t\t(%s.const %s)\n", opType, var2);
                }
            }

            // End the operation call
            if (isMain) {
                fprintf(MAINcode, "\t\t\t)\n");
                fprintf(MAINcode, "\t\t)\n");
            } else {
                fprintf(LOCALcode, "\t\t\t)\n");
                fprintf(LOCALcode, "\t\t)\n");
            }
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
    // Initialize String Hash Tables
    init(&stringAddresses);
    init(&stringSizes);

    initAssemblyFile();
    generateStartModule();
    generateText();
    generateMain();
    completeFile();
}