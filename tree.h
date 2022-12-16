struct node {
  struct node *left;
  struct node *right;
  char *token;     
};
struct node *head;
struct node* mknode(struct node *left, struct node *right, char *token);
void freeTree(struct node *tree);
void printInOrder(struct node *tree, FILE *ftree);
void printSyntaxTree(struct node *tree);
