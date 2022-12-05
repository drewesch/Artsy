//Abstract Syntax Tree Implementation
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AST.h"

// Generate an AST Node with just a RHS
struct AST * AST_SingleChildNode(char nodeType[50], char RHS[50], struct AST * childNode) {
	// Declare size of AST with malloc
	struct AST* astSingleChildNode = malloc(sizeof(struct AST));

	// Declare the node type and RHS
	strcpy(astSingleChildNode->nodeType, nodeType);
	strcpy(astSingleChildNode->RHS, RHS);

	// Set a pointer to the RHS
	astSingleChildNode -> right = childNode;

	// Return the node to the parser
	return astSingleChildNode;
}

struct AST * AST_DoublyChildNodes(char nodeType[50], char LHS[50], char RHS[50], struct AST * leftChildNode, struct AST * rightChildNode){
	// Declare size of AST with malloc
	struct AST* astDoubleChildNode = malloc(sizeof(struct AST));

	// Declare the node type, RHS, and LHS data
	strcpy(astDoubleChildNode->nodeType, nodeType);
	strcpy(astDoubleChildNode->LHS, LHS);
	strcpy(astDoubleChildNode->RHS, RHS);

	// Set a pointer to the RHS and LHS
	astDoubleChildNode -> left = leftChildNode;
	astDoubleChildNode -> right = rightChildNode;

// AST Tree Model
/*
	 NODE
	/    \
  LHS    RHS

*/
	// Return the node to the parser
	return astDoubleChildNode;
	
}



//This function is to show the abstract symbol tree
//Will allow for an easier ability to debug future projects!
void showSingleAST(struct AST * ASTNode) {
	// Use recursion to traverse the AST
	// Base case
	if (ASTNode == NULL)
        return;

    showSingleAST(ASTNode->left); // Start by using recursion to traverse the LHS of the tree
    printf("%s\t%s\t%s", ASTNode->nodeType, ASTNode->LHS, ASTNode->RHS); // Print field in tree position
    showSingleAST(ASTNode->right); // Traverse RHS of tree
}