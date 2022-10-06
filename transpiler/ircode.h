#ifndef IRCODE_H 
#define IRCODE_H


// ---- Functions to handle IR code emissions ---- //

void initIRcodeFile();

void emitBinaryOperation(char op[1], const char* id1, const char* id2);

void emitAssignment(char * id1, char * id2);

void emitConstantIntAssignment (char id1[50], char id2[50]);

void emitWriteId(char * id);
    

#endif