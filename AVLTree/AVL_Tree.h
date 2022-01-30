/* Stephanie Briere Americo
	       GRR20165313         */
/* Talita Halboth Cunha Fernandes
	       GRR20165399         */

#ifndef __AVL_Tree__
#define __AVL_Tree__

typedef struct AVL_Node {
	int key;
    struct AVL_Node *left;
    struct AVL_Node *right;
    /* Height of the node, 
       the count starts on the sheet 
       and increases to the root.
       The height of the sheet is 0. */
    unsigned int height; 
} AVL_Node;

AVL_Node* insertNode (AVL_Node *node, int key);
AVL_Node* removeNode (AVL_Node *node, int key); 
void searchNode (AVL_Node *node, int key);
void preorder (AVL_Node *node);
void freeTree (AVL_Node *node);
#endif