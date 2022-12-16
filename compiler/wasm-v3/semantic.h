#ifndef SEMANTIC_H 
#define SEMANTIC_H

// Header file for all semantic check functions

void CheckGlobal(char* variableName, char* currentScope);
char* CheckPrimaryType(char*arg1, char*scope);
void CheckID(char * identifier, char * currentScope);
void CheckAssignmentType(char * identifier, char * exprType, char * currentScope);
void CheckOperationType(char * leftExpr, char * rightExpr);
void CheckIndexOutOfBound(char * identifier, char * integer, char * currentScope);
int isAlpha(char * phrase);
int isInt(char * phrase);
int isFloat(char * phrase);
char * getPrimaryType(char * phrase);
void checkIntDivisionError(int numerator, int denominator);
void checkFloatDivisionError(float numerator, float denominator);

#endif


