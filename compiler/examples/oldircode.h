#ifndef IRCODE_H 
#define IRCODE_H

extern struct AST* ast;

// Struct to handle temporary variable construction
struct ConstantVar {
    char var[50];
    char scope[50];
    int val;
};

// Generate symbol table of temporary variables
struct ConstantVar cvTable[100];


// Temporary variable struct to determine if a variable has been used in optimization
struct Var {
    char var[50];
    int boolVal;
};

// Generate symbol table for variable usage
struct Var uvTable[100];

struct node {
    char var[50];
    char rootVar[50];
};

struct nodeInfo {
    char tempVar[50];
    char leftVar[50];
    char rightVar[50];
    char rootVar[50];
};

struct node nodeTable[100];
struct nodeInfo bnodeTable[200];

// ---- Functions to handle IR code emissions ---- //

void initIRcodeFile();

char* emitBinaryOperation(char op[1], const char* id1, const char* id2);

void emitAssignment(char * id1, char * id2);

void emitConstantIntAssignment(char id1[50], char id2[50]);

void emitWriteId(char * id);

void emitAddOperation(char * id1, char * id2);

void generateIRCode(); 

void generateIRCodeOptimized();

#endif