%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "ircode.h"
#include "semantic.h"
#include "codegen.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
char currentScope[50]; // global or the name of the function
%}

%union {
	char* number;
	char character;
	char* string;
	struct AST* ast;
}

// List of all supported tokens from the lexer that will be processed in the parser

%token <string> TYPE
%token <string> ID
%token <char> COMMA
%token <char> SEMICOLON
%token <char> EQ
%token <char> LEFTBRACKET
%token <char> RIGHTBRACKET
%token <number> NUMBER
%token WRITE

/* %printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER; */

%left PLUS MINUS
%left MULTIPLY DIVIDE
%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr Primary ExprListTail ExprList Block BinOp

%start Program

%%

Program: DeclList  {
	// Main program parser rule, generates the whole AST for the program
	$$ = AST_SingleChildNode("program",$1, $1);

printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");

ast = $$;

}
;

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
	| Block {
		// To do for next iteration
	}
;

Primary :	 NUMBER	{$$ = AST_SingleChildNode("int", $1, $1); }
	|  ID {$$ = AST_SingleChildNode($1, $1, $1);}
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
					//printf("ID Declare check\n");
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

	| Expr BinOp Expr { printf("\n RECOGNIZED RULE: BinOp statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					$$ = AST_DoublyChildNodes("+",$1,$3, $1, $3);

				}

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
/* 
	#ifdef YYDEBUG
		yydebug = 1;
	#endif */

	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	
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