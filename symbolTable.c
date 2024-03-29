#include "helper.h"
#include "symbolTable.h"

// Single Scope declaration
// This approach will change in the next iteration
struct Entry symTabItems[100];
int symTabIndex;

// Add a single entry struct to the symbol table for the appropriate scope
void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50], int stackPointer, int blockNumber){
	// Set entry struct item data for each parameter in the action
	symTabItems[symTabIndex].itemID = symTabIndex;
	strcpy(symTabItems[symTabIndex].itemName, itemName);
	strcpy(symTabItems[symTabIndex].itemKind, itemKind);
	strcpy(symTabItems[symTabIndex].itemType, itemType);
	symTabItems[symTabIndex].arrayLength = arrayLength;
	strcpy(symTabItems[symTabIndex].scope, scope);
	symTabItems[symTabIndex].stackPointer = stackPointer;
	symTabItems[symTabIndex].blockNumber = blockNumber;

	// Increment the symbol table index for this scope
	symTabIndex++;
}

struct Entry* getParamList(char * id, struct AST* paramlist, char scopeStack[50][50], int stackPointer) {
	struct Entry * list = malloc(sizeof(struct Entry));	
	if(strcmp(paramlist->nodeType, "variable parm") == 0) {
		// Semantic check
		// If the parameter variable name has already been declared before this, throw a Semantic Error
		if (found(paramlist->RHS, scopeStack, stackPointer) == 1) {
			fprintf(errorFile, "Semantic Error, line %d: Parameter %s already declared as a variable.\n", lines, paramlist->RHS);
			exit(1);
		}

		list->itemID = symTabIndex;
		strcpy(list->itemName, paramlist->RHS);
		strcpy(list->itemKind, "Var");
		strcpy(list->itemType, paramlist->LHS);
		list->arrayLength = 0;
		strcpy(list->scope, id);
		list->paramlist = 0;

		return list;
	}
	else if(strcmp(paramlist->nodeType, "ParaDecl comma ParaDeclListTail") == 0) {
		list = getParamList(id, paramlist->left, scopeStack, stackPointer);
		list->paramlist = getParamList(id, paramlist->right, scopeStack, stackPointer);
	}

	return list;

}


void addAction(char *type, char *id, struct AST* paramlist, char scopeStack[50][50], int stackPointer, int blockNumber){
	if (paramlist == 0){
		symTabItems[symTabIndex].paramlist = 0;
	}
	else if (strcmp(paramlist->nodeType, "variable parm") == 0) {
		struct Entry* list = malloc(sizeof(struct Entry));

		// Semantic check
		// If the parameter variable name has already been declared before this, throw a Semantic Error
		if (found(paramlist->RHS, scopeStack, stackPointer) == 1) {
			fprintf(errorFile, "Semantic Error, line %d: Parameter %s already declared as a variable.\n", lines, paramlist->RHS);
			exit(1);
		}
		
		list->itemID = symTabIndex;
		strcpy(list->itemName, paramlist->RHS);
		strcpy(list->itemKind, "Var");
		strcpy(list->itemType, paramlist->LHS);
		list->arrayLength = 0;
		strcpy(list->scope, id);
		list->paramlist = 0;

		symTabItems[symTabIndex].paramlist = list;
	} else if (strcmp(paramlist->nodeType, "ParaDecl comma ParaDeclListTail") == 0) {		
		symTabItems[symTabIndex].paramlist = getParamList(id, paramlist, scopeStack, stackPointer);
	}

	// Set entry struct item data for each parameter in the action
	symTabItems[symTabIndex].itemID = symTabIndex;
	strcpy(symTabItems[symTabIndex].itemName, id);
	strcpy(symTabItems[symTabIndex].itemKind, "action");
	strcpy(symTabItems[symTabIndex].itemType, type);
	symTabItems[symTabIndex].arrayLength = 0;
	strcpy(symTabItems[symTabIndex].scope, "global");
	symTabItems[symTabIndex].stackPointer = stackPointer;
	symTabItems[symTabIndex].blockNumber = blockNumber;

	// Increment the symbol table index for this scope
	symTabIndex++;
}

// action module for adding if-statements and while-loops to the symbol table
void addLogic(char * itemName, char * itemKind, char * scopeStack, int stackPointer, int blockNumber){
	// Set entry struct item data for each parameter in the action
	symTabItems[symTabIndex].itemID = symTabIndex;
	strcpy(symTabItems[symTabIndex].itemName, itemName);
	strcpy(symTabItems[symTabIndex].itemKind, itemKind);
	strcpy(symTabItems[symTabIndex].itemType, "void");
	symTabItems[symTabIndex].arrayLength = 0;
	strcpy(symTabItems[symTabIndex].scope, scopeStack);
	symTabItems[symTabIndex].stackPointer = stackPointer;
	symTabItems[symTabIndex].blockNumber = blockNumber;

	// Increment the symbol table index for this scope
	symTabIndex++;
}

int found(char itemName[50], char scopeStack[50][50], int stackPointer){
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);
				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							//// printf("Found: %s\n-----------------------", itemName);
							return 1; // found the ID in the table
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				
				if(str2 == 0) {
				//// printf("Found: %s\n-----------------------", itemName);
				return 1; // found the ID in the table
				}
			}
		}
	}
	// Else, return false
	return 0;
}

void updateItemArrayLength(char itemName[50], char scopeStack[50][50], int stackPointer, int newLen) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, update length
				if(str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							symTabItems[i].arrayLength = newLen;
							return;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, update length
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					symTabItems[i].arrayLength = newLen;
					return;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

struct Entry* getItem(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);
				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return &symTabItems[i]; // found the ID in the table
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		// If these strings are the same, return true
		if( str1 == 0 ){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return &symTabItems[i]; // found the ID in the table
				}
			}
		}
	}
	// Else, return false
	return NULL;
}

int getItemID(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if(str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if (str2 == 0) {
							return symTabItems[i].itemID;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].itemID;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

char* getItemKind(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->itemKind;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j --) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].itemKind;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

char* getItemType(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->itemType;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].itemType;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

int getArrayLength(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->arrayLength;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].arrayLength;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

char* getItemScope(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->scope;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].scope;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

int getItemStackPointer(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->stackPointer;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].stackPointer;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

int getItemBlockNumber(char itemName[50], char scopeStack[50][50], int stackPointer) {
	// Lookup an identifier in the symbol table
	// return TRUE or FALSE
	// Later on, this may return additional information for an item being found
	for(int i=0; i<symTabIndex; i++){
		if(symTabItems[i].paramlist) {
			struct Entry* tempList = symTabItems[i].paramlist;
			while(tempList) {
				int str1 = strcmp(tempList->itemName, itemName);

				// If these strings are the same, return true
				if( str1 == 0){
					for(int j = stackPointer; j >= 0; j--) {
						int str2 = strcmp(tempList->scope, scopeStack[j]);
						if(str2 == 0) {
							return tempList->blockNumber;
						}
					}
				}
				tempList = tempList->paramlist;
			}
		}
		
		int str1 = strcmp(symTabItems[i].itemName, itemName);

		// If these strings are the same, return true
		if( str1 == 0){
			for(int j = stackPointer; j >= 0; j--) {
				int str2 = strcmp(symTabItems[i].scope, scopeStack[j]);
				if(str2 == 0) {
					//// printf("Found: %s\n-----------------------", itemName);
					return symTabItems[i].blockNumber;
				}
			}
		}
	}
	// Else, return false
	fprintf(errorFile, "Semantic Error, line %d: Variable %s does not exist.\n", lines, itemName);
	exit(1);
}

int compareTypes(char item1[50], char item2[50], char scope[50]) {
	// Compare two item types for any symbol table entry
	const char* idType1 = item1;
	const char* idType2 = item2;

	// Return true or false to state if these items are the same
	return strcmp(idType1, idType2);
}

int countParams(int itemID) {
	// Count variable
	int totalParams = 0;

	// Create the list of all parameters
	struct Entry* tempList = symTabItems[itemID].paramlist;

	// For each loop, add one parameter to the counter
	while(tempList) {
		totalParams++;
		tempList = tempList->paramlist;
	}
	
	// Return total count
	return totalParams;
}

int getNumFuncParams(char funcName[50]) {
	return countParams(getItemID(funcName, "global", 0));
}

char * getParamType(int itemID, int numParams, int searchIndex) {
	// Initial index variable
	int currIndex = 0;

	// Create the list of all parameters
	struct Entry* tempList = symTabItems[itemID].paramlist;

	// For each loop, add one parameter to the counter
	char * paramType = malloc(100 * sizeof(char));
	for (int i = 0; i < numParams; i++) {
		if (i == searchIndex) {
			strcpy(paramType, tempList->itemType);
			return paramType;
		}
		tempList = tempList->paramlist;
	}
	// If it is not found, return none
	strcpy(paramType, "none");
	return paramType;
}

char * getFuncParamItemType(char funcName[50], int numParams, int index) {
	return getParamType(getItemID(funcName, "global", 0), numParams, index);
}