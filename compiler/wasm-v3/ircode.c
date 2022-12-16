#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ircode.h"
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
int startIR = 0;
int startIROptimized = 0;
int lastIndex = 0;
int lastArrayTempIndex = 0;
char outputId[50];
char buffer[50];
char arrElVar[50];
char c[50][50];
int cindex = 0;

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

// Use the cvTable to find the temporary variable for a given variable declaration
char* getVarConstant(char var[50]){
	for(int i=0; i<cvIndex; i++){
		int str1 = strcmp(cvTable[i].var, var);
        if( str1 == 0){
            memset(buffer, 0, 50);
            printf("cvTable[%d].var: %s\n", i, cvTable[i].var);
            printf("cvTable[%d].val: %d\n", i, cvTable[i].val);
			sprintf(buffer, "%d", cvTable[i].val);
            return buffer;
		}
	}
	return var;
}

// Function to update variable declarations if the variable is unused - part of the optimization process
void updateUnusedVar(char var[50]) {

    // printf("updateUnused: %s\n", var);
	for(int i=0; i<uvIndex; i++){
		int str1 = strcmp(uvTable[i].var, var);
        if( str1 == 0){
            uvTable[i].boolVal = 1;
            return;
		}
	}
}

// Checks the symbol table
// Returns true or false depending if the variable is used or not (for code optimization)
int isUsedVar(char var[50]) {
    for(int i=0; i<uvIndex; i++){
		int str1 = strcmp(uvTable[i].var, var);
        if( str1 == 0){
            return uvTable[i].boolVal;
		}
	}
    return 0;
}

// For unoptimized IRcode
// Generates the IRcode for assignments
char* emitBinaryOperation(char op[1], const char* id1, const char* id2){
    // Opens IRcode file if it is not open already
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Create a temporary variable assignment using "T"
    memset(outputId, 0, 50);
    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);

    // Updates the declaration if the variable is unused
    if (strncmp(getPrimaryType(id1), "var", 3) == 0) {
        updateUnusedVar(id1);
    }
    if (strncmp(getPrimaryType(id2), "var", 3) == 0) {
        updateUnusedVar(id2);
    }

    // Output suboperation type (for webgen parsing)
    if (!startSubOp) {
        char * opType;
        
        if (strncmp(getPrimaryType(id1), "var", 3) == 0) {
            opType = getItemType(id1, currIRScope);
        } else {
            opType = getPrimaryType(id1);
        }

        fprintf(IRcode, "subop %s\n", opType);
        startSubOp = 1;
    }

    // Print the unoptimized iRcode using outputIDs, the operator, and the other ids
    fprintf(IRcode, "%s = %s %s %s\n", outputId, id1, op, id2);
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

// Optimized versiion of binary operations for IRcodeOptimized.ir
char* emitBinaryOperationOptimized(char op[1], const char* id1, const char* id2){
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    memset(outputId, 0, 50);

    char * opType = getPrimaryType(id1);

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
        char * opType;

        if (strncmp(getPrimaryType(id1), "var", 3) == 0) {
            opType = getItemType(id1, currIRScope);
        } else {
            opType = getPrimaryType(id1);
        }

        fprintf(IRcodeOptimized, "subop %s\n", opType);
        startSubOpOptimized = 1;
    }

    // Output optimized suboperation line
    fprintf(IRcodeOptimized, "%s = %s %s %s\n", outputId, id1, op, id2);
    lastIndex += 1;

    return outputId;
}

// Unoptimized IRcode operation for variable assignment
void emitAssignment(char * id1, char * id2){
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Print the assignment statement using the two basic IDs
    fprintf(IRcode, "%s = %s\n", id1, id2);
    // lastIndex = 0;

    // Indicate subop stop
    startSubOp = 0;
}

// Unoptimized IRcode operation for variable assignment (for array)
void emitAssignmentForElement(char *id1, char * elementNum, char * id2) {
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Print the assignment statement using the two basic IDs with an element number
    fprintf(IRcode, "%s[%s] = %s\n", id1, elementNum, id2);
    // lastIndex = 0;
}

void emitAssignmentForElementOptimized(char *id1, char * elementNum, char * id2) {
    // Open IRfile if it is not open
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    // Print the assignment statement using the two basic IDs with an element number
    fprintf(IRcodeOptimized, "%s[%s] = %s\n", id1, elementNum, id2);
    // lastIndex = 0;
}

// Optimized assignment operation function for IRcodeOptimized.ir
void emitAssignmentOptimized(char * id1, char * id2){
    int flag = 1;
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }
    if(isnumeric(id2)) {
        for(int i=0; i<cvIndex; i++){
            int str1 = strcmp(cvTable[i].var, id1);
            if( str1 == 0){
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

        // else {
    //     if(isUninitializedNodeVar(id2)) {
    //         strcpy(nodeTable[nodeIndex].var, id2);
    //         strcpy(nodeTable[nodeIndex].rootVar, id2);
    //         nodeIndex ++;
    //     }

    //     if(isUninitializedNodeVar(id1)) {
    //         strcpy(nodeTable[nodeIndex].var, id1);
    //         strcpy(nodeTable[nodeIndex].rootVar, nodeTable[getNodeVarIndex(id2)].rootVar);
    //         nodeIndex ++;
    //     } else {
    //         strcpy(nodeTable[getNodeVarIndex(id1)].rootVar, nodeTable[getNodeVarIndex(id2)].rootVar);
    //     }
    // }

    fprintf(IRcodeOptimized, "%s = %s\n", id1, id2);
    
    // Indicate subop stop
    startSubOpOptimized = 0;

    // lastIndex = 0;
}

void emitWriteNum(char * value) {
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }
    fprintf(IRcode, "output %s\n", value);
}

void emitWriteString(char * value) {
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }
    fprintf(IRcode, "output \"%s\"\n", value);
}

// Unoptimized IRcode operation for the write keyword
void emitWriteId(char * id){
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Update the code if it is unused
    if (strncmp(getPrimaryType(id), "var", 3) == 0) {
        updateUnusedVar(id);
    }
    fprintf(IRcode, "output %s\n", id);
}

void emitWriteLn(){
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    fprintf(IRcode, "nextline\n");
}

void emitWriteLnOptimized(){
    // Open IRfile if it is not open
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    fprintf(IRcode, "nextline\n");
}

// Optimized IRCode operation for writing 
void emitWriteIdOptimized(char * id){
    // Opens IRcodeOptimized file is it is not open
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    // Print output keyword with the associated ID
    // Unused variables are already removed prior to this step, so it is redundant to include it here
    fprintf(IRcodeOptimized, "output %s\n", id);
}

// Outputs the variable and type for variable declaration (unoptimized)
void emitTypeDeclaration(char * type, char * id){
    // Flag variable for unused code optimization testing
    int flag = 1;
    
    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";
    
    // Opens the IRcode file if it is not open already
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Check the whole UV table
    // If the type is unused, do not generate IRcode
    for(int i=0; i<uvIndex; i++){
        int str1 = strcmp(uvTable[i].var, id);
        if( str1 == 0){ flag = 0; break; }
    }
    // If the flag is still true, continue with generating IRcode, update the table, and increase the uvIndex
    if(flag) {
        strcpy(uvTable[uvIndex].var, id);
        uvTable[uvIndex].boolVal = 0;
        uvIndex ++;
    }

    if(isParam) {
        varType = "param";
    }

    // Print variable declaration IRcode to file
    fprintf(IRcode, "%s %s %s\n", varType, type, id);
}

// Outputs the variable and type for variable declaration (unoptimized) (for array)
void emitTypeArrayDeclaration(char * type, char * id, char * size){
    // Flag variable for unused code optimization testing
    int flag = 1;

    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";
    
    // Opens the IRcode file if it is not open already
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Check the whole UV table
    // If the type is unused, do not generate IRcode
    for(int i=0; i<uvIndex; i++){
        int str1 = strcmp(uvTable[i].var, id);
        if( str1 == 0){ flag = 0; break; }
    }
    // If the flag is still true, continue with generating IRcode, update the table, and increase the uvIndex
    if(flag) {
        strcpy(uvTable[uvIndex].var, id);
        uvTable[uvIndex].boolVal = 0;
        uvIndex ++;
    }

    if(isParam) {
        varType = "param";
    }

    if(atoi(size) >= 0) {
        // Print variable declaration IRcode to file
        fprintf(IRcode, "%s %s %s array %s\n", varType, type, id, size);
    } else {
        fprintf(IRcode, "%s %s %s array\n", varType, type, id);
    }
}

// Emit the type declaration for optimized IRcode file
void emitTypeDeclarationOptimized(char * type, char * id){
    // Open the IRcodeOptimized.ir file if it is not open already
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    // Char variable to determine if the variable is a type or a parameter
    char * varType = "type";

    if(isParam) {
        varType = "param";
    }

    // Already includes optimizations prior to this step, so doing optimization beforehand is redundant
    // Print variable declaration IRcode to file
    fprintf(IRcodeOptimized, "%s %s %s\n", varType, type, id);
}

// Outputs the variable and type for variable declaration (unoptimized) (for array)
void emitTypeArrayDeclarationOptimized(char * type, char * id, char * size){
    // Flag variable for unused code optimization testing
    int flag = 1;
    
    // Opens the IRcode file if it is not open already
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

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
    
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Check the whole UV table
    // If the type is unused, do not generate IRcode
    for(int i=0; i<uvIndex; i++){
        int str1 = strcmp(uvTable[i].var, id);
        if( str1 == 0){ flag = 0; break; }
    }
    // If the flag is still true, continue with generating IRcode, update the table, and increase the uvIndex
    if(flag) {
        strcpy(uvTable[uvIndex].var, id);
        uvTable[uvIndex].boolVal = 0;
        uvIndex ++;
    }

    // Get type and update current scope
    char * type = getItemType(id, currIRScope);
    currIRScope = id;

    fprintf(IRcode, "entry %s %s\n", type, id);
}

void emitEntryOptimized(char * id) {    
    // Open IRfile if it is not open
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    char * type = getItemType(id, currIRScope);
    currIRScope = id;

    fprintf(IRcodeOptimized, "entry %s %s\n", type, id);
}

void emitReturn(char * id) {
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    // Updates the variable if it is unused
    if (strncmp(getPrimaryType(id), "var", 3) == 0) {
        updateUnusedVar(id);
    }

    fprintf(IRcode, "return %s\n", id);
}

void emitReturnOptimized(char * id) {
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }
    
    fprintf(IRcodeOptimized, "return %s\n", id);
}

void emitExit() {
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

    currIRScope = "global";
    fprintf(IRcode, "exit\n");
}

void emitExitOptimized() {
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    currIRScope = "global";
    fprintf(IRcodeOptimized, "exit\n");
}

char * emitFunctionCall(char *id) {
    // Open IRfile if it is not open
    if (startIR == 0) {
        initIRcodeFile();
        startIR = 1;
    }

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
    if (!startSubOp) {
        char * opType;
        
        if (strncmp(getPrimaryType(id), "var", 3) == 0) {
            opType = getItemType(id, currIRScope);
        } else {
            opType = getPrimaryType(id);
        }

        fprintf(IRcode, "subop %s\n", opType);
        startSubOp = 1;
    }

    fprintf(IRcode, "%s = call %s args", outputId, id);

    for(int i = 0; i < cindex; i ++) {
        // Update variable if unused
        if (strncmp(getPrimaryType(c[i]), "var", 3) == 0) {
            updateUnusedVar(c[i]);
        }

        fprintf(IRcode, " %s", c[i]);
    }
    fprintf(IRcode, "\n");
    lastIndex += 1;

    return outputId;
}

char * emitFunctionCallOptimized(char *id) {
    // Open IRfile if it is not open
    if (startIROptimized == 0) {
        initIRcodeFileOptimized();
        startIROptimized = 1;
    }

    memset(outputId, 0, 50);
    char currLabelIndexBuffer[50];
    sprintf(currLabelIndexBuffer, "%d", lastIndex);
    strcat(outputId, "T");
    strcat(outputId, currLabelIndexBuffer);

    // Output suboperation type (for webgen parsing)
    if (!startSubOpOptimized) {
        char * opType;
        
        if (strncmp(getPrimaryType(id), "var", 3) == 0) {
            opType = getItemType(id, currIRScope);
        } else {
            opType = getPrimaryType(id);
        }

        fprintf(IRcodeOptimized, "subop %s\n", opType);
        startSubOpOptimized = 1;
    }

    fprintf(IRcodeOptimized, "%s = call %s args", outputId, id);

    for(int i = 0; i < cindex; i ++) {
        fprintf(IRcodeOptimized, " %s", c[i]);
    }
    fprintf(IRcodeOptimized, "\n");
    lastIndex += 1;

    return outputId;
}

// Function to traverse the AST tree
// This initializes creating all of the IRcode for unoptimized IRcode
char* ASTTraversal(struct AST* root) {
    if(root != NULL) {
        printf("root -> nodeType: %s\n", root -> nodeType);
        fflush(stdout);
        char rightVar[50];
        char leftVar[50];
        if(strcmp(root -> nodeType, "int") == 0
            || strcmp(root -> nodeType, "float") == 0
            || strcmp(root -> nodeType, "string") == 0) {
            return root -> RHS;
        }
        if(strcmp(root->nodeType, "type") == 0) {
            if(root -> right != NULL && strcmp(root -> right -> LHS, "array") == 0) {
                emitTypeArrayDeclaration(root -> LHS, root -> RHS, root -> right -> right -> RHS);
            } else {
                emitTypeDeclaration(root -> LHS, root -> RHS);
            }
        }
        if(strcmp(root->nodeType, "variable parm") == 0){
            isParam = 1;
            emitTypeDeclaration(root -> LHS, root -> RHS);
            isParam = 0;
        }
        if(strcmp(root->nodeType, "array parm") == 0) {
            emitTypeArrayDeclaration(root -> LHS, root ->RHS, "-1");
        }
        if(strcmp(root->nodeType, "program") == 0 
            || strcmp(root->nodeType, "vardec") == 0
            || strcmp(root->nodeType, "FunDecl FunDeclListTail") == 0
            || strcmp(root->nodeType, "ParaDecl comma ParaDeclListTail") == 0
            || strcmp(root->nodeType, "block") == 0
            || strcmp(root->nodeType, "statements") == 0) { 
            ASTTraversal(root -> left);
            ASTTraversal(root -> right);
        }
        if(strcmp(root->nodeType, "write") == 0) {
            if(strcmp(root-> right, "int")
            || strcmp(root-> right, "float")) {
                emitWriteNum(root -> right -> RHS);
            } else if(strcmp(root-> right, "string")) {
                emitWriteString(root -> right -> RHS);
            }else {
                emitWriteId(root -> RHS);
            }
        }
        if(strcmp(root->nodeType, "writeln") ==0) {
            emitWriteLn();
        }
        if(strcmp(root->nodeType, "function context") == 0) {
            emitEntry(root -> LHS);
            ASTTraversal(root -> right);
        }
        if(strcmp(root->nodeType, "function") == 0) {
            ASTTraversal(root -> left);
            ASTTraversal(root -> right);
            emitExit();
        }
        if(strcmp(root->nodeType, "exprlist end") == 0) {
            if (root->right != NULL) {
                strcpy(c[cindex], root -> right -> RHS);
                cindex += 1;
            }
        }
        if(strcmp(root->nodeType, "exprlist exprtail") == 0) {
            strcpy(c[cindex], root -> left -> RHS);
            cindex += 1;
            ASTTraversal(root -> right);
        }
        if(strcmp(root->nodeType, "function call param list") == 0) {
            memset(c, 0, 50 * 50);
            ASTTraversal(root -> right);
        }
        if(strcmp(root->nodeType, "function call") == 0) {
            ASTTraversal(root -> right);

            memset(buffer, 0, 50);
            strcpy(buffer, emitFunctionCall(root -> LHS));
            cindex = 0;
            return buffer;
        }
        if(strcmp(root -> nodeType, "return") == 0) {
            strcpy(rightVar, ASTTraversal(root-> right));
            emitReturn(rightVar);
        }
        if(strcmp(root->nodeType, "=") == 0) {
            strcpy(rightVar, ASTTraversal(root-> right));
            if(strcmp(root -> right -> nodeType, "element assignment") == 0) {
                emitAssignmentForElement(root -> LHS, root -> right -> LHS, root -> right -> right -> RHS);
            } else {
                emitAssignment(root -> LHS, rightVar);
            }
        }
        if(strcmp(root -> nodeType, "+") == 0
            || strcmp(root -> nodeType, "-") == 0
            || strcmp(root -> nodeType, "*") == 0
            || strcmp(root -> nodeType, "/") == 0) {
            strcpy(leftVar, ASTTraversal(root-> left));
            strcpy(rightVar, ASTTraversal(root-> right));
            return emitBinaryOperation(root -> nodeType, leftVar, rightVar);
        }
        if(strcmp(root -> LHS, "array") == 0) {
            memcpy(arrElVar, 0, 50);
            strcat(arrElVar, root -> nodeType);
            strcat(arrElVar, root-> RHS);
            return arrElVar;
        }
        return "";
    }
}

// Main function for IRcode generation
// After IRcode is generated, close the file
void generateIRCode(){
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
        char rightVar[50];
        char leftVar[50];
        if(strcmp(root -> nodeType, "int") == 0
            || strcmp(root -> nodeType, "float") == 0
            || strcmp(root -> nodeType, "string") == 0) {
            return root -> RHS;
        }
        if(strcmp(root->nodeType, "type") == 0) {
            if(isUsedVar(root -> RHS)) {
                if(root -> right != NULL && strcmp(root -> right -> LHS, "array") == 0) {
                    emitTypeArrayDeclarationOptimized(root -> LHS, root -> RHS, root -> right -> right -> RHS);
                } else {
                    emitTypeDeclarationOptimized(root -> LHS, root -> RHS);
                }
            }
        }
        if(strcmp(root->nodeType, "program") == 0 
            || strcmp(root->nodeType, "vardec") == 0
            || strcmp(root->nodeType, "FunDecl FunDeclListTail") == 0
            || strcmp(root->nodeType, "ParaDecl comma ParaDeclListTail") == 0
            || strcmp(root->nodeType, "block") == 0
            || strcmp(root->nodeType, "statements") == 0) { 
            ASTTraversalOptimized(root -> left);
            ASTTraversalOptimized(root -> right);
        }
        if(strcmp(root->nodeType, "variable parm") == 0){
            isParam = 1;
            emitTypeDeclarationOptimized(root -> LHS, root -> RHS);
            isParam = 0;
        }
        if(strcmp(root->nodeType, "array parm") == 0) {
            emitTypeArrayDeclarationOptimized(root -> LHS, root ->RHS, "-1");
        }
        if(strcmp(root->nodeType, "write") == 0) {
            if(strcmp(root-> right, "int")
            || strcmp(root-> right, "float")) {
                emitWriteNum(root -> right -> RHS);
            } else if(strcmp(root-> right, "string")) {
                emitWriteString(root -> right -> RHS);
            }else {
                if(isUsedVar(root -> RHS)) {
                    emitWriteIdOptimized(root -> RHS);
                }
            }
        }
        if(strcmp(root->nodeType, "writeln") ==0) {
            emitWriteLnOptimized();
        }
        if(strcmp(root->nodeType, "function context") == 0) {
            emitEntryOptimized(root -> LHS);
            ASTTraversalOptimized(root -> right);
        }
        if(strcmp(root->nodeType, "function") == 0) {
            if(isUsedVar(root -> left -> LHS)) {
                ASTTraversalOptimized(root -> left);
                ASTTraversalOptimized(root -> right);
                emitExit();
            }
        }
        if(strcmp(root->nodeType, "exprlist end") == 0) {
            if (root->right != NULL) {
                strcpy(c[cindex], root -> right -> RHS);
                cindex += 1;
            }
        }
        if(strcmp(root->nodeType, "exprlist exprtail") == 0) {
            strcpy(c[cindex], root -> left -> RHS);
            cindex += 1;
            if(isUsedVar(root -> RHS)) {
                if(root -> right != NULL && strcmp(root -> right -> LHS, "array") == 0) {
                    emitTypeArrayDeclarationOptimized(root -> LHS, root -> right -> right -> RHS, root -> RHS);
                } else {
                    emitTypeDeclarationOptimized(root -> LHS, root -> RHS);
                }
            }
            ASTTraversalOptimized(root -> right);
        }
        if(strcmp(root->nodeType, "function call param list") == 0) {
            memset(c, 0, 50 * 50);
            if(isUsedVar(root -> RHS)) {
                if(root -> right != NULL && strcmp(root -> right -> LHS, "array") == 0) {
                    emitTypeArrayDeclarationOptimized(root -> LHS, root -> right -> right -> RHS, root -> RHS);
                } else {
                    emitTypeDeclarationOptimized(root -> LHS, root -> RHS);
                }
            }
            ASTTraversalOptimized(root -> right);
        }
        if(strcmp(root->nodeType, "function call") == 0) {
            ASTTraversalOptimized(root -> right);

            memset(buffer, 0, 50);
            strcpy(buffer, emitFunctionCallOptimized(root -> LHS));
            cindex = 0;
            return buffer;
        }
        if(strcmp(root -> nodeType, "return") == 0) {
            strcpy(rightVar, ASTTraversalOptimized(root-> right));
            emitReturnOptimized(rightVar);
        }
        if(strcmp(root->nodeType, "=") == 0) {
            if(isUsedVar(root -> LHS)) {
                strcpy(rightVar, ASTTraversalOptimized(root-> right));
                if(strcmp(root -> right -> nodeType, "element assignment") == 0) {
                    emitAssignmentForElementOptimized(root -> LHS, root -> right -> LHS, root -> right -> right -> RHS);
                } else {
                    char rightVarOptimized[50];
                    strcpy(rightVarOptimized, getVarConstant(rightVar));
                    emitAssignmentOptimized(root -> LHS, rightVarOptimized);
                }
            }
        }
        if(strcmp(root -> nodeType, "+") == 0
            || strcmp(root -> nodeType, "-") == 0
            || strcmp(root -> nodeType, "*") == 0
            || strcmp(root -> nodeType, "/") == 0) {
            strcpy(leftVar, ASTTraversalOptimized(root-> left));
            strcpy(rightVar, ASTTraversalOptimized(root-> right));
            char rightVarOptimized[50];
            char leftVarOptimized[50];
            strcpy(rightVarOptimized, getVarConstant(leftVar));
            strcpy(leftVarOptimized, getVarConstant(rightVar));
            return emitBinaryOperationOptimized(root -> nodeType, rightVarOptimized, leftVarOptimized);
        }
        if(strcmp(root -> LHS, "array") == 0) {
            memcpy(arrElVar, 0, 50);
            strcat(arrElVar, root -> nodeType);
            strcat(arrElVar, root-> RHS);
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

    ASTTraversalOptimized(ast);
    fclose(IRcodeOptimized);
    fflush(stdout);
}