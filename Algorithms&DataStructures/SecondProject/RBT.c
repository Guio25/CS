#include <stdio.h>
#include <stdlib.h>

#include "funzioni.h"

void rotateRightRBT(Node *n, Node *x) {    //n: nodo perno, x: figlio

    Node *b;     //padre del nodo perno
    b=n->parent;

    //rotazione a dx
    
    if (b==NULL) {             //    il bisnonno è NULL quindi il nonno è la radice
        n->left = x->right;
	if (n->left!=NULL)
	    n->left->parent = n;
        x->right = n;
	n->parent = x;
	x->parent = NULL;
        rbt = x;

    }
    
    else {
        
        if (n==b->left)
            b->left=x;
        else
            b->right=x;
        
	x->parent = b;
        n->left=x->right;
	if (n->left!=NULL)
  	   n->left->parent = n;
        x->right = n;
	n->parent = x;
    }
    
}

void rotateLeftRBT(Node *n, Node *x) {    

    Node *b;     //padre di n
    b=n->parent;
  
    //rotazione a sx
    
    if (b==NULL) {                    
        n->right = x->left;
	if (n->right!=NULL)
	    n->right->parent = n;
        x->left = n;
	n->parent = x;
	x->parent = NULL;
        rbt = x;
    }
    
    else {
        
        if (n==b->left)
            b->left=x;
        else
            b->right=x;
        
        x->parent = b;
        n->right=x->left;
	if (n->right!=NULL)
	    n->right->parent = n;
        x->left = n;
	n->parent = x;
    }
    
}

void insertRBT(int k) {

     if (rbt==NULL) {
        rbt = (Node *) malloc(sizeof(Node));
        rbt->key = k;
        rbt->color = black;
        rbt->right = NULL;
        rbt->left = NULL;
	rbt->parent = NULL;
     }

     else {

        Node *y = NULL;
        Node *x = rbt;
        while (x!=NULL) {
           y = x;
           if (k > x->key)
              x = x->right;
           else
              x = x->left;
        }

        x = (Node *) malloc(sizeof(Node));
        x->key = k;
        x->color = red;
        x->right = NULL;
        x->left = NULL;
        if (y->key < k)
           y->right = x;
        else
           y->left = x;

	x->parent = y;
 
        Node *n;          //nonno
        Node *p;          //padre
        Node *z;          //zio

	n = x->parent->parent;
        p = x->parent;

        while (x->color==red && p->color==red && x!=rbt) {

	    if (x->key < n->key) 
                z=n->right;
            else
                z=n->left;
 
            if ((z==NULL || z->color==black) && (x==p->left && z==n->right || x==p->right && z==n->left)) {               //caso 1: zio di x BLACK e opposto a x
                if (z==n->left)
                    rotateLeftRBT(n, p);
                else
                    rotateRightRBT(n, p);
                    
                p->color=black;
                n->color=red;

            }
            
            else if ((z==NULL || z->color==black) && (x==p->left && z==n->left || x==p->right && z==n->right)) {          //caso 2: zio di x BLACK ma dallo stesso lato di x
                if (x==p->left)
                    rotateRightRBT(p, x);
                else
                    rotateLeftRBT(p, x);
                    
                x=p;                                                                                            //caso 1
            }
            
            else if (z!=NULL && z->color==red) {                                  //caso 3
                p->color=black;
                n->color=red;
                z->color=black;
                x=n;
            }

            if (x->parent==NULL || x->parent==rbt)
                x=rbt;

            else {
                n = x->parent->parent;
                p = x->parent;
            }

        }
        
        if (x==rbt && x->color==red)
            x->color=black;
 
     }
    
}