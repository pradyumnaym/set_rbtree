typedef struct node{
    int value;
    int color;
    int deleted;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node,set;

void Insert(Node **, int);
void inOrder(Node *);
void preOrder(Node *);
int kthsmallest(Node*,int);
int kthlargest(Node*,int);
Node* Union(Node *a, Node *b);
Node* Intersection(Node *a,Node *b);
Node* Set_difference(Node *a,Node *b);
void deleteNode(Node*,int);
Node* Symmetric_sd(Node *a,Node *b);
int height(Node*);
int heightDifference(Node*,Node*);
int lengthOf(Node*);
void insertBST(Node**,int);
void clearSet(Node*);
int search(Node *a,int e,int flag);
int range(Node *root);
Node* tdelete(Node*,int);