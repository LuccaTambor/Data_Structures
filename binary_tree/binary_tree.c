#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Basic ATD of a binary tree
typedef struct node {
    int key;
    struct node *left, *right;
}TREE;

//Clean terminal
void clear() {
    #ifdef WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

//Pause script 
void pause() {
    puts("PRESS ENTER.......");
    getchar();
    getchar();
}

//recursive insertion function for a binary tree
void insertNode(TREE **aux, int key) {
	if(*aux == NULL) {//the aux node is empty
		*aux = malloc(sizeof(TREE));
		(*aux)->key = key;
		(*aux)->left = NULL;
		(*aux)->right = NULL;
	}
	else {
		if(key > (*aux)->key)
			insertNode(&(*aux)->right , key);
		else if(key < (*aux)->key)
			insertNode(&(*aux)->left , key);
	}	
}

//Prints the elements of the binary tree in order
void order(TREE *node) {
	if(node != NULL) {
		order(node->left);
		printf("%i ", node->key);
		order(node->right);
	}
}

//Prints the elements of the binary tree in pre-order
void preOrder(TREE *node) {
	if(node != NULL) {
		printf("%i ", node->key);
		preOrder(node->left);
		preOrder(node->right);
	}
}

//Prints the elements of the binary tree in pos-order
void posOrder(TREE *node) {
	if(node != NULL) {
		posOrder(node->left);
		posOrder(node->right);
		printf("%i ", node->key);
	}
}

//search a key in the binary tree
TREE *searchNode (TREE *aux, int key, TREE **father_node) {
	TREE *actual_node = aux;
	*father_node = NULL;
	while(actual_node) {
		if(actual_node->key == key)
			return actual_node;
		*father_node = actual_node;
		if(key < actual_node->key)
			actual_node = actual_node->left;
		else
			actual_node = actual_node->right;
	}
	return(NULL);//key not founded
}

//Excludes a node and rebalances the tree
TREE *removeNode(TREE *aux, int key){
    TREE *father_node, *node, *p, *q;
    //p points to father_node of the node who gonna replace the node that will be removed(q)
    node = searchNode(aux, key, &father_node);
    
    //there is no node with the key
    if(node == NULL) 
		return aux;

    //In case of the node having sons, is not a leaf
    if(!node->left || !node->right)
        if(!node->left) 
            q = node->right;
        else 
            q = node->left;
    else { //Node has both sons
        p = node;

        q = node->left;
        while(q->right) { 
            p = q;
            q = q->right;
        }
        if(p != node) {
            p->right = q->left;
            q->left = node->left;
        }
        q->right = node->right;
    }

    if(!father_node) {
        free(node);
        return(q);
    }
    
    if(father_node->key < key) 
        father_node->right = q;
    else
        father_node->left = q;

    free(node);
    return aux; 
}

int main() {
    int i,key,op;
    TREE *root=NULL;
	do {
		puts("-----MENU-----");
		puts("1)Insert on Tree");
		puts("2)Elements in order");
		puts("3)Elements in pre-order");
		puts("4)Elements in pos-order");
		puts("5)Remove node");
		scanf("%i",&op);
		switch (op) {
			case 1:
				printf("Insert a key:");
				scanf("%i",&key);
				insertNode(&root, key);
				pause();
				clear();
				break;
			case 2:
				order(root);
				printf("\n");
				pause();
				clear();
				break;
			case 3:
				preOrder(root);
				printf("\n");
				pause();
				clear();
				break;
			case 4:
				posOrder(root);
				printf("\n");
				pause();
				clear();
				break;
			case 5:
				puts("Insert the key:");
				int n;
				scanf("%i",&n);
				root = removeNode(root,key);
				pause();
				clear();
				break;
			default:
				break;
		}
	} while (op<=5);
	
	
}