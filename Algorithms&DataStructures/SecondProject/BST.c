#include <stdio.h>
#include <stdlib.h>

#include "funzioni.h"

void insertBST(int k) {

     if (bst==NULL) {
        bst = (Node *) malloc(sizeof(Node));
        bst->key = k;
        bst->right = NULL;
        bst->left = NULL;
     }

     else {

        Node *x = bst;
        Node *y = NULL;
        while (x!=NULL) {
           y = x;
           if (k > x->key)
              x = x->right;
           else
              x = x->left;
        }

        x = (Node *) malloc(sizeof(Node));
        x->key = k;
        x->right = NULL;
        x->left = NULL;
        if (y->key < k)
           y->right = x;
        else
           y->left = x;   
     }
}
