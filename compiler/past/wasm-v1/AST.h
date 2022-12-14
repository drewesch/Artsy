//Abstract Syntax Tree Implementation
#ifndef AST_H 
#define AST_H

#include <string.h>

// Header file to list the AST structure and all functions to generate an AST

// An AST node contains a LHS, a RHS, and pointers to new AST nodes on the LHS & RHS
struct AST{
	char nodeType[50];
	char LHS[50];
	char RHS[50];
	
	struct AST * left;
	struct AST * right;
	// review pointers to structs in C 
	// complete the tree struct with pointers
};

// Generates an AST Node with just a RHS
struct AST * AST_SingleChildNode(char nodeType[50], char RHS[50], struct AST * childNode);

// Generates an AST Node with both a LHS and RHS
struct AST * AST_DoublyChildNodes(char nodeType[50], char LHS[50], char RHS[50], struct AST * leftChildNode, struct AST * rightChildNode);



//This function is to show the abstract symbol tree
//Will allow for an easier ability to debug future projects!
void showSingleAST(struct AST * ASTNode);

#endif