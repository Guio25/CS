enum COLOR { red = 0, black = 1 };

struct node_t {
   int key;
   int h;
   enum COLOR color;
   struct node_t *left;
   struct node_t *right;
   struct node_t *parent;
};
typedef struct node_t Node;
Node *bst;
Node *rbt;
Node *avl;

void insertBST(int);
void insertRBT(int);
Node *insertAVL(Node *, Node *);
Node *create(int);
void rotateLeftRBT(Node *, Node *);
void rotateRightRBT(Node *, Node *);
Node *rotateLeftAVL(Node *);
Node *rotateRightAVL(Node *);
void restoreHeights(Node *);
int max(int, int);