./a.out: codice.o BST.o RBT.o AVL.o
	clang codice.o BST.o RBT.o AVL.o -lm
BST.o: funzioni.h BST.c
	clang -c BST.c
RBT.o: funzioni.h RBT.c
	clang -c RBT.c
AVL.o: funzioni.h AVL.c
	clang -c AVL.c
codice.o: funzioni.h codice.c
	clang -c codice.c