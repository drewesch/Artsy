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

//If statements
//Order of operations
//Booleans



int x;
int y;
int z;
string a;
string b;
string c;
string d;
string e;


x = 1;
a = "less then 5 or equal";
b = "greater"
c = "greater then 5";
d = "else statement";
e = "done with loop";





for ( x < 15){
	if (x < 5 || x == 5){
		write a;
		write x;
	}
	else if (x > 5){
		write b;
		write x;
	}
	else {
		write d;
		write x;
	}
}

write e;
write x;

y = 1 + 5 * 2;
wrtie y;

z = (1 + 5) * 2;
write y;


















/* 1. accept comments            */
/* 2. functions= function int hi(int x, int y){x = 2; y = 3; return x;}
/* 3. order of operation */
/* 4. multiply float and int */ 
/* 6. adding to an array of strings. (no char, and like python) */ 
/* 7. everytime displayMessage, it should show message*/ 
/* 8. writeln is line breaks*/ 


int aNumber;
float secondNumber;
string someLetter;  /* unused variable */
string message[50];
float justAverage;

function float average(float a, float b, float c){
	float avg;
	avg = (a + b + c)/3.0;
	return avg;
}

function int unreachableFunction(float x, int y){
   /* 
	This function does nothing and should
	Be removed from IR code in the optimization step
   */

   int result;
   result = x^y + x*y;

   return result;
}

function int displayMessage(){
	message[0] = "I";
	message[1] = " ";
	message[2] = "c";
	message[3] = "a";
	message[4] = "n";
	message[5] = " ";
	message[6] = "p";
	message[7] = "r";
	message[8] = "i";
	message[9] = "n";
	message[10] = "t";
	message[11] = ":";

    write message; 
	
	return 0;
}

function float ambitiousFunction (float a, float b, float c){

   /* great optimization opportunity */

   float result;
 
   result = (average(a, b, c) + average(a, b, c))/2.0;

   return result;
}

justAverage = average(12.5, 13.7, 25.8);
aNumber = displayMessage();
write justAverage;
writeln;

justAverage = justAverage * (justAverage + 2.0);
justAverage = average(justAverage, 0.0, 0.0);
aNumber = displayMessage();
writeln;

aNumber = displayMessage();
aNumber = aNumber / (aNumber + aNumber * aNumber);
write aNumber;
writeln;

justAverage = ambitiousFunction(1.0, 2.0, 3.0);
aNumber = displayMessage();
write justAverage;
writeln;

    

