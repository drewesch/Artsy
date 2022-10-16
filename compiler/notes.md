# For SymbolTable.h

char* getItemType(char itemName[50], char scope[50]) {
	for(int i=0; i<100; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return symTabItems[i].itemType; // found the type in the table
		}
	}

	return "nope";
}

int compareTypes(char item1[50], char item2[50], char scope[50]) {
	const char* idType1 = getItemType(item1. scope);
	const char* idType2 = getItemType(item2. scope);

	printf("%s = %s\n", idType1, idType2);

	int isMatch = strcmp(idType1, idType2);

	if (isMatch) {
		return 0;
	} else return 1;
}

# For parser.y

 DeclList:	Decl DeclList
 	| Decl
 ;

 Decl:	VarDecl
 	| StmtList
 ;

 VarDecl:	TYPE ID SEMICOLON	{ printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
									// Symbol Table
									symTabAccess();
									int inSymTab = found($2, currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
									
									if (inSymTab == 0) 
										addItem($2, "Var", $1,0, currentScope);
									else
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
									showSymTable();
									
								  // ---- SEMANTIC ACTIONS by PARSER ----
								  //  code goes here...

								}
;

 StmtList:    Stmt
 	| Stmt StmtList
 ;

 Stmt:	SEMICOLON
 	| Expr SEMICOLON
 ;

 Expr:	ID { printf("\n RECOGNIZED RULE: Simplest expression\n"); }
 	| ID EQ ID 	{ printf("\n RECOGNIZED RULE: Assignment statement for variable\n");
					// --- SEMANTIC ACTIONS by PARSER //
						$$ = AST_assignment("=",$1,$3);
						// --- SEMANTIC ANALYSIS --- // 
						/*
							Write the external C code to:
							 1. Verify that both variables have been declared
							 2. Verify that the type of RHS and LHS is the same.
							 3. Decide what to do if the types are different
							 4. THE MAIN OUTCOME:
								If all semantic checks passed, generate 
								intermediate representation code.
								It is sudo-code with a three address code notation.
								(4.1 Write the external C program to generate IR code)

							What to do if we run into mismatches?
							 1. State line and character which error occurred
							 2. State type of error (e.g., type mismatch)
							 3. Be informative on what the error was
							 4. Recommendations on how to fix it
							 5. Stop compilation process
						*/

						// Assume you implemented a C function that prints to a file
						// Also assume that there's something in C that handles the symbol table
						// If you give it two values of IDs, it generates the correct IR code and writes it to a file
						if(testVarDeclaration($1)) == True)
							if(testVarDeclaration($3)) == True)
								if(checkType($1) == checktype($3))
									emitIRcode(IRfile, IRAssignment($1, $3))
				}
 	| ID EQ NUMBER 	{ printf("\n RECOGNIZED RULE: Assignment statement for number\n"); }

	// --- SEMANTIC CHECKS --- //
	/*
		int semanticCorrectness = FALSE;
		1. Has ID been declared? If yes, semanticCorrectness = 1

		2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

		If all tests == 1, then
			perform SEMANTIC ACTIONS
		
	*/

	int check = 1;

	if(found($1, currentScope) != 1) { 
		printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s.\n", $1, currentScope);
		check == 0;
		exit(1);
	}

	if (getItemType($1) == "NUMBER") {
		printf("AssignStmt RULE is correct, generating IR code.");
		// Generate IR code

	} else {
		printf("SEMANTIC ERROR: Types do not match for %s and %s.\n", $1, $3);
		check == 0;
		exit(1);
	}

    | ID EQ STRING { printf("\n RECOGNIZED RULE: Assignment statement for string\n") ;}
 	| WRITE ID 	{ printf("\n RECOGNIZED RULE: WRITE statement\n"); }

 %%