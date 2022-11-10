#ifndef WEBGEN_H 
#define WEBGEN_H

void initAssemblyFile();

void generateModule();

char * getWATType(char * phrase);

int getMoveAmount(char * phrase);

void generateDataVariables();

void printNewLine();

void generateTextSection();

void completeFile();

void generateWATcode();


#endif