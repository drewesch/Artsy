#ifndef SEMANTIC_H 
#define SEMANTIC_H

void CheckGlobal(char* variableName, char* currentScope);
void CheckNumParams(char* func, char* exprList, char* currentScope);
void CheckParamTypes(char* funcName, char* exprList, char* currentScope);
char* CheckPrimaryType(char*arg1, char*scope);
char* CheckAssignmentType(char*identifier, char* exp, char* scope);

// Header file for all semantic check functions

#endif


