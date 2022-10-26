#include "symbolTable.h"

// Function to reference getItemType in symbol table
char* getItemType(char itemName[50], char scope[50]);

// Single Scope declaration
// This approach will change in the next iteration
struct Entry symTabItems[100];
int symTabIndex;

// Simple function to notify user that the table has been accessed successfully
void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

// Add a single entry struct to the symbol table for the appropriate scope
void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
	// Set entry struct item data for each parameter in the function
	symTabItems[symTabIndex].itemID = symTabIndex;
	strcpy(symTabItems[symTabIndex].itemName, itemName);
	strcpy(symTabItems[symTabIndex].itemKind, itemKind);
	strcpy(symTabItems[symTabIndex].itemType, itemType);
	symTabItems[symTabIndex].arrayLength = arrayLength;
	strcpy(symTabItems[symTabIndex].scope, scope);

	// Increment the symbol table index for this scope
	symTabIndex++;
	
}

struct Entry* getParamList(char * id, struct AST* paramlist) {
	struct Entry * list = malloc(sizeof(struct Entry));	
	if(strcmp(paramlist->nodeType, "Variable parm") == 0) {
		list -> itemID = symTabIndex;
		strcpy(list->itemName, paramlist->RHS);
		strcpy(list->itemKind, "Var");
		strcpy(list->itemType, paramlist->LHS);
		list->arrayLength = 0;
		strcpy(list->scope, id);
		list->paramlist = 0;

		return list;
	}
	else if(strcmp(paramlist->nodeType, "ParaDecl comma ParaDeclListTail") == 0) {
		list = getParamList(id, paramlist -> left);
		list->paramlist = getParamList(id, paramlist -> right);
	}

	return list;

}

void addFunction(char *type, char *id, struct AST* paramlist){
	//printf("ADD Function:------------------------- %s\n---------------------\n", id);
	//showAST(paramlist);
	
	if (paramlist == 0){
		symTabItems[symTabIndex].paramlist = 0;
	}
	else if (strcmp(paramlist->nodeType, "Variable parm") == 0){
		
		struct Entry* list = malloc(sizeof(struct Entry));
		strcpy(list->itemName, paramlist->LHS);
		strcpy(list->itemKind, "variable");
		strcpy(list->itemType, paramlist->RHS);
		list->arrayLength = 0;
		strcpy(list->scope, id);
		list->paramlist = 0;
		symTabItems[symTabIndex].paramlist = list;
	} else if(strcmp(paramlist->nodeType, "ParaDecl comma ParaDeclListTail") == 0) {		

		symTabItems[symTabIndex].paramlist = getParamList(id, paramlist);
	}

	// Set entry struct item data for each parameter in the function
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, id);
		strcpy(symTabItems[symTabIndex].itemKind, "function");
		strcpy(symTabItems[symTabIndex].itemType, type);
		symTabItems[symTabIndex].arrayLength = 0;
		strcpy(symTabItems[symTabIndex].scope, "global");
		printf("check");

		// Increment the symbol table index for this scope
		symTabIndex++;
}

void showSymTable(){
	// Show the format of the symboltable using the scope's current entries
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemScope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6d %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope);
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				printf("%5d %15s  %7s  %7s %6d %15s \n",tempList -> itemID, tempList -> itemName, tempList -> itemKind, tempList ->itemType, tempList  -> arrayLength, tempList ->scope);
				tempList = tempList -> paramlist;
			}
		}
	}
	

	printf("-----------------------------------------------------------------------\n");
}

int found(char itemName[50], char scope[50]){
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++) {
		if (symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList -> itemName, itemName);
				int str2 = strcmp(tempList -> scope, scope);

				// If these strings are the same, return true
				if( str1 == 0 && str2 == 0){
					return 1; // found the ID in the table
				}
				tempList = tempList -> paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope, scope);
		int str3 = strcmp(symTabItems[i].scope, "global");

		// If these strings are the same, return true
		if (str1 == 0 && (str2 == 0 || str3 == 0)) {
			return 1; // found the ID in the table
		}
	}
	
	// Else, return false
	return 0;
}

/*
char* getItemType(char itemName[50], char scope[50]) {
	// Using a for loop for the scope, test to see if this item exists
	// If it does, return the index's item type
	for(int i=0; i<100; i++){
		if (found(itemName, scope)) {
			// found the type in the table
			//printf("Found item! Item Type: %s\n", symTabItems[i].itemType);
			return symTabItems[i].itemType;
		}
	}
	
	// If it isn't found, state this and return a semantic error
	printf("ERROR: Item not found.\n\n");
	exit(1);
}
*/

char* getItemType(char itemName[50], char scope[50]) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList -> itemName, itemName);
				int str2 = strcmp(tempList -> scope,scope);

				// If these strings are the same, return true
				if( str1 == 0 && str2 == 0){
					return symTabItems[i].itemType;
				}
				tempList = tempList -> paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope, scope);
		int str3 = strcmp(symTabItems[i].scope, "global");

		// If these strings are the same, return true
		if( str1 == 0 && (str2 == 0 || str3 == 0)){
			//printf("Found: %s\n-----------------------", itemName);
			return symTabItems[i].itemType;
		}
	}
	// Else, return false
	printf("SEMANTIC ERROR: Var %s is not in the symbol table", itemName);
	exit(1);
}


int compareTypes(char item1[50], char item2[50], char scope[50]) {
	// Compare two item types for any symbol table entry
	const char* idType1 = item1;

	const char* idType2 = item2;

	printf("%s = %s\n", idType1, idType2);

	// Return true or false to state if these items are the same
	return strcmp(idType1, idType2);
}