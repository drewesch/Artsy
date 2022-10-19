%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

int words = 0;
int chars = 0;
int lines = 0;

// Grammar recognized for the language

%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
STRING		\"(\\.|[^"\\])*\"
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
LINEBREAK	(\n\r)|(\r\n)|[\n\r]
ws          {delim}+

%%
"/*"    				{
						// Comment recognition
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}				
"int"	{
			// Recognize integers as a TYPE, return as a token
			words++; chars += strlen(yytext);
			printf("%s : TYPE\n", yytext);
			yylval.string = strdup(yytext); 
			return TYPE;
		}


"string"	{
			// Recognize strings as a TYPE, return as a token
			words++; chars += strlen(yytext);
			printf("%s : STRING\n", yytext);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"write"	{
			// The write operation is special, return as a KEYWORD token
			words++; chars += strlen(yytext);
			printf("%s : KEYWORD\n", yytext);
			yylval.string = strdup(yytext); 
			return WRITE;
		}

{ID}	{
			  // IDs such as "x" or "y" are utilized with a TYPE or KEYWORD, return as an identifier token
			  words++; chars += strlen(yytext);
			  printf("%s : IDENTIFIER\n",yytext);
			  yylval.string = strdup(yytext); 
			  return ID;
			}
			
{NUMBER}	{
		      // Any integer needs to be assigned to a digit or number, so return any digit as a number token
			  words++; chars += strlen(yytext);
			  printf("%s : NUMBER\n",yytext);
			  yylval.number = strdup(yytext); 
			  //yylval.number = atoi(yytext); 
			  return NUMBER;
			}

","		{
		  // Comma Recognition
		  chars++;
		  printf("%s : COMMA\n", yytext);
		  yylval.string = strdup(yytext); 
		  return COMMA;
		}

";"		{
		  // End of statement recognition
		  chars++;
		  printf("%s : SEMICOLON\n", yytext);
		  yylval.string = strdup(yytext); 
		  return SEMICOLON;
		}
		
"="		{
		  // Assignment recognition token
		  chars++;
		  printf("%s : EQ\n", yytext);
		  yylval.string = strdup(yytext); 
		  return EQ;
		}

"+"		{
	// Addition operator recognition, return as "PLUS" token
	chars++;
	printf("%s : PLUS\n", yytext);
	yylval.string = strdup(yytext); 
	return PLUS;
}

"-"		{
	// Minus operator recognition, return as "MINUS" token
	chars++;
	printf("%s : Minus\n", yytext);
	yylval.string = strdup(yytext); 
	return MINUS;
}


"/"		{
	// Division operator recognition, return as "DIVIDE" token
	chars++;
	printf("%s : Divide\n", yytext);
	yylval.string = strdup(yytext); 
	return DIVIDE;
}

"*"		{
	// Multiplication operator recognition, return as "PLUS" token
	chars++;
	printf("%s : Multiply\n", yytext);
	yylval.string = strdup(yytext); 
	return MULTIPLY;
}

"{"		{
	// Bracket recognition, will be used later as a token for scopes
	chars++;
	printf("%s : LEFTBRACKET\n", yytext);
	yylval.string = strdup(yytext); 
	return LEFTBRACKET;
}

"}"		{
	// Bracket recognition, will be used later as a token for scopes
	chars++;
	printf("%s : RIGHTBRACKET\n", yytext);
	yylval.string = strdup(yytext); 
	return RIGHTBRACKET;
}
		
{LINEBREAK}	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
		 // Line break and tab recognition for processing files in Windows
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		

%%