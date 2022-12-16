%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "ircode.h"
#include "semantic.h"
#include "webgen.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
char currentScope[50]; // global or the name of the function
char tempScopeStore[50];
%}

%union {
	char* number;
	char* decimal; 
	char character;
	char* string;
	struct AST* ast;
}

// List of all supported tokens from the lexer that will be processed in the parser

%token <string> TYPE
%token <string> ID
%token <string> INTEGER
%token <string> FLOAT
%token <string> STRING
%token <string> LOGICALOPERATOR
%token <string> COMPARSIONOPERATOR
%token <char> CHAR
%token <char> COMMA
%token <char> SEMICOLON
%token <char> EQ
%token <char> LEFTBRACKET
%token <char> RIGHTBRACKET
%token <char> LEFTPAREN
%token <char> RIGHTPAREN
%token <char> LEFTSQUARE
%token <char> RIGHTSQUARE
%token <number> NUMBER
%token LET
%token DECLARE
%token AS
%token WRITE
%token WRITELN
%token READ
%token RETURN
%token IF
%token ELIF
%token ELSE
%token WHILE
%token BREAK
%token FOR
%token <string> TRUE
%token <string> FALSE
%token FUNCTION

//function decl
//symbol table
//semantic analzyer 

/* %printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER; */

%left LOGICALOPERATOR 
%left COMPARSIONOPERATOR
%left PLUS MINUS
%left MULTIPLY DIVIDE
%left MODULO
%left EXPONENT
%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr Primary ExprListTail ExprList Block FunDeclList FuncHeader FunDecl ParamDeclList ParamDeclListTail ParamDecl FunctionCall FunDeclListTail If Loop Elif Else ForL

%start Program

%%

// Main program parser rule, generates the whole AST for the program
Program: DeclList StmtList {
		printf("\nProgram Version: DeclList StmtList\n");
		$$ = AST_DoublyChildNodes("program", $1, $2, $1, $2);

		printf("\n--------------------Parser End------------------------\n");

		ast = $$;
	} |
	DeclList StmtList Program{
		printf("\nProgram Version: DeclList StmtList Program\n");
		struct AST * funcChildNode = AST_DoublyChildNodes("program", $2, $3, $2, $3);
		$$ = AST_DoublyChildNodes("program",$1, funcChildNode, $1, funcChildNode);

		printf("\n--------------------Parser End------------------------\n");

		ast = $$;
	}
;

// Comment: DIVIDE MULTIPLY CommentBlock MULTIPLY DIVDE
// 	| 
// { }

DeclList: // Grammar rule to generate the whole list of variable and regular declarations
	VarDecl DeclList	{ $$ = AST_DoublyChildNodes("vardec", $1, $2, $1, $2);
							}
	| FunDeclList { $$ = $1; }
	| Decl	{ $$ = $1; }
;

Decl: {
	printf("\ncheck5\n");
	fflush(stdout);
	$$ = AST_SingleChildNode("empty", "empty", "empty");}
	| VarDecl {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	$$ = $1;
	}
	
;


VarDecl:	
	TYPE ID SEMICOLON	{
		printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
		// Variable declaration rule
		// Symbol Table
		symTabAccess();
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem($2, "Var", $1, 0, currentScope);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", $2);
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();
		

		// Generate AST node as a doubly node
		$$ = AST_DoublyChildNodes("type",$1, $2, $1, $2);

	}

	| DECLARE ID AS TYPE SEMICOLON	{
		printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
		// Variable declaration rule
		// Symbol Table
		symTabAccess();
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem($2, "Var", $4, 0, currentScope);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", $2);
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();
		

		// Generate AST node as a doubly node
		$$ = AST_DoublyChildNodes("type", $4, $2, $4, $2);

	}

	| TYPE ID LEFTSQUARE INTEGER RIGHTSQUARE SEMICOLON {
		printf("RECOGNIZED RULE: Array declaration"); 
		symTabAccess(); 
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem($2, "Array", $1, atoi($4), currentScope);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", $2);
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();

		struct AST* arraySize = AST_SingleChildNode("size", $4, $4); 
		struct AST* array = AST_DoublyChildNodes($2, "array", arraySize, "array", arraySize);
		$$ = AST_DoublyChildNodes("type", $1, array, $1, array);
	}

	| DECLARE ID AS TYPE LEFTSQUARE INTEGER RIGHTSQUARE SEMICOLON {
		printf("RECOGNIZED RULE: Array declaration"); 
		symTabAccess(); 
		int inSymTab = found($2, currentScope);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem($2, "Array", $4, atoi($6), currentScope);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", $2);
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();

		struct AST* arraySize = AST_SingleChildNode("size", $6, $6); 
		struct AST* array = AST_DoublyChildNodes($2, "array", arraySize, "array", arraySize);
		$$ = AST_DoublyChildNodes("type", $4, array, $4, array);
	}
;

FunDeclList: {}
	| FunDecl {$$ = $1;}
	| FunDeclListTail {$$ = $1;}
;

FunDeclListTail: FunDecl {$$ = $1;}
	| FunDecl FunDeclListTail {$$ = AST_DoublyChildNodes("FunDecl FunDeclListTail",$1,$2,$1, $2);}
;

FuncHeader: FUNCTION TYPE ID LEFTPAREN ParamDeclList RIGHTPAREN {
	printf("\ncheck2\n");
	fflush(stdout);
	symTabAccess();
	int inSymTab = found($3, currentScope);

	// Check if the function variable has already been declared
	// If it has, throw an error
	if (inSymTab == 0){
		addFunction($2, $3, $5); //id
	}
	else {
		printf("SEMANTIC ERROR: Function %s has already been declared.\n", $3);
		exit(1);
	}


	// If the variable has not been declared 
	showSymTable();
	$$ = AST_DoublyChildNodes("function context", $3, $5, $3, $5);

	strcpy(tempScopeStore, currentScope);
	strcpy(currentScope, $3);
}
;

FunDecl: FuncHeader Block {
	// Generate AST node as a doubly node
	$$ = AST_DoublyChildNodes("function",$1,$2,$1, $2);
	fflush(stdout);
	strcpy(currentScope, tempScopeStore);
}
;

ParamDeclList: {}
	| ParamDeclListTail {$$ = $1;}
;

ParamDeclListTail: ParamDecl {$$ = $1;}
	| ParamDecl COMMA ParamDeclListTail {$$ = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail",$1,$3,$1, $3);}
;

ParamDecl: TYPE ID {$$ = AST_DoublyChildNodes("variable parm",$1,$2,$1, $2);}
	| TYPE ID LEFTSQUARE RIGHTSQUARE {$$ = AST_DoublyChildNodes("array parm",$1,$2,$1, $2);}
;

StmtList: Stmt {
		$$ = $1;
	}
	| Stmt StmtList {
		printf("\n RECOGNIZED RULE: StmtList statement\n");
		// Generate a list of all statement declarations below vardecl
		$$ = AST_DoublyChildNodes("statements", $1, $2, $1, $2);
		}
	| FunDeclList {
		$$ = $1;
	}
;

Stmt:	SEMICOLON	{}
	| Expr SEMICOLON	{
		// Simplest expr statement in grammar
		$$ = $1;
		}
	| WRITE Primary SEMICOLON	{ printf("\n RECOGNIZED RULE: WRITE statement\n");
					// Generate write declarations as a statement in the parser
					$$ = AST_SingleChildNode("write", $2, $2);

					printf("write: %s", $2 -> nodeType);

					// If the primary type is a variable, check if the variable is in the symbol table
					if (!strcmp($2 -> nodeType, "int") && !strcmp($2 -> nodeType, "float") && !strcmp($2 -> nodeType, "string") && strncmp(getPrimaryType($2), "var", 3) == 0 && !found($2, currentScope)) {
						printf("SEMANTIC ERROR: Variable %s does not exist.\n", $2);
						exit(1);
					}

				}
	| WRITELN SEMICOLON {
		printf("\n RECOGNIZED RULE: WRITEIN statement\n");
		$$ = AST_SingleChildNode("writeln", "\n", 0);
	}
	| RETURN Expr SEMICOLON {
		printf("\n RECOGNIZED RULE: RETURN statement\n");
		$$ = AST_SingleChildNode("return", $2,$2); 

		// Check if the return type matches the function type
		CheckAssignmentType(currentScope, getExprOp($2), currentScope);
	}
	| READ ID SEMICOLON {$$ = AST_SingleChildNode("read", $2, 0);}
	| Block {$$ = $1;} //To do for next iteration
	| Loop {$$=$1;}
	| If {$$=$1;} 
	| Elif {$$=$1;} 
	| Else {$$=$1;}
	| ForL {$$=$1;}  
;

ForL: FOR LEFTPAREN Expr RIGHTPAREN Block { }
;

Loop: WHILE LEFTPAREN Expr RIGHTPAREN Block { }
;

If: IF LEFTPAREN Expr RIGHTPAREN Block {}
;

Elif:  ELIF LEFTPAREN Expr RIGHTPAREN Block {}
;

Else:  ELSE Block {}
;


Primary :	 INTEGER	{$$ = AST_SingleChildNode("int", $1, $1); }
	|	NUMBER	{$$ = AST_SingleChildNode("float", $1, $1); }
	|  ID {$$ = AST_SingleChildNode($1, $1, $1);}
	|  STRING {$$ = AST_SingleChildNode( "string", $1, $1);}
	| FLOAT {$$ = AST_SingleChildNode( "float", $1, $1);}
	| ID LEFTSQUARE NUMBER RIGHTSQUARE {
		$$ = AST_DoublyChildNodes($1, "array", $3, "array", $3);
	}
;

ExprListTail: {$$ = AST_SingleChildNode("exprlist end", "\n", 0);}	
	| Primary	{ 
			$$ = AST_SingleChildNode("exprlist end", $1, $1); 
		}
	| Primary COMMA ExprListTail	{
			$$ = AST_DoublyChildNodes("exprlist exprtail", $1, $3, $1, $3);
		}
;

ExprList: {}	
	| ExprListTail {
		$$ = $1;
	}
;


// Fix the AST tree for block
Block:  LEFTBRACKET DeclList StmtList RIGHTBRACKET { printf("\n RECOGNIZED RULE: Block statement\n");
		$$ = AST_DoublyChildNodes("block",$2, $3, $2, $3);
		}
;

Expr  :	Primary { printf("\n RECOGNIZED RULE: Simplest expression\n");
				$$ = $1;
				strcpy($$->nodeType, CheckPrimaryType($1, currentScope));
				}		
	| ID EQ Expr 	{ printf("\n RECOGNIZED RULE: Assignment statement\n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID($1, currentScope);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType($1, getExprOp($3), currentScope);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					$$ = AST_DoublyChildNodes("=",$1, $3, $1, $3);

					}
	| ID LEFTSQUARE INTEGER RIGHTSQUARE EQ Expr 	{ printf("\n RECOGNIZED RULE: Assignment element statement\n");
	
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID($1, currentScope);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType($1, $6, currentScope);

					CheckIndexOutOfBound($1, $3, currentScope);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrayElement = AST_DoublyChildNodes("element assignment", $3, $6, $3, $6); 

					$$ = AST_DoublyChildNodes("=", $1, arrayElement, $1, arrayElement);

					}

	| LET ID EQ Expr 	{ printf("\n RECOGNIZED RULE: Let Assignment statement \n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID($2, currentScope);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType($2, getExprOp($4), currentScope);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					$$ = AST_DoublyChildNodes("=",$2, $4, $2, $4);

					}
	| LET ID LEFTSQUARE INTEGER RIGHTSQUARE EQ Expr 	{ printf("\n RECOGNIZED RULE: Let Assignment element statement\n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID($2, currentScope);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType($2, $7, currentScope);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrayElement = AST_DoublyChildNodes("element assignment", $4, $7, $4, $7); 

					$$ = AST_DoublyChildNodes("=", $2, arrayElement, $2, arrayElement);

					}

	| Expr PLUS Expr { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks

					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp($1), getExprOp($3));
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("+", $1, $3, $1, $3);
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", $3 ->nodeType);
				}
	| Expr MINUS Expr { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp($1), getExprOp($3));
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("-",$1,$3, $1, $3);
				}
	| Expr MULTIPLY Expr { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp($1), getExprOp($3));
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("*", $1, $3, $1, $3);
				}
	| Expr DIVIDE Expr { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp($1), getExprOp($3));
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("/", $1, $3, $1, $3);

					// If the RHS is an int, check for integer division error
					if (strncmp($3, "int", 3) == 0) {
						int numeratorInt = 1;
						int denominatorInt = 1;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars($1)) {
							numeratorInt = evaluateIntExpr($1);
						}
						if (containsNonVars($3)) {
							denominatorInt = evaluateIntExpr($3);
						}
						checkIntDivisionError(numeratorInt, denominatorInt);
					} else if (strncmp($3, "float", 5) == 0) {
						float numeratorFloat = 1.0;
						float denominatorFloat = 1.0;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars($1)) {
							numeratorFloat = evaluateFloatExpr($1);
						}
						if (containsNonVars($3)) {
							denominatorFloat = evaluateFloatExpr($3);
						}
						checkFloatDivisionError(numeratorFloat, denominatorFloat);
					}

				}
	| Expr EXPONENT Expr { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check to see if the LHS matches the RHS
				CheckOperationType(getExprOp($1), getExprOp($3));
				
				// Generate AST Nodes (doubly linked)
				$$ = AST_DoublyChildNodes("^", $1, $3, $1, $3);
			}
	| Expr COMMA Expr { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				$$ = AST_DoublyChildNodes("EXP ", $1, $3, $1, $3);
			}
	| Expr COMPARSIONOPERATOR Expr {$$ = AST_DoublyChildNodes("Comparsion", $1, $3, $1, $3);}
	| Expr LOGICALOPERATOR Expr {$$ = AST_DoublyChildNodes("Logical", $1, $3, $1, $3);}			
	| LEFTPAREN Expr RIGHTPAREN {$$ = $2;}
	| FunctionCall {$$ = $1;}
	| TRUE {$$ = AST_SingleChildNode("boolean", $1, $1);}
	| FALSE {$$ = AST_SingleChildNode("boolean",$1, $1);}
;


FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN {
	struct AST* funcCallParamList = AST_SingleChildNode("function call param list", $3, $3);
	$$ = AST_DoublyChildNodes("function call", $1, funcCallParamList, $1, funcCallParamList);

	// Check if the number of call parameters matches the number of function parameters
	CheckParamLength($1, funcCallParamList);

	// Check to see if the list of call parameters matches the function declaration
	// compareFuncToExpr($1, funcCallParamList, currentScope);
	
	// Find the number of parameters
    int numParams = getNumExprs(funcCallParamList);

    // Compare parameters if there's at least one parameter
    if (numParams != 0) {
        // Iterate through for each parameter in the list
        for (int i = 0; i < numParams; i++) {
            // Get the function parameter type at this index
            char * funcParamType = getFuncParamItemType($1, numParams, i);

            // Get the expression parameter type at this index
			char * callParamType = getCallListItemType(funcCallParamList, i, 0, currentScope);

            // Check to see if the two types do not match
            // If they don't, return a semantic error
            if (strncmp(funcParamType, callParamType, strlen(callParamType)) != 0) {
                printf("\nSEMANTIC ERROR: The call for parameter #%d (%s) does not match the type for parameter #%d (%s) in the function declaration for \"%s\".\n", i, callParamType, i, funcParamType, $1);
                exit(1);
            }
        }
    }
}
;

%%



/* [EType]  */




/* 
EType = CheckPrimaryType($1); */
/* EType = CheckAssignmentType($1, $3);
EType = CheckBinOpType($1, $3); */


// int main(int argc, char**argv)
// {
// /* 
// 	#ifdef YYDEBUG
// 		yydebug = 1;
// 	#endif */

// 	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	
// 	if (argc > 1){
// 	  if(!(yyin = fopen(argv[1], "r")))
//           {
// 		perror(argv[1]);
// 		return(1);
// 	  }
// 	}
// 	yyparse();
// }

int parser_main(FILE*inputfile)
{

	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	strcpy(currentScope, "global");
	if (2 > 1){
	  if(!(yyin = inputfile))
          {
		perror("Cannot open file");
		return(1);
	  }
	}
	
	
	return yyparse();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}