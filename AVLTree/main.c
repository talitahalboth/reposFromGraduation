#include <stdio.h>
#include "AVL_Tree.h"

int main() {
    AVL_Node *root = NULL;
    char input;
    int key;

    // While it is not the end of the file
    while (scanf("%c", &input) > 0) {
        switch (input) {
            // Insertion
            case 'i':
                // Reads the key to be inserted
                scanf("%d", &key);
                printf("%c %d\n",input,key );
                // Insert the node
                root = insertNode(root, key);
                // Prints the final tree
                preorder(root);
                printf("\n");
                break;
            // Removal
            case 'r':
                // Reads the key to be removed
                scanf("%d", &key);
                printf("%c %d\n",input,key );
                // Remove the node (if any)
                root = removeNode(root, key);
                // Prints the final tree
                preorder(root);
                printf("\n");
                break;
            // Search
            case 'b':
                // Reads the key to be searched
                scanf("%d", &key);
                printf("%c %d\n",input,key );
                // Shearch the node
                searchNode(root, key);
                printf("\n");
                break;
        }
    }
    if (root) freeTree(root);
}