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
%token <string> TRUEZ
%token <string> FALSEZ
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
%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr Primary ExprListTail ExprList Block FunDeclList FuncHeader FunDecl ParamDeclList ParamDeclListTail ParamDecl FunctionCall FunDeclListTail If Loop Identifier


%start Program

%%

Program: DeclList FunDeclList StmtList {
	// Main program parser rule, generates the whole AST for the program
	$$ = AST_SingleChildNode("program",$1, $1);

	printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");

	ast = $$;

}
;

// Comment: DIVIDE MULTIPLY CommentBlock MULTIPLY DIVDE
// 	| 
// { }

DeclList: // Grammar rule to generate the whole list of variable and regular declarations
	| VarDecl DeclList	{ $$ = AST_DoublyChildNodes("vardec", $1, $2, $1, $2);
							}
	| Decl	{ $$ = $1; }
;

Decl:	VarDecl {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	$$ = $1;
	}
	| StmtList {
		// Basic Statement list declaration rule, generates AST for all statement declarations
		$$ = $1;
		}
;


VarDecl:	TYPE ID SEMICOLON	{ printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
									// Variable declaration rule
									// Symbol Table
									symTabAccess();
									int inSymTab = found($2, currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
									
									// Check if the variable has been declared
									// If it has, throw an error
									if (inSymTab == 0) 
										addItem($2, "Var", $1,0, currentScope);
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
										exit(1);
									}
									// If the variable has not been declared 
									showSymTable();
									

								  // Generate AST node as a doubly node
								  $$ = AST_DoublyChildNodes("type",$1,$2,$1, $2);

								}

								| TYPE ID LEFTSQUARE NUMBER RIGHTSQUARE SEMICOLON {printf("Found Array declaration"); 
									symTabAccess(); 
									int inSymTab = found($2, currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
														
									// Check if the variable has been declared
									// If it has, throw an error
									if (inSymTab == 0) 
										addItem($2, "Array", $1,atoi($4), currentScope);
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
										exit(1);
									}
									// If the variable has not been declared 
									showSymTable();
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
	symTabAccess();
	int inSymTab = found($3, currentScope);
	//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

	// Check if the variable has been declared
	// If it has, throw an error
	//printf("0 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	if (inSymTab == 0){
		//printf("Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
		addFunction($2, $3, $5); //id
	}
	else {
		printf("SEMANTIC ERROR: Function %s is already in the symbol table", $3);
		exit(1);
	}
	//printf("2 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	// If the variable has not been declared 
	showSymTable();
	$$ = AST_DoublyChildNodes("Function Context", $3, $5, $3, $5);

	strcpy(tempScopeStore, currentScope);
	strcpy(currentScope, $3);
}
;

FunDecl: FuncHeader Block {
	// Generate AST node as a doubly node
	$$ = AST_DoublyChildNodes("Function",$1,$2,$1, $2);
	strcpy(currentScope, tempScopeStore);
}
;

ParamDeclList: {}
	| ParamDeclListTail {$$ = $1;}
;

ParamDeclListTail: ParamDecl {$$ = $1;}
	| ParamDecl COMMA ParamDeclListTail {$$ = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail",$1,$3,$1, $3);}
;

ParamDecl: TYPE ID {$$ = AST_DoublyChildNodes("Variable parm",$1,$2,$1, $2);}
	| TYPE ID LEFTSQUARE RIGHTSQUARE {$$ = AST_DoublyChildNodes("array parm",$1,$2,$1, $2);}
;



StmtList:	Stmt
	| Stmt StmtList {
		// Generate a list of all statement declarations below vardecl
		$$ = AST_DoublyChildNodes("statements", $1, $2, $1, $2);
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
					printf("Write AST generated!");
				}
	| WRITELN SEMICOLON {
		printf("\n RECOGNIZED RULE: WRITEIN statement\n");
		$$ = AST_SingleChildNode("writeln", "\n", 0);
	}
	| RETURN Expr SEMICOLON { $$ = AST_SingleChildNode("return", $2,0); }
	| READ ID SEMICOLON {$$ = AST_SingleChildNode("read", $2, 0);}
	| Block {$$ = $1;} //To do for next iteration
	| Loop {$$=$1;}
	| If {$$=$1;} 
;

Identifier: ID {AST_SingleChildNode("ID", $1,$1);}
;


Loop: WHILE LEFTPAREN Expr RIGHTPAREN Block {}
;

If: IF LEFTPAREN Expr RIGHTPAREN Block {}
;


Primary :	 NUMBER	{$$ = AST_SingleChildNode("int", $1, $1); }
	|  ID {$$ = AST_SingleChildNode($1, $1, $1);}
	|  STRING {$$ = AST_SingleChildNode( "string", $1, $1);}
	| FLOAT {$$ = AST_SingleChildNode( "float", $1, $1);}
	| ID LEFTSQUARE Expr RIGHTSQUARE {$$ = AST_SingleChildNode($1, $1, $3);}
;


BinOp:	PLUS {}
;

ExprListTail:	Expr	{ $$ = $1; }
	| Expr COMMA ExprListTail	{ $1->left = $3;
							  $$ = $1;
							}
;

ExprList: {}	
	| ExprListTail
;


// Fix the AST tree for block
Block: {}	
	| LEFTBRACKET DeclList StmtList RIGHTBRACKET { printf("\n RECOGNIZED RULE: Block statement\n");
		$$ = AST_DoublyChildNodes("BLOCK",$2,$3, $2, $3);
		}
;



Expr  :	Primary { printf("\n RECOGNIZED RULE: Simplest expression\n");
				$$ = $1;
				printf("%s\n", $1);
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
					printf("ID Declare check\n");
					CheckAssignmentType($1,$3, currentScope);
					// printf("RHS LHS Check\n");
					// if (compareTypes($1,$3, currentScope) != 0) {
					// 	exit(1);
					// }

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					$$ = AST_DoublyChildNodes("=",$1,$3, $1, $3);
					// Generate IRcode
					// printf("Generate IR Code\n");
					// emitConstantIntAssignment($1, $3);

					// Generate MIPS code
					// printf("Generate MIPS\n");
					// emitMIPSConstantIntAssignment($1, $3);

					}
	| ID LEFTSQUARE Expr RIGHTSQUARE EQ Expr 	{ printf("\n RECOGNIZED RULE: Assignment element statement\n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					printf("ID Declare check\n");
					CheckAssignmentType($1,$6, currentScope);
					// printf("RHS LHS Check\n");
					// if (compareTypes($1,$3, currentScope) != 0) {
					// 	exit(1);
					// }

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrElementNode = AST_DoublyChildNodes("element",$1,$3, $1, $3);
					$$ = AST_DoublyChildNodes("=",arrElementNode,$6, arrElementNode, $6);
					// Generate IRcode
					// printf("Generate IR Code\n");
					// emitConstantIntAssignment($1, $3);

					// Generate MIPS code
					// printf("Generate MIPS\n");
					// emitMIPSConstantIntAssignment($1, $3);

					}

	| Expr PLUS Expr { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("+",$1,$3, $1, $3);
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", $3 ->nodeType);
				}
	| Expr MINUS Expr { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("-",$1,$3, $1, $3);
				}
	| Expr MULTIPLY Expr { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("*",$1,$3, $1, $3);
				}
	| Expr DIVIDE Expr { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("/",$1,$3, $1, $3);
				}
	| Expr EXPONENT Expr { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				$$ = AST_DoublyChildNodes("EXP ",$1,$3, $1, $3);
			}
	| Expr COMPARSIONOPERATOR Expr {$$ = AST_DoublyChildNodes("Comparsion",$1,$3, $1, $3);}
	| Expr LOGICALOPERATOR Expr {$$ = AST_DoublyChildNodes("Logical",$1,$3, $1, $3);}			
	| LEFTPAREN Expr RIGHTPAREN {$$ = $2;}
	| FunctionCall {$$ = $1;}
	| TRUEZ {$$ = AST_SingleChildNode("TRUE", $1, $1);}
	| FALSEZ {$$ = AST_SingleChildNode("FALSE",$1, $1);}
;


FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN {}
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