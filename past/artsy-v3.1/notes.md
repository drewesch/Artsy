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


### IF STATEMENTS
if (a > 0) {
	write a;
} else {
	write 0;
}

if (b < a) {
	if (b > d) {
		write something;
	} else {
		if (a > b) {
			do something;
		}
		write somethingelse;
	}
}

#### BNF Rules Options for IFs  
OPTION 1: Stmt: etc.
	| IF LPAREN LogicExpr RPAREN Block {}
;
OPTION 2:
StmtList: Stmt StmtList {}
;
Stmt: All Options
	| IfBlock {}
;
IfBlock: IF LPAREN LogicExpr RPAREN Block {}
	| IF LPAREN LogicExpr RPAREN Block ELSE BLOCK {}
;
### DANGLING ELSE PROBLEM
- Happens when you cannot match between the else and the ifs
- Only manifests when you have nested IFs
- Your code must support nested IFs
- One way to eliminate the dangling else problem is to ensure IfBlocks are nested together in the AST

### AST for IFs and ELSEs
StmtList
	\
	IfBlock
		\
		IF
	  /		\
	cond	IfBlock
	/	\		  \		
   >   block		IF
  / \	   	   /  		\
 a	 0  	cond  		ELSE
	  		/	\		/	\
		   ==  block  block IfBlock
								\
								etc.








/*project 4 and 5 */ 
/* if statements and while */
/*boolean true / false */



boolean n;
boolean k;
int a;
int b;
int x;
int y;
int z;
string c;
string d;

x = 0;
a = 5;
b=3;
n = (a > b);
k = (a < b);
c = "c c c";
d = "d d d";

while (x < 4){
	if (x < 1){
		z = 5;
		write z;
		x = x + 1;
	}

	if else (x == 1 || x < 0){
		z = 6;
		write z;
		x = x + 1;
	}

	if else (x == 2 && x > 1){
		z = 7;
		write z;
		x = x + 1;
	}
	else{
		z = 8;
		write z;
		x = x + 1;
		if (n == true ){
			write c; 
			if (k == false){
				write d; 
			}
		}
	}
}

z = 9;
write z; 


/*project 4 */ 








































new-------------------------------------------------------------------


/*project 4 and 5 */ 
/* if statements and while */
/*boolean true / false */


boolean n;
boolean k;
int a;
int b;
int x;
int y;
int z;
string c;
string d;

x = 0;
a = 5;
b=3;
n = (a > b);
k = (a < b);
c = "c c c";
d = "d d d";

while (x < 4){
	if (x < 1){
		z = 5;
		write z;
		x = x + 1;
	}

	elif (x == 1 || x < 0){
		z = 6;
		write z;
		x = x + 1;
	}

	elif (x == 2 && x > 1){
		z = 7;
		write z;
		x = x + 1;
	}
	else{
		z = 8;
		write z;
		x = x + 1;
		if (n == true ){
			write c; 
			if (k == false){
				write d; 
			}
		}
	}
}

z = 9;
write z; 


/*project 4 */ 



scope check
type if a > b 

1. Has it been declared ? global scope vs if scope (might not have a scope)
2. Types ? if a > b, a is 5 and b is string 

extra if function returns a value then it can > 




new 2-------


int x;
int y;
int z;

x = 3;
y = x + 5;
z = y + 7;

write x;
write y;
write z;



new 2---------




















error 1-----------
int x;
int y ;



function int add(int z, int a){
	z = z + 2;
	return z;
}


function int addtwo(int b, int c){
	b = b + 2;
	return b;
}


x = 5;
y = 10;

add(x);

error 1--------------------------


error 2----------------------------

int x;
int y ;



function float average(float a, float b, float c){
	a = a + 2;
	return a;
}

function int add(int z){
	z = z + 1;
	return z;
}

function int addtwo(int a){
	a = a + 1;
	return a;
}

x = 5;
y = 10;

add(x);


error 2--------------------



Run Files
 make artsy ../test-programs/addition.artsy