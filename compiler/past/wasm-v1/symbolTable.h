//Symbol table header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header file for all semantic check functions
// This is a simplistic implementation, will be expanded on later

// Create a struct with a list of all items that variables within a scope will contain after variable declaration
struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
	int arrayLength;
	char scope[50];     // global, or the name of the function
	char used;
};


// Single scope and scope index declaration
extern struct Entry symTabItems[100];
extern int symTabIndex;

// Symbol table functions for adding items and accessing specific data types
void symTabAccess(void);

void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]);

void showSymTable();

int found(char itemName[50], char scope[50]);

char* getItemType(char itemName[50], char scope[50]);

int compareTypes(char item1[50], char item2[50], char scope[50]);