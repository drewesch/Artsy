%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "semantic.h"
#include "javascriptgen.h"

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

%token <string> TYPE
%token <string> ID
%token <char> COMMA
%token <char> SEMICOLON
%token <char> EQ
%token <char> PLUS
%token <char> LEFTBRACKET
%token <char> RIGHTBRACKET
%token <number> NUMBER
%token WRITE

/* %printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER; */

%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr Primary ExprListTail ExprList Block BinOp

%start Program

%%

Program: DeclList  { $$ = AST_SingleChildNode("program",$1, $1);

printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");}
;

DeclList:
	| VarDecl DeclList	{ $$ = AST_DoublyChildNodes('vardec', $1, $1, $2, $2);
							}
	| Decl	{ $$ = $1; }
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
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
										exit(1);
									}
									showSymTable();
									


								  // ---- SEMANTIC ACTIONS by PARSER ----
								  $$ = AST_SingleChildNode("Type",$1,$2);
								  printf("Show AST\n");
								  showSingleAST($1);
								}
;







StmtList:	Stmt
	| Stmt StmtList {  $$ = AST_DoublyChildNodes('statements', $1, $1, $2, $2); }
;

Stmt:	SEMICOLON	{}
	| Expr SEMICOLON	{$$ = $1;}
	| WRITE Expr SEMICOLON	{ printf("\n RECOGNIZED RULE: WRITE statement\n");
					$$ = AST_SingleChildNode("write",$2, $2);
				}
	| Block
;

Primary :	 NUMBER	{$$ = $1;}
	|  ID {$$ = $1;}
;


BinOp:	PLUS {}
;

ExprListTail:	Expr	{ $$ = $1; }
	| Expr COMMA ExprListTail	{ $1->left = $3;
							  $$ = $1;
							}
;

ExprList:	
	| ExprListTail
;


// Fix the AST tree for block
Block: 
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
					
					CheckAssignmentType($1,$3, currentScope);
					if (compareTypes($1,$3, currentScope) != 0) {
						exit(1);
					}

					// Generate AST tree nodes
					$$ = AST_DoublyChildNodes("=",$1,$3, $1, $3);

					// Generate IRcode
					// emitAssignment($1, $3);

					// Generate MIPS code
					// emitMIPSConstantIntAssignment($1, $3);

					}









	| Expr BinOp Expr { printf("\n RECOGNIZED RULE: BinOp statement\n"); 
					$$ = AST_DoublyChildNodes("+",$1,$3, $1, $3);
				}

%%



/* [EType]  */




/* 
EType = CheckPrimaryType($1); */
/* EType = CheckAssignmentType($1, $3);
EType = CheckBinOpType($1, $3); */









int main(int argc, char**argv)
{
/* 
	#ifdef YYDEBUG
		yydebug = 1;
	#endif */

	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}