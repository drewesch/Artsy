#ifndef CODEGEN_H 
#define CODEGEN_H

void initAssemblyFile();

// ---- Functions to handle MIPS code generation ---- //

void emitMIPSAsisgnment(char id1[50], char id2[50]);

void emitMIPSConstantIntAssignment(char id1[50], char id2[50]);

void emitMIPSWriteID(char * id);

void emitMIPSAddOp(char * id1, char * id2);

void emitEndOfAssemblyCode();

void generateMIPScode();


#endif