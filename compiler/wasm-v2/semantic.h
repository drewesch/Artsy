#ifndef SEMANTIC_H 
#define SEMANTIC_H

char* CheckPrimaryType(char*arg1, char*scope);
char* CheckAssignmentType(char*identifier, char* exp, char* scope);
int isAlpha(char * phrase);
int isInt(char * phrase);
int isFloat(char * phrase);
char * getPrimaryType(char * phrase);
void checkIntDivisionError(int numerator, int denominator);
void checkFloatDivisionError(float numerator, float denominator);

// Header file for all semantic check functions

#endif


