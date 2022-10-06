//Symbol table header
#include <stdio.h>
#include <ctype.h>
#include <string.h> 

// This is a very simplistic implementation of a symbol table
// You will use this as reference and build a much more robust one

struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
	int arrayLength;
	char scope[50];     // global, or the name of the function
};

struct Entry symTabItems[100];
int symTabIndex = 0;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
		// what about scope? should you add scope to this function?
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, itemName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		symTabItems[symTabIndex].arrayLength = arrayLength;
		strcpy(symTabItems[symTabIndex].scope, scope);
		symTabIndex++;
	
}

void showSymTable(){
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemScope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6d %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
	}
	

	printf("-----------------------------------------------------------------------\n");
}

int found(char itemName[50], char scope[50]){
	// Lookup an identifier in the symbol table
	// what about scope?
	// return TRUE or FALSE
	// Later on, you may want to return additional information
	for(int i=0; i<symTabIndex; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return 1; // found the ID in the table
		}
	}
	return 0;
}

char* getItemType(char itemName[50], char scope[50]) {
	// TK
}

int compareTypes(char item1[50], char item2[50], char scope[50]) {
	// TK
}