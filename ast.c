#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree.h"

//funzione per dichiarare e assegnare i valori all'albero
struct node* mknode(struct node *left, struct node *right, char *token) {
  struct node *newnode = (struct node*) malloc(sizeof(struct node));
  char *newstr = (char*) malloc(strlen(token)+1);
  strcpy(newstr, token);
  newnode->left = left;
  newnode->right = right;
  newnode->token = newstr;
  return(newnode);
}

//stampo su file albero
void printSyntaxTree(struct node *tree){
    FILE *ftree;
    ftree=fopen("ast.txt","w");
    printInOrder(tree,ftree);
    fclose(ftree);
    freeTree(tree);
    free(tree);
}

//free dell'AST
void freeTree(struct node *tree){
    if (tree->left && tree->right) {
        return; 
    }
    freeTree(tree->right);
    freeTree(tree->left); 
    free(tree); 
}

void printInOrder(struct node *tree, FILE * ftree) {
    
    if (tree->left) {
        printInOrder(tree->left,ftree); 
    } 
    fprintf(ftree,"%s,\n", tree->token); 

    if (tree->right) {  
        printInOrder(tree->right, ftree); 
    }
}
