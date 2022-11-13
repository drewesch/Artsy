#ifndef WEBGEN_H 
#define WEBGEN_H

void initAssemblyFile();

void generateModule();

char * getWATType(char * phrase);

int getMoveAmount(char * phrase);

int isAlpha(char * phrase);

int isInt(char * phrase);

int isFloat(char * phrase);

char * getPrimaryType(char * phrase);

void printNewLine();

void generateTextSection();

void completeFile();

void generateWATcode();

#endif