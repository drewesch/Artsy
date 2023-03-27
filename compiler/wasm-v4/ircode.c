
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ircode.h"
#include "helper.h"
#include "semantic.h"
#include "symbolTable.h"
#include "AST.h"

// FEATURES TO ADD
// 1. Assignment Declaration Semantic Check
//      - By default, all integers and floats in WebAssembly are set to "0" and "0.0" respectively if it's not assigned
//      - For this language, we could force users to assign a value first before using it an any operation

// Open two files for unoptimized and optimized IRcode
FILE * IRcode;
FILE * IRcodeOptimized;

// Constant declarations for generating variables and statements in the IRcode
int lastIndex = 0;
int lastArrayTempIndex = 0;
char outputId[50];
char buffer[50];
char * arrElVar;
char params[50][50];
int paramIndex = 0;

// Bool for checking if a comparison is within a logical statement
int isLogical = 0;
int currLogicalStatements = 0;
int totalLogicalStatements = 0;
char ** logicalTypes;

// Bool for checking if type is a parameter
int isParam = 0;

// Variable to detect current scope
char * currIRScope = "global";

// Variables to detect suboperation starts
int startSubOp = 0;
int startSubOpOptimized = 0;

// Struct to handle temporary variable construction
struct ConstantVar {
    char var[50];
    char scope[50];
    int val;
};

// Generate symbol table of temporary variables
struct ConstantVar cvTable[100];

// Indexes to traverse these tables
int cvIndex = 0;
int uvIndex = 0;

// Temporary variable struct to determine if a variable has been used in optimization
struct Var {
    char var[50];
    int boolVal;
};

// Generate symbol table for variable usage
struct Var uvTable[100];

// Function to open unoptimized IRcode
void initIRcodeFile() {
    IRcode = fopen("IRcode.ir", "w");
    fprintf(IRcode, "#### IR Code ####\n");
}

// Function to open optimized IRcode file
void initIRcodeFileOptimized() {
    IRcodeOptimized = fopen("IRcodeOptimized.ir", "w");
    fprintf(IRcodeOptimized, "#### Optimized IR Code ####\n");
}

char * updateArrayId(char id[50]) {
    // Split apart the phrase into a set of tokens by the "[" keyword
    char delimiter[] = "[], ";
    return strtok(id, delimiter);
}

// Use the cvTable to find the temporary variable for a given variable declaration
char* getVarConstant(char var[50]){
	for(int i=0; i<cvIndex; i++){
        if (strcmp(cvTable[i].var, var) == 0){
            memset(buffer, 0, 50);
			sprintf(buffer, "%d", cvTable[i].val);
            return buffer;
		}
	}
	return var;
}

// Function to add a variable to the unused variable table
void addUnusedVar(char var[50]) {
    strncpy(uvTable[uvIndex].var, var, 50);
    uvTable[uvIndex].boolVal = 0;
    uvIndex++;
}

// Function to update variable declarations if the variable is unused - part of the optimization process
void updateUnusedVar(char var[50]) {
	for(int i=0; i<uvIndex; i++){
        if (strcmp(uvTable[i].var, var) == 0) {
            uvTable[i].boolVal = 1;
            return;
		}
	}
}

// Checks the symbol table
// Returns true or false depending if the variable is used or not (for code optimization)
int isUsedVar(char var[50]) {
    for (int i = 0; i < uvIndex; i++){
        if (strcmp(uvTable[i].var, var) == 0) {
            return uvTable[i].boolVal;
		}
	}
    return 0;
}

// For unoptimized IRcode
// Generates the IRcode for assignments
char* emitBinaryOperation(char op[2], const char* id1, const char* id2){
    // Assign temporary variables for tracking base array variables
    char * token1 = malloc(strlen(id1)*sizeof(char));
    char * token2 = malloc(strlen(id2)*sizeof(char));
    strcpy(token1, id1);
    strcpy(token2, id2);

    // Create a temporary variable assignment using "T"
    memset(outputId, 0, 50);
    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);

    // Updates the declaration if the variable is unused
    if (strncmp(getPrimaryType(token1), "var", 3) == 0) {
        updateUnusedVar(updateArrayId(token1));
    }
    if (strncmp(getPrimaryType(token2), "var", 3) == 0) {
        updateUnusedVar(updateArrayId(token2));
    }

    // Output suboperation type (for webgen parsing)
    if (!startSubOp) {
        char * opType;
        
        if (strncmp(getPrimaryType(token1), "var", 3) == 0) {
            opType = getItemType(token1, currIRScope, 1);
        } else {
            opType = getPrimaryType(token1);
        }

        fprintf(IRcode, "subop %s\n", opType);
        startSubOp = 1;
    }

    // Print the unoptimized iRcode using outputIDs, the operator, and the other ids
    fprintf(IRcode, "%s = %s %s %s\n", outputId, token1, op, token2);
    lastIndex += 1;

    // Returns output
    return outputId;
}

// Helper function that checks each char and determines if the whole string is a digit or not
int isnumeric(char var[50]) {
    for(int i = 0; var[i]; i++) {
        // If any char in the string is not a digit, return false
        if(!isdigit((int)var[i])) {
            return 0;
        }
    }
    // Else, return true, it is a digit
    return 1;
}

// Optimized version of binary operations for IRcodeOptimized.ir
char* emitBinaryOperationOptimized(char op[1], const char* id1, const char* id2){
    // printf("ID1: %s, ID2: %s\n", id1, id2);
    memset(outputId, 0, 50);

    // Assign temporary variables for tracking base array variables
    char * token1 = malloc(strlen(id1)*sizeof(char));
    char * token2 = malloc(strlen(id2)*sizeof(char));
    strcpy(token1, id1);
    strcpy(token2, id2);

    // If it's an array, get the optype based on the token
    char * opType = getPrimaryType(updateArrayId(token1));

    if (strncmp(opType, "int", 3) == 0) {
        int num1 = (int) strtol(id1, (char **)NULL, 10);
        int num2 = (int) strtol(id2, (char **)NULL, 10);

        // Get optimized result
        int result;
        if (strncmp(op, "+", 1) == 0) {
            result = num1 + num2;
        } else if (strncmp(op, "-", 1) == 0) {
            result = num1 - num2;
        } else if (strncmp(op, "*", 1) == 0) {
            result = num1 * num2;
        } else if (strncmp(op, "/", 1) == 0) {
            result = num1 / num2;
        }

        sprintf(outputId, "%d", result);
        return outputId;
    } else if (strncmp(opType, "float", 5) == 0) {
        float num1 = atof(id1);
        float num2 = atof(id2);

        // Get optimized result
        float result;
        if (strncmp(op, "+", 1) == 0) {
            result = num1 + num2;
        } else if (strncmp(op, "-", 1) == 0) {
            result = num1 - num2;
        } else if (strncmp(op, "*", 1) == 0) {
            result = num1 * num2;
        } else if (strncmp(op, "/", 1) == 0) {
            result = num1 / num2;
        }

        sprintf(outputId, "%f", result);
        return outputId;
    }

    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);
    
    // Output suboperation type (for webgen parsing)
    if (!startSubOpOptimized) {
        char * opType = calloc(100, sizeof(char));

        if (strncmp(getPrimaryType(token1), "var", 3) == 0) {
            opType = getItemType(token1, currIRScope, 1);
        } else {
            opType = getPrimaryType(token1);
        }

        fprintf(IRcodeOptimized, "subop %s\n", opType);
        startSubOpOptimized = 1;
    }

    // Output optimized suboperation line
    // printf("TOK1: %s, TOK2: %s\n", token1, token2);
    fprintf(IRcodeOptimized, "%s = %s %s %s\n", outputId, id1, op, id2);
    lastIndex += 1;

    return outputId;
}

// Unoptimized IRcode operation for variable assignment
void emitAssignment(char * id1, char * id2){
    // Print the assignment statement using the two basic IDs
    // If the statement is a combined string, separate it as a set of array index assignments
    if (strncmp(getPrimaryType(id2), "string", 6) == 0) {
        // Update the symbol table with the new array length
        char ** scopeStack = currIRScope;

        // Get the number of escape characters
        // Used in calculating the new array length
        int numEscapeCharacters = countEscapeChars(id2);

        // If new array length is bigger, update it to that
        if (strlen(id2)-2-numEscapeCharacters > getArrayLength(id1, scopeStack, 0)) {
            updateItemArrayLength(id1, scopeStack, 0, strlen(id2)-2);
        }

        // Print each index assignment statement
        int loopEscapeChars = 0; // Tracks total escape chars encountered
        for (int i = 1; i < strlen(id2)-1-numEscapeCharacters; i++) {
            if (id2[i+loopEscapeChars] == '\\') {
                fprintf(IRcode, "%s[%d] = \"%s\"\n", id1, i-1, escapeCharType(id2[i+1+loopEscapeChars]));
                loopEscapeChars++;
            } else {
                fprintf(IRcode, "%s[%d] = \"%c\"\n", id1, i-1, id2[i+loopEscapeChars]);
            }
        }

        // Indicate end of full string with length
        fprintf(IRcode, "endstring %s %ld\n", id1, strlen(id2)-2-numEscapeCharacters);
    } else {
        fprintf(IRcode, "%s = %s\n", id1, id2);
    }

    // Indicate subop stop
    startSubOp = 0;
}

// Unoptimized IRcode operation for variable assignment (for array)
void emitAssignmentForElement(char *id1, char * elementNum, char * id2) {
    // Print the assignment statement using the two basic IDs with an element number
    fprintf(IRcode, "%s[%s] = %s\n", id1, elementNum, id2);
}

void emitAssignmentForElementOptimized(char *id1, char * elementNum, char * id2) {
    int flag = 1;

    if(isnumeric(id2)) {
        for(int i=0; i<cvIndex; i++){
            if (strcmp(cvTable[i].var, id1) == 0){
                cvTable[i].val = (int) strtol(id2, (char **)NULL, 10);
                flag = 0;
                break;
            }
	    }
        if(flag) {
            strcpy(cvTable[cvIndex].var, id1);
            cvTable[cvIndex].val = (int) strtol(id2, (char **)NULL, 10);
            cvIndex ++;
        }
    }

    // Print the assignment statement using the two basic IDs with an element number
    fprintf(IRcodeOptimized, "%s[%s] = %s\n", id1, elementNum, id2);
}

// Optimized assignment operation function for IRcodeOptimized.ir
void emitAssignmentOptimized(char * id1, char * id2){
    int flag = 1;
    if(isnumeric(id2)) {
        for(int i=0; i<cvIndex; i++){
            if (strcmp(cvTable[i].var, id1) == 0){
                cvTable[i].val = (int) strtol(id2, (char **)NULL, 10);
                flag = 0;
                break;
            }
	    }
        if(flag) {
            strcpy(cvTable[cvIndex].var, id1);
            cvTable[cvIndex].val = (int) strtol(id2, (char **)NULL, 10);
            cvIndex ++;
        }
    }

    // If the statement is a combined string,
    // separate it out into a set of array index assignments
    if (strncmp(getPrimaryType(id2), "string", 6) == 0) {
        // Get the number of escape characters
        // Used in calculating the new array length
        int numEscapeCharacters = countEscapeChars(id2);
        int loopEscapeChars = 0; // Tracks total escape chars encountered
        for (int i = 1; i < strlen(id2)-1-numEscapeCharacters; i++) {
            if (id2[i+loopEscapeChars] == '\\') {
                fprintf(IRcodeOptimized, "%s[%d] = \"%s\"\n", id1, i-1, escapeCharType(id2[i+1+loopEscapeChars]));
                loopEscapeChars++;
            } else {
                fprintf(IRcodeOptimized, "%s[%d] = \"%c\"\n", id1, i-1, id2[i+loopEscapeChars]);
            }
        }
        // Indicate end of full string with length
        fprintf(IRcodeOptimized, "endstring %s %ld\n", id1, strlen(id2)-2-numEscapeCharacters);
    } else {
        fprintf(IRcodeOptimized, "%s = %s\n", id1, id2);
    }
    
    // Indicate subop stop
    startSubOpOptimized = 0;

}

void emitWritePrimary(char * value) {
    fprintf(IRcode, "output %s\n", value);
}

void emitWritePrimaryOptimized(char * value) {
    fprintf(IRcodeOptimized, "output %s\n", value);
}

// Unoptimized IRcode operation for the write keyword
void emitWriteId(char * id) {
    // Update variable in the unused variable table
    updateUnusedVar(updateArrayId(id));

    fprintf(IRcode, "output %s\n", id);
}

// Optimized IRCode operation for writing 
void emitWriteIdOptimized(char * id){
    // Print output keyword with the associated ID
    // Unused variables are already removed prior to this step, so it is redundant to include it here
    fprintf(IRcodeOptimized, "output %s\n", id);
}

void emitWriteLn(){
    fprintf(IRcode, "addline\n");
}

void emitWriteLnOptimized(){
    fprintf(IRcodeOptimized, "addline\n");
}

// Outputs the variable and type for variable declaration (unoptimized)
void emitTypeDeclaration(char * type, char * id){
    // Flag variable for unused code optimization testing
    int flag = 1;
    
    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";
    
    // Check the whole UV table
    // If the type is already in the table, set the flag to 0
    for(int i=0; i<uvIndex; i++){
        if (strcmp(uvTable[i].var, id) == 0){ flag = 0; break; }
    }
    // If the flag is still true, add the new id to the unused variable table
    if (flag) {
        addUnusedVar(id);
    }

    if(isParam) {
        varType = "param";
    }

    // Print variable declaration IRcode to file
    // If the type is a string, print a statement with a default size limit
    if (strncmp(type, "string", 6) == 0) {
        char * size = "100";
        fprintf(IRcode, "%s %s %s array %s\n", varType, type, id, size);
    } else {
        // Else, print a standard type declaration statement
        fprintf(IRcode, "%s %s %s\n", varType, type, id);
    }
}

// Outputs the variable and type for variable declaration (unoptimized) (for array)
void emitTypeArrayDeclaration(char * type, char * id, char * size){
    // Flag variable for unused code optimization testing
    int flag = 1;

    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";

    if(isParam) {
        varType = "param";
    }

    // Check the whole UV table
    // If the type is already in the table, set the flag to 0
    for(int i=0; i<uvIndex; i++){
        if (strcmp(uvTable[i].var, id) == 0){ flag = 0; break; }
    }

    // If the flag is still true, add the new id to the unused variable table
    // Also, print the 
    if (flag) {
        addUnusedVar(id);
    }

    fprintf(IRcode, "%s %s %s array %s\n", varType, type, id, size);
}

// Emit the type declaration for optimized IRcode file
void emitTypeDeclarationOptimized(char * type, char * id){
    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";

    if(isParam) {
        varType = "param";
    }

    // Already includes optimizations prior to this step, so doing optimization beforehand is redundant
    // Print variable declaration IRcode to file
    // If the type is a string, print a statement with a default size limit
    if (strncmp(type, "string", 6) == 0) {
        char * size = "100";
        fprintf(IRcodeOptimized, "%s %s %s array %s\n", varType, type, id, size);
    } else {
        // Else, print a standard type declaration statement
        fprintf(IRcodeOptimized, "%s %s %s\n", varType, type, id);
    }

}

// Outputs the variable and type for variable declaration (unoptimized) (for array)
void emitTypeArrayDeclarationOptimized(char * type, char * id, char * size){
    // Flag variable for unused code optimization testing
    int flag = 1;

    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";

    if(isParam) {
        varType = "param";
    }

    // Already includes optimizations prior to this step, so doing optimization beforehand is redundant
    // Print variable declaration IRcode to file
    fprintf(IRcodeOptimized, "%s %s %s array %s\n", varType, type, id, size);
}

void emitEntry(char * id) {
    int flag = 1;

    // Check the whole UV table
    // If the type is already in the table, set the flag to 0
    for(int i=0; i<uvIndex; i++){
        if (strcmp(uvTable[i].var, id) == 0){ flag = 0; break; }
    }

    // If the flag is still true, add the new id to the unused variable table
    if (flag) {
        addUnusedVar(id);
    }

    // Get type and update current scope
    char ** scopeStack = { "global", currIRScope };
    char * type = getItemType(id, scopeStack, 1);
    currIRScope = id;

    fprintf(IRcode, "entry %s %s\n", type, id);
}

void emitEntryOptimized(char * id) {    
    char ** scopeStack = { "global", currIRScope };
    char * type = getItemType(id, scopeStack, 1);
    currIRScope = id;

    fprintf(IRcodeOptimized, "entry %s %s\n", type, id);
}

void emitReturn(char * id) {
    // Create a temporary variable for array return support
    char token[50];
    strcpy(token, id);

    // Updates the variable if it is unused
    if (strncmp(getPrimaryType(token), "var", 3) == 0) {
        updateUnusedVar(updateArrayId(token));
    }

    fprintf(IRcode, "return %s\n", id);
}

void emitReturnOptimized(char * id) {    
    fprintf(IRcodeOptimized, "return %s\n", id);
}

void emitExit() {
    currIRScope = "global";
    fprintf(IRcode, "exit\n");
}

void emitExitOptimized() {
    currIRScope = "global";
    fprintf(IRcodeOptimized, "exit\n");
}

void emitLogicalExpression(char * opType) {
    fprintf(IRcode, " %s", opType);
}

void emitComparisonExpression(char * leftExpr, char * compareType, char * rightExpr) {
    fprintf(IRcode, " %s %s %s", leftExpr, compareType, rightExpr);
}

void emitIfConditionStatement() {
    fprintf(IRcode, "if");
}

void emitIfEndStatement() {
    fprintf(IRcode, "end if\n");
}

void emitElifEndStatement() {
    fprintf(IRcode, "end elif\n");
}

void emitElseEndStatement() {
    fprintf(IRcode, "end else\n");
}

void emitWhileConditionStatement() {
    // Print While Starting Statement
    fprintf(IRcode, "while");
}

void emitWhileEndStatement() {
    fprintf(IRcode, "end while\n");
}

char * emitFunctionCall(char *id) {
    memset(outputId, 0, 50);
    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);

    // Update the code if it is unused
    if (strncmp(getPrimaryType(id), "var", 3) == 0) {
        updateUnusedVar(id);
    }

    // Output suboperation type (for webgen parsing)
    char * opType = calloc(100, sizeof(char));
    if (!startSubOp) {        
        if (strncmp(getPrimaryType(id), "var", 3) == 0) {
            char ** scopeStack = { "global", currIRScope };
            strcpy(opType, getItemType(id, scopeStack, 1));
        } else {
            strcpy(opType, getPrimaryType(id));
        }

        // Do not generate a subop if its a void function call
        if (strncmp(opType, "void", 4) != 0) {
            fprintf(IRcode, "subop %s\n", opType);
            startSubOp = 1;
        }
    }

    // Generate function call based on if there is a void keyword
    if (strncmp(opType, "void", 4) != 0) {
        fprintf(IRcode, "%s = call %s args", outputId, id);
    } else {
        fprintf(IRcode, "call %s args", id);
    }
    
    // Print arguments
    for(int i = 0; i < paramIndex; i ++) {
        // Update variable if unused
        if (strncmp(getPrimaryType(params[i]), "var", 3) == 0) {
            updateUnusedVar(params[i]);
        }

        fprintf(IRcode, " %s", params[i]);
    }
    fprintf(IRcode, "\n");
    lastIndex += 1;

    return outputId;
}

char * emitFunctionCallOptimized(char *id) {
    memset(outputId, 0, 50);
    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);

    // Output suboperation type (for webgen parsing)
    char * opType;
    if (!startSubOpOptimized) {
        if (strncmp(getPrimaryType(id), "var", 3) == 0) {
            char ** scopeStack = { "global", currIRScope };
            opType = getItemType(id, scopeStack, 1);
        } else {
            opType = getPrimaryType(id);
        }

        // Do not generate a subop if its a void function call
        if (strncmp(opType, "void", 4) != 0) {
            fprintf(IRcodeOptimized, "subop %s\n", opType);
            startSubOpOptimized = 1;
        }
    }

    // Generate function call based on if there is a void keyword
    if (strncmp(opType, "void", 4) != 0) {
        fprintf(IRcodeOptimized, "%s = call %s args", outputId, id);
    } else {
        fprintf(IRcodeOptimized, "call %s args", id);
    }

    // Generate arguments
    for(int i = 0; i < paramIndex; i ++) {
        fprintf(IRcodeOptimized, " %s", params[i]);
    }
    fprintf(IRcodeOptimized, "\n");
    lastIndex += 1;

    return outputId;
}

// Function to traverse the AST tree
// This initializes creating all of the IRcode for unoptimized IRcode
char* ASTTraversal(struct AST* root) {
    if(root != NULL) {
        printf("root->nodeType: %s\n", root->nodeType);
        if(root->LHS != NULL)
        printf("root->LHS: %s\n", root->LHS);
        if(root->RHS != NULL)
        printf("root->RHS: %s\n", root->RHS);
        fflush(stdout);
        char rightVar[50];
        char leftVar[50];
        if(strcmp(root->nodeType, "int") == 0
            || strcmp(root->nodeType, "float") == 0
            || strcmp(root->nodeType, "string") == 0
            || strcmp(root->nodeType, "flag") == 0) {
                return root->RHS;
        }
        if(strcmp(root->nodeType, "type") == 0) {
            if(root->right != NULL && strcmp(root->right->LHS, "array") == 0) {
                emitTypeArrayDeclaration(root->LHS, root->RHS, root->right->right->RHS);
            } else {
                emitTypeDeclaration(root->LHS, root->RHS);
            }
        }
        if(strcmp(root->nodeType, "variable parm") == 0){
            isParam = 1;
            emitTypeDeclaration(root->LHS, root->RHS);
            isParam = 0;
        }
        if(strcmp(root->nodeType, "array parm") == 0) {
            emitTypeArrayDeclaration(root->LHS, root->RHS, "-1");
        }
        // Handle Logical Statements
        if(strcmp(root->nodeType, "Logical") == 0) {
            // Set logical operation type variables
            if (strcmp(root->RHS, "Logical") == 0) {
                strcpy(logicalTypes[totalLogicalStatements], root->right->RHS);
            } else {
                strcpy(logicalTypes[totalLogicalStatements], root->RHS);
            }
            totalLogicalStatements++;

            // Traverse to both conditionals
            ASTTraversal(root->right->left);
            ASTTraversal(root->right->right);
        }
        if(strcmp(root->nodeType, "Comparison") == 0) {
            if (isLogical == 1 && currLogicalStatements != 0) {
                emitLogicalExpression(logicalTypes[totalLogicalStatements-currLogicalStatements]);
                emitComparisonExpression(ASTTraversal(root->right->left), root->right, ASTTraversal(root->right->right));
                currLogicalStatements++;
            } else if (isLogical == 1) {
                emitComparisonExpression(ASTTraversal(root->right->left), root->right, ASTTraversal(root->right->right));
                currLogicalStatements++;
            }
            else {
                emitComparisonExpression(ASTTraversal(root->right->right->left), root->right->RHS, ASTTraversal(root->right->right->right));
            }
        }
        if(strcmp(root->nodeType, "program") == 0 
            || strcmp(root->nodeType, "vardec") == 0
            || strcmp(root->nodeType, "FunDecl FunDeclListTail") == 0
            || strcmp(root->nodeType, "ParaDecl comma ParaDeclListTail") == 0
            || strcmp(root->nodeType, "statements") == 0
            || strcmp(root->nodeType, "IfStmtTail continue") == 0
            || strcmp(root->nodeType, "IfStmt") == 0) { 
            ASTTraversal(root->left);
            ASTTraversal(root->right);
        }

        if(strcmp(root->nodeType, "WhileL") == 0) {
            emitWhileConditionStatement();

            // Change logical statement indicator variable to active
            isLogical = !strcmp(root->LHS, "Logical");

            // Set memory for logical type string array
            logicalTypes = calloc(2500, sizeof(char));
            for (int i = 0; i < 50; i++) { logicalTypes[i] = malloc(5 * sizeof(char));}

            // Traverse to the left to generate logical and conditional statements
            ASTTraversal(root->left);
            isLogical = 0;
            currLogicalStatements = 0;
            totalLogicalStatements = 0;
            fprintf(IRcode, "\n");

            // Traverse to the right to generate block code
            ASTTraversal(root->right);

            // End the While statement
            emitWhileEndStatement();
        }

        if(strcmp(root->nodeType, "If") == 0) {
            emitIfConditionStatement();
            ASTTraversal(root->left);
            ASTTraversal(root->right);
            emitIfEndStatement();
        }

        if (strcmp(root->nodeType, "Elif") == 0) {
            emitIfConditionStatement();
            ASTTraversal(root->left);
            ASTTraversal(root->right);
            emitElifEndStatement();
        }

        if(strcmp(root->nodeType, "IfStmtTail else end") == 0) {
            if(strcmp(root->right, "") == 0) {
                return "";
            }
            ASTTraversal(root->right);
        }
        if(strcmp(root->nodeType, "Else") == 0) {
            ASTTraversal(root->right);
            emitElseEndStatement();

        }
        if(strcmp(root->nodeType, "write") == 0) {
            if(strcmp(root->RHS, "int") == 0
            || strcmp(root->RHS, "float") == 0
            || strcmp(root->RHS, "string") == 0) {
                updateUnusedVar(root->right->RHS);
                emitWritePrimary(root->right->RHS);
            } else if (strncmp(getPrimaryType(root->RHS), "var", 3) == 0) {
                emitWriteId(root->RHS);
            } else {
                // Get tempVar from ASTtraversal
                char * tempVar = ASTTraversal(root->right);

                // Emit write operation using temporary variable
                emitWriteId(tempVar);
            }
        }
        if(strcmp(root->nodeType, "writeln") == 0) {
            emitWriteLn();
        }
        if(strcmp(root->nodeType, "function context") == 0) {
            emitEntry(root->LHS);
            ASTTraversal(root->right);
        }
        if(strcmp(root->nodeType, "function") == 0) {
            ASTTraversal(root->left);
            ASTTraversal(root->right);
            emitExit();
        }
        if(strcmp(root->nodeType, "exprlist end") == 0) {
            if (root->RHS != NULL && root->RHS[0] != '\0') {
                strcpy(params[paramIndex], root->right->RHS);
                paramIndex += 1;
            }
        }
        if(strcmp(root->nodeType, "exprlist exprtail") == 0) {
            strcpy(params[paramIndex], root->left->RHS);
            paramIndex += 1;
            ASTTraversal(root->right);
        }
        if(strncmp(root->nodeType, "function call param list", 24) == 0) {
            memset(params, 0, 50 * 50);
            ASTTraversal(root->right);
        }
        if(strncmp(root->nodeType, "function call", 14) == 0) {
            char * funcVar = malloc(100*sizeof(char));
            ASTTraversal(root->right);
            strncpy(funcVar, root->LHS, 100);
            memset(buffer, 0, 50);
            strcpy(buffer, emitFunctionCall(funcVar));
            paramIndex = 0;
            return buffer;
        }
        if(strcmp(root->nodeType, "report") == 0) {
            strcpy(rightVar, ASTTraversal(root->right));
            emitReturn(rightVar);
        }
        if(strcmp(root->nodeType, "=") == 0) {
            strcpy(rightVar, ASTTraversal(root->right));
            if(strcmp(root->right->nodeType, "element assignment") == 0) {
                if(strcmp(root->right->RHS, "+") == 0
                    || strcmp(root->right->RHS, "-") == 0
                    || strcmp(root->right->RHS, "*") == 0
                    || strcmp(root->right->RHS, "/") == 0) {
                        // Check to see if the operation includes any array indexes
                        // If so, include the array callout in the binary operation
                        // Form leftVar variable
                        if (strncmp(getPrimaryType(root->right->right->left->LHS), "var", 3) == 0) {
                            sprintf(leftVar, "%s[%s]", root->right->right->left->LHS, root->right->right->left->RHS);
                        } else {
                            strcpy(leftVar, root->right->right->left->RHS);
                        }

                        // Form rightVar variable
                        if (strncmp(getPrimaryType(root->right->right->right->LHS), "var", 3) == 0) {
                            sprintf(rightVar, "%s[%s]", root->right->right->right->LHS, root->right->right->right->RHS);
                        } else {
                            strcpy(rightVar, root->right->right->right->RHS);
                        }
                        return emitBinaryOperation(root->right->RHS, leftVar, rightVar);
                    } else {
                        if (strncmp(getPrimaryType(root->right->right->LHS), "var", 3) == 0) {
                            sprintf(rightVar, "%s[%s]", root->right->right->LHS, root->right->right->RHS);
                        } else {
                            strcpy(rightVar, root->right->right->right->RHS);
                        }
                        emitAssignmentForElement(root->LHS, root->right->LHS, rightVar);
                    }
            } else {
                emitAssignment(root->LHS, rightVar);
            }
        }
        if(strcmp(root->nodeType, "block") == 0) {
            return ASTTraversal(root->right);
        }
        if(strcmp(root->nodeType, "and") == 0
            || strcmp(root->nodeType, "or") == 0) {
                ASTTraversal(root->left);
                ASTTraversal(root->right);
        }

        if(strcmp(root->nodeType, "+") == 0
            || strcmp(root->nodeType, "-") == 0
            || strcmp(root->nodeType, "*") == 0
            || strcmp(root->nodeType, "/") == 0)
            // || strcmp(root->nodeType, ">") == 0
            // || strcmp(root->nodeType, ">=") == 0
            // || strcmp(root->nodeType, "<") == 0
            // || strcmp(root->nodeType, "<=") == 0
            // || strcmp(root->nodeType, "==") == 0
            // || strcmp(root->nodeType, "!=") == 0) 
            {
                // Check to see if the operation includes any array indexes
                // If so, include the array callout in the binary operation
                // Form leftVar variable
                if (strncmp(getPrimaryType(root->left->LHS), "var", 3) == 0) {
                    // New changes here
                    if (strncmp(root->left->LHS, "function call", 14) == 0) {
                        strcpy(leftVar, ASTTraversal(root->left));
                    } else if (strncmp(root->left->LHS, "int", 3) == 0 || strncmp(root->left->LHS, "float", 5) == 0) {
                        strcpy(leftVar, root->left->left->RHS);
                    } else if (strncmp(root->left->RHS, "function call param list", 24) == 0) {
                        strcpy(leftVar, ASTTraversal(root->right));
                    } else {
                        sprintf(leftVar, "%s[%s]", root->left->LHS, root->left->RHS);
                    }
                } else {
                    strcpy(leftVar, ASTTraversal(root->left));
                }

                if (strncmp(getPrimaryType(root->right->LHS), "var", 3) == 0) {
                    // New changes here
                    if (strncmp(root->right->LHS, "function call", 14) == 0) {
                        strcpy(rightVar, ASTTraversal(root->right));
                    } else if (strncmp(root->right->LHS, "int", 3) == 0 || strncmp(root->right->LHS, "float", 5) == 0) {
                        strcpy(rightVar, root->right->left->RHS);
                    } else if (strncmp(root->right->RHS, "function call param list", 24) == 0) {
                        strcpy(rightVar, ASTTraversal(root->right));
                    } else {
                        sprintf(rightVar, "%s[%s]", root->right->LHS, root->right->RHS);
                    }
                } else {
                    strcpy(rightVar, ASTTraversal(root->right));
                }

                // Traverse to the left FIRST if there's an expression; avoids last missing expression problem
                if (strcmp(root->LHS, "+") == 0
                    || strcmp(root->LHS, "-") == 0
                    || strcmp(root->LHS, "*") == 0
                    || strcmp(root->LHS, "/") == 0
                    || strcmp(root->LHS, ">") == 0
                    || strcmp(root->LHS, ">=") == 0
                    || strcmp(root->LHS, "<") == 0
                    || strcmp(root->LHS, "<=") == 0
                    || strcmp(root->LHS, "==") == 0
                    || strcmp(root->LHS, "!=") == 0) {
                        return emitBinaryOperation(root->nodeType, ASTTraversal(root->left), rightVar);;
                }

                return emitBinaryOperation(root->nodeType, leftVar, rightVar);
        }

        if(strcmp(root->LHS, "array") == 0) {
            arrElVar = malloc(50*sizeof(char));
            strcat(arrElVar, root->nodeType);
            strcat(arrElVar, root->RHS);
            return arrElVar;
        }
        return "";
    }
}

// Main function for IRcode generation
// After IRcode is generated, close the file
void generateIRCode(){
    printf("\n\n----Generate IRCode----\n\n");
    initIRcodeFile();
    ASTTraversal(ast);
    fclose(IRcode);
}

// Function to traverse the AST tree
// This initializes creating all of the IRcode for optimized IRcode

/**
 * @brief Applied code Optimization techniques
 *          1. Constant Propogation
 *          2. Dead Code Elimination
 *          3. Constant Folding
 *          4. Copy propogation (Currently disabled)
 * @param root 
 * @return * Code* 
 */
char* ASTTraversalOptimized(struct AST* root) {
    if(root != NULL) {
        printf("root->nodeType: %s\n", root->nodeType);
        // if(root->LHS != NULL)
        // printf("root->LHS: %s\n", root->LHS);
        // if(root->RHS != NULL)
        // printf("root->RHS: %s\n", root->RHS);
        fflush(stdout);

        char rightVar[50];
        char leftVar[50];
        
        if(strcmp(root->nodeType, "int") == 0
            || strcmp(root->nodeType, "float") == 0
            || strcmp(root->nodeType, "string") == 0
            || strcmp(root->nodeType, "flag") == 0) {
                return root->RHS;
        }
        if(strcmp(root->nodeType, "type") == 0) {
            if (isUsedVar(root->RHS)) {
                if (root->right != NULL && strncmp(root->right->LHS, "array", 5) == 0) {
                    emitTypeArrayDeclarationOptimized(root->LHS, root->RHS, root->right->right->RHS);
                } else {
                    emitTypeDeclarationOptimized(root->LHS, root->RHS);
                }
            }
        }
        if(strcmp(root->nodeType, "program") == 0 
            || strcmp(root->nodeType, "vardec") == 0
            || strcmp(root->nodeType, "FunDecl FunDeclListTail") == 0
            || strcmp(root->nodeType, "ParaDecl comma ParaDeclListTail") == 0
            || strcmp(root->nodeType, "statements") == 0) { 
            ASTTraversalOptimized(root->left);
            ASTTraversalOptimized(root->right);
        }
        // TO-DO: Ircode Handling
        if(strcmp(root->nodeType, "WhileL") == 0 
            || strcmp(root->nodeType, "IfStmt") == 0
            || strcmp(root->nodeType, "IfStmtTail continue") == 0
            || strcmp(root->nodeType, "If") == 0
            || strcmp(root->nodeType, "Elif") == 0) {
            ASTTraversalOptimized(root->left);
            ASTTraversalOptimized(root->right);
        }
        // TO-DO: Ircode Handling
        if(strcmp(root->nodeType, "IfStmtTail else end") == 0
            || strcmp(root->nodeType, "Else") == 0) {
            ASTTraversalOptimized(root->right);
        }
        if(strcmp(root->nodeType, "variable parm") == 0){
            isParam = 1;
            emitTypeDeclarationOptimized(root->LHS, root->RHS);
            isParam = 0;
        }
        if(strcmp(root->nodeType, "array parm") == 0) {
            emitTypeArrayDeclarationOptimized(root->LHS, root->RHS, "-1");
        }
        if(strcmp(root->nodeType, "write") == 0) {
            if(strcmp(root->RHS, "int") == 0
            || strcmp(root->RHS, "float") == 0
            || strcmp(root->RHS, "string") == 0) {
                emitWritePrimaryOptimized(root->right->RHS);
            } else if (strncmp(getPrimaryType(root->RHS), "var", 3) == 0) {
                if (isUsedVar(root->RHS)) {
                    emitWriteIdOptimized(root->RHS);
                }
            } else {
                // Get tempVar from ASTtraversal
                char * tempVar = ASTTraversalOptimized(root->right);

                // Emit write operation using temporary variable
                emitWriteIdOptimized(tempVar);
            }
        }
        if(strcmp(root->nodeType, "writeln") == 0) {
            emitWriteLnOptimized();
        }
        if(strcmp(root->nodeType, "function context") == 0) {
            emitEntryOptimized(root->LHS);
            ASTTraversalOptimized(root->right);
        }
        if(strcmp(root->nodeType, "function") == 0) {
            if(isUsedVar(root->left->LHS)) {
                ASTTraversalOptimized(root->left);
                ASTTraversalOptimized(root->right);
                emitExit();
            }
        }
        if(strcmp(root->nodeType, "exprlist end") == 0) {
            if (root->right != NULL) {
                strcpy(params[paramIndex], root->right->RHS);
                paramIndex += 1;
            }
        }
        if(strcmp(root->nodeType, "exprlist exprtail") == 0) {
            strcpy(params[paramIndex], root->left->RHS);
            paramIndex += 1;
            if (isUsedVar(root->RHS)) {
                if (root->right != NULL && strcmp(root->right->LHS, "array") == 0) {
                    emitTypeArrayDeclarationOptimized(root->LHS, root->right->right->RHS, root->RHS);
                } else {
                    emitTypeDeclarationOptimized(root->LHS, root->RHS);
                }
            }
            ASTTraversalOptimized(root->right);
        }
        if(strncmp(root->nodeType, "function call param list", 24) == 0) {
            memset(params, 0, 50 * 50);
            if(isUsedVar(root->RHS)) {
                if(root->right != NULL && strcmp(root->right->LHS, "array") == 0) {
                    emitTypeArrayDeclarationOptimized(root->LHS, root->right->right->RHS, root->RHS);
                } else {
                    emitTypeDeclarationOptimized(root->LHS, root->RHS);
                }
            }
            ASTTraversalOptimized(root->right);
        }
        if(strncmp(root->nodeType, "function call", 14) == 0) {
            ASTTraversalOptimized(root->right);

            memset(buffer, 0, 50);
            strcpy(buffer, emitFunctionCallOptimized(root->LHS));
            paramIndex = 0;
            return buffer;
        }
        if(strcmp(root->nodeType, "report") == 0) {
            strcpy(rightVar, ASTTraversalOptimized(root->right));
            emitReturnOptimized(rightVar);
        }
        if(strcmp(root->nodeType, "block") == 0) {
            return ASTTraversalOptimized(root->right);
        }
        if(strcmp(root->nodeType, "=") == 0) {
            if (isUsedVar(root->LHS)) {
                strcpy(rightVar, ASTTraversalOptimized(root->right));
                if (strcmp(root->right->nodeType, "element assignment") == 0) {
                    if(strcmp(root->right->RHS, "+") == 0
                        || strcmp(root->right->RHS, "-") == 0
                        || strcmp(root->right->RHS, "*") == 0
                        || strcmp(root->right->RHS, "/") == 0) {
                            // Check to see if the operation includes any array indexes
                            // If so, include the array callout in the binary operation
                            // Form leftVar variable
                            if (strncmp(getPrimaryType(root->right->right->left->LHS), "var", 3) == 0) {
                                sprintf(leftVar, "%s[%s]", root->right->right->left->LHS, root->right->right->left->RHS);
                            } else {
                                strcpy(leftVar, root->right->right->left->RHS);
                            }

                            // Form rightVar variable
                            if (strncmp(getPrimaryType(root->right->right->right->LHS), "var", 3) == 0) {
                                sprintf(rightVar, "%s[%s]", root->right->right->right->LHS, root->right->right->right->RHS);
                            } else {
                                strcpy(rightVar, root->right->right->right->RHS);
                            }

                            return emitBinaryOperationOptimized(root->right->RHS, leftVar, rightVar);
                            // emitAssignmentForElement(root->LHS, root->right->LHS, root->right->right->RHS);
                        } else {
                            if (strncmp(getPrimaryType(root->right->right->LHS), "var", 3) == 0) {
                                sprintf(rightVar, "%s[%s]", root->right->right->LHS, root->right->right->RHS);
                            } else {
                                strcpy(rightVar, root->right->right->RHS);
                            }
                            emitAssignmentForElementOptimized(root->LHS, root->right->LHS, rightVar);
                        }
                } else {
                    char rightVarOptimized[50];
                    strcpy(rightVarOptimized, getVarConstant(rightVar));
                    emitAssignmentOptimized(root->LHS, rightVarOptimized);
                }
            }
        }
        if(strcmp(root->nodeType, "+") == 0
            || strcmp(root->nodeType, "-") == 0
            || strcmp(root->nodeType, "*") == 0
            || strcmp(root->nodeType, "/") == 0
            || strcmp(root->nodeType, ">") == 0
            || strcmp(root->nodeType, ">=") == 0
            || strcmp(root->nodeType, "<") == 0
            || strcmp(root->nodeType, "<=") == 0
            || strcmp(root->nodeType, "==") == 0
            || strcmp(root->nodeType, "!=") == 0) {
                char rightVarOptimized[50];
                char leftVarOptimized[50];

                // Check to see if the operation includes any array indexes
                // If so, include the array callout in the binary operation
                // Form leftVar variable
                if (strncmp(getPrimaryType(root->left->LHS), "var", 3) == 0) {
                    // New changes here
                    if (strncmp(root->left->LHS, "function call", 14) == 0) {
                        strcpy(leftVar, ASTTraversalOptimized(root->left));
                    } else if (strncmp(root->left->LHS, "int", 3) == 0 || strncmp(root->left->LHS, "float", 5) == 0) {
                        strcpy(leftVar, root->left->left->RHS);
                    } else if (strncmp(root->left->RHS, "function call param list", 24) == 0) {
                        strcpy(leftVar, ASTTraversalOptimized(root->right));
                    } else {
                        sprintf(leftVar, "%s[%s]", root->left->LHS, root->left->RHS);
                    }
                } else {
                    strcpy(leftVar, ASTTraversalOptimized(root->left));
                }

                // Form rightVar variable
                if (strncmp(getPrimaryType(root->right->LHS), "var", 3) == 0) {
                    // New changes here
                    if (strncmp(root->right->LHS, "function call", 14) == 0) {
                        strcpy(rightVar, ASTTraversalOptimized(root->right));
                    } else if (strncmp(root->right->LHS, "int", 3) == 0 || strncmp(root->right->LHS, "float", 5) == 0) {
                        strcpy(rightVar, root->right->left->RHS);
                    } else if (strncmp(root->right->RHS, "function call param list", 24) == 0) {
                        strcpy(rightVar, ASTTraversalOptimized(root->right));
                    } else {
                        sprintf(rightVar, "%s[%s]", root->right->LHS, root->right->RHS);
                    }
                } else {
                    strcpy(rightVar, ASTTraversalOptimized(root->right));
                }

                // Traverse to the left FIRST if there's an expression; avoids last missing expression problem
                if (strcmp(root->LHS, "+") == 0
                    || strcmp(root->LHS, "-") == 0
                    || strcmp(root->LHS, "*") == 0
                    || strcmp(root->LHS, "/") == 0
                    || strcmp(root->LHS, ">") == 0
                    || strcmp(root->LHS, ">=") == 0
                    || strcmp(root->LHS, "<") == 0
                    || strcmp(root->LHS, "<=") == 0
                    || strcmp(root->LHS, "==") == 0
                    || strcmp(root->LHS, "!=") == 0) {
                        char * newVar = getVarConstant(ASTTraversalOptimized(root->left));
                        strcpy(rightVarOptimized, getVarConstant(newVar));
                        strcpy(leftVarOptimized, getVarConstant(rightVar));
                        return emitBinaryOperationOptimized(root->nodeType, rightVarOptimized, leftVarOptimized);
                }

                strcpy(rightVarOptimized, getVarConstant(leftVar));
                strcpy(leftVarOptimized, getVarConstant(rightVar));

                return emitBinaryOperationOptimized(root->nodeType, rightVarOptimized, leftVarOptimized);
        }
        if(strcmp(root->LHS, "array") == 0) {
            memcpy(arrElVar, 0, 50);
            strcat(arrElVar, root->nodeType);
            strcat(arrElVar, root->RHS);
            return arrElVar;
        }
        return "";
    }
}

// Main function for optimized IRcode generation
// After IRcode is generated, close the file
// Moreover, flush the stdout buffer prior to proceeding to the next step
void generateIRCodeOptimized() {
    // Reset temp variable number
    lastIndex = 0;

    printf("\n\n----Perform Code Optimizations----\n\n");
    initIRcodeFileOptimized();
    ASTTraversalOptimized(ast);
    fclose(IRcodeOptimized);
    fflush(stdout);
}