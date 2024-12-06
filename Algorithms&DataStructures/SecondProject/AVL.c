#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funzioni.h"

int bilanciato(Node *);
int max(int, int);
int height(Node *);

Node *create (int data) {

	Node *ptr = malloc(sizeof(Node ));
	ptr->key = data;
	ptr->h = 1;
	ptr->left = NULL;
	ptr->right = NULL;

	return ptr;
}

int max (int a, int b) {

    if (a > b) {

        return a;
    }

    else{

        return b;

    }

}


int height (Node *root) {

    if (root == NULL) {

        return 0;
    }

    return root->h;

}

Node *rotateRightAVL(Node *root) {

    Node *newR = root->left;
    Node *TR = newR->right;

    newR->right = root;
    root->left = TR;

    root->h = max( height(root->left),height(root->right) ) + 1;
    newR->h = max( height(newR->left),height(newR->right) ) + 1;

    return newR;

}

Node *rotateLeftAVL(Node *root) {

    Node *newR = root->right;
    Node *TL = newR->left;

    newR->left = root;
    root->right = TL;

    root->h = max( height(root->left),height(root->right) ) + 1;
    newR->h = max( height(newR->left),height(newR->right) ) + 1;

    return newR;

}

int bilanciato (Node *root) {

    if (root == NULL) {

        return 0;
    }

    return height(root->left) - height(root->right);

}

Node *insertAVL (Node *root, Node *nodo) {

 if (root == NULL) {

     return nodo;

 }

 if (root->key > nodo->key) {

     root->left = insertAVL(root->left,nodo);
 }

 else if (root->key < nodo->key) {

     root->right = insertAVL(root->right,nodo);

 }

 root->h = max(height(root->left),height(root->right)) + 1;

 int getBalance = bilanciato(root);

 ///left left case
 if ( (getBalance > 1) && (nodo->key < root->left->key) ) {

     return rotateRightAVL(root);

 }

 //left right case
 if ( (getBalance > 1) && (nodo->key > root->left->key) ) {

     root->left = rotateLeftAVL(root->left);
     return rotateRightAVL(root);

 }


 //right right case
 if ( (getBalance < -1) && (nodo->key > root->right->key) ) {

     return rotateLeftAVL(root);

 }


 //right left case
 if ( (getBalance < -1) && (nodo->key < root->right->key)  ) {

     root->right = rotateRightAVL(root->right);
     return rotateLeftAVL(root);

 }

 return root;

}