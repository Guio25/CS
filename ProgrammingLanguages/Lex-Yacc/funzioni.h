

typedef enum {typeId , typeOpr} nodeEnum;


typedef struct constant  {	
	int i;
} conNode;


typedef struct node{
	
  struct nodeTypetag *left;
  struct nodeTypetag *right;
  char *token;
} oprNode;


typedef struct nodeTypetag {
	
    nodeEnum type;

    union{
  
       conNode con;
       oprNode opr;
    };

} nodeType;
