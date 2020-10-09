#include"header.h"
#include<stdlib.h>
#include<stdio.h>
//#define test "yes"


//static declarations
static void inorder_push(Node *a);
static void preorder_push(Node *a);
static void print_stack();
static int realloc_stack();

int maxsize = 1000;
Node** stk;
int t=-1;

Node* pop(){
    return stk[t--];
}

static int realloc_stack() {
	maxsize *= 2;
    printf("In Realloc");
    fflush(stdout);
	Node** tmp_ptr = realloc(stk, maxsize);
	if (tmp_ptr == NULL) {
		// realloc failed, orig_ptr still valid so you can clean up
		return -1;
	}
	else {
		// Only overwrite orig_ptr once you know the call was successful
		stk = tmp_ptr;
	}
	return 1;
}

void push(Node* a){
    stk[++t]=a;
}

int full() {
	return t==(maxsize-1);
}

int empty(){
    return t==-1;
}
void initstack(){
    free(stk);
    stk = malloc(sizeof(Node*)*maxsize);
    t=-1;
}

Node* getNode(int value){
    Node* temp=malloc(sizeof(Node));
    temp->left=NULL;
    temp->right=NULL;
    temp->parent=NULL;
    temp->value=value;
    temp->color=0; //red by default
    temp->deleted=0;
    return temp;
}

void print_stack() {
	printf("{ ");
	Node *temp;
    int x=0;
	while(x<t) {
		temp = stk[x++];
		printf("%d, ",temp->value);
	}
	if((t!=-1)&&(x==t)) {
		temp = stk[x];
		printf("%d }\n\n",temp->value);
	}
    else printf("}\n\n");
}

void inOrder(Node* n){
    #ifdef test
    if(n!=NULL){
        inOrder(n->left);
        printf("(%d-",n->value);
        if(n->color) printf("B ");
        else printf("R ");
        if(n->parent) printf("P-%d)",n->parent->value);
        else printf("p-NULL)");
        inOrder(n->right);
    }
    #endif
    #ifndef test
        initstack();
        inorder_push(n);
        print_stack();
    #endif
}

Node* Uncle(Node* x){
    Node* g = x->parent->parent;  //grandparent
    if(g->left == x->parent){
        return g->right;
    }
    else{
        return g->left;
    }
}

void preOrder(Node* n){
    initstack();
    preorder_push(n);
    print_stack();
}

void leftRotate(Node* n,Node** root){
    if(*root ==n){
        *root=n->right;
        #ifdef test
            printf("ya, %d is the new root\n",(*root)->value);
            fflush(stdout);
        #endif
    }
    #ifdef test
        printf("Lrotate %d \n",n->value);
    #endif
    if(n->parent) {
        #ifdef test
            printf("parent exists and value is %d\n",n->parent->value);
        #endif
        if(n->parent->right==n)
            n->parent->right=n->right;
        else
            n->parent->left=n->right;
    }
    fflush(stdout);
    n->right->parent=n->parent;
    n->parent=n->right;
    Node* childLeft=n->right->left;
    n->right->left=n; 
    n->right=childLeft;
    if(childLeft) childLeft->parent=n;
    fflush(stdout);
}

void rightRotate(Node* n,Node** root){
    if(*root==n){
        *root=n->left;
        #ifdef test
            printf("ya, %d is the new root\n",(*root)->value);
            fflush(stdout);
        #endif
    }
    #ifdef test
        printf("Rrotate %d\n",n->value);
        fflush(stdout);
    #endif
    if(n->parent) {
        #ifdef test
            printf("parent exists and value is %d\n",n->parent->value);
        #endif
        if(n->parent->right==n)
            n->parent->right=n->left;
        else
            n->parent->left=n->left;
    }
    n->left->parent=n->parent;
    fflush(stdout);
    n->parent=n->left;
    fflush(stdout);
    Node* childRight=n->left->right;
    fflush(stdout);
    n->left->right=n;
    fflush(stdout);
    n->left=childRight;
    if(childRight!=NULL) childRight->parent=n;
}

void swapColors(Node* a,Node* b){
    #ifdef test
        printf("Swap colors of %d and %d\n",a->value,b->value);
    #endif
    /*fflush(stdout);
    int temp=a->color;
    a->color=b->color;
    b->color=temp;*///both are same
    a->color=!a->color;
    b->color=!b->color;

}

void balanceTree(Node *x,Node** root){
    if(x->parent==NULL){
        //root node
        x->color=1;
        #ifdef test
            printf("rootNode,Making it BLACK\n");
            fflush(stdout);
        #endif
    }
    if((x->parent) &&x->parent->color==0){
        if((Uncle(x)==NULL) || (Uncle(x)->color==1)){
            //four cases , 3 b)
            if((x->parent->parent->left ==x->parent) && (x->parent->left==x)){
                //LL case
                #ifdef test
                    printf("LL case!!\n");
                #endif
                fflush(stdout);
                swapColors(x->parent,x->parent->parent);
                rightRotate(x->parent->parent,root);
            }
            else if((x->parent->parent->left ==x->parent) && (x->parent->right==x)){
                //LR case
                #ifdef test
                    printf("LR case\n");
                    fflush(stdout);
                #endif
                swapColors(x->parent->parent,x);
                leftRotate(x->parent,root);
                rightRotate(x->parent,root);
            }
            else if((x->parent->parent->right==x->parent) && (x->parent->left==x)){
                //RL case
                #ifdef test
                    printf("RL case \n");
                    fflush(stdout);
                #endif
                swapColors(x,x->parent->parent);
                rightRotate(x->parent,root);
                leftRotate(x->parent,root);
            }
            else if((x->parent->parent->right ==x->parent) && (x->parent->right==x)){
                //RR case
                #ifdef test
                    printf("RR case\n");
                    fflush(stdout);
                #endif
                swapColors(x->parent,x->parent->parent);
                leftRotate(x->parent->parent,root);
            }
            
        }
        else if(Uncle(x)->color==0){
            //recolor, case 3 a)
            #ifdef test
                printf("Recoloring is enough\n");
                fflush(stdout);
            #endif
            Uncle(x)->color=1;  //no need to NULL check since the color is RED!!
            x->parent->color=1;
            x->parent->parent->color=0;
            balanceTree(x->parent->parent,root);
        }
        
    }
    else{
        //proper, parent is black
        #ifdef test
            printf("Proper, no change Required\n");
            fflush(stdout);
        #endif
    }
}


void Insert(Node** n,int value){
    if(*n == NULL) {
        *n=getNode(value);
        (*n)->color=1; //root node should be black
        #ifdef test
            printf("Creating root\n");
	    fflush(stdout);
        #endif
        return;
    }
    Node* previous,*present=*n;
    while(present!=NULL){
        previous=present;
        if(present->value >value) present=present->left;
        else if(present->value<value) present=present->right;
        else{
            present->deleted=0;
            return; //Set!!!

        }
    }
    if(value>previous->value){
        previous->right=getNode(value);
        previous->right->parent=previous;
        balanceTree(previous->right,n);
    }
    else{
        previous->left=getNode(value);
        previous->left->parent=previous;
        balanceTree(previous->left,n);
    }
    (*n)->color=1; //root = Black
}

int kthsmallest(Node* a,int k){
    initstack();
    Node* pres= a;
    while(pres){
        push(pres);
        pres=pres->left;
    }
    while(!empty()){
        Node* x= pop();
        if(!x->deleted) k-=1;
        if(!k) return x->value;
        x=x->right;
        while(x){
            push(x);
            x=x->left;
    
    }
    }
    return -1;
}

int kthlargest(Node* a,int k){
    initstack();
    Node* pres= a;
    while(pres){
        push(pres);
        pres=pres->right;
    }
    while(!empty()){
        Node* x= pop();
        if(!x->deleted) k-=1;
        if(!k) return x->value;
        x=x->left;
        while(x){
            push(x);
            x=x->right;
        }
    }
    return -1;
}

Node* Union(Node *a, Node *b) {
	initstack();
	inorder_push(a);
	inorder_push(b);

	Node *res = NULL;
	while(!empty()) {
		Node *x = pop();
		Insert(&res,x->value);
	}
	return res;

}

int search(Node *a,int e,int flag) { //flag -0 search flag -1 level
	if((flag==1)&&(a == NULL))return -1;
	if((flag==0)&&(a == NULL)) return 0;
	int level = 1;
	while(a != NULL && a->value != e) {
		if(a->value < e) 
			a = a->right;
		else
			a = a->left;
		level += 1;
	}
	if(flag == 0) {
		if(a == NULL) {
			return 0;
		}
		else
			return 1;
	}
	if(a == NULL) return -1;
	return level;
}

Node* Intersection(Node *a,Node *b) {
	initstack();
	inorder_push(a);

	Node*res = NULL;
	int l;
	while(!empty()) {
		Node *x = pop();
		l = search(b,x->value,0);
		if(l == 1) {
			Insert(&res,x->value);
		}
	}
	return res;
}

Node* Set_difference(Node *a,Node *b) {
	Node *c = Intersection(a,b);

	initstack();
	inorder_push(a);

	Node *res = NULL;
	int l;
	while(!empty()) {
		Node *x = pop();
		l = search(c,x->value,0);
		if(l == -1 || l == 0) {
			Insert(&res,x->value);
		}	
	}

	return res;
}

Node* Symmetric_sd(Node *a,Node *b) {
	Node *c = Set_difference(a,b);
	Node *d = Set_difference(b,a);
	
	return Union(c,d);
}

static void inorder_push(Node *a) {
	if(a == NULL)
		return;

	inorder_push(a->left);

	if(!(full())) { 
		if(a->deleted == 0) {
			push(a);
		}
	}
	else {
		int check = realloc_stack();
		if(check == 1) {
			if(a->deleted == 0) {
				push(a);
			}
		}
	}

	inorder_push(a->right);	
}

static void preorder_push(Node *a) {
	if(a == NULL) return;

	if(!(full())) { 
		if(a->deleted == 0) {
			push(a);
		}
	}
	else {
		int check = realloc_stack();
		if(check == 1) {
			if(a->deleted == 0) {
				push(a);
			}
		}
	}

	preorder_push(a->left);
	preorder_push(a->right);	
} 

void deleteNode(Node* a,int val){
    while(a!=NULL){
        if(a->value>val) a=a->left;
        else if(a->value<val) a=a->right;
        else break;
    }
    if(a){
        a->deleted=1;
    }
}

void insertBST(Node** n,int value){
    if(*n == NULL) {
        *n=getNode(value);
        return;
    }
    Node* previous,*present=*n;
    while(present!=NULL){
        previous=present;
        if(present->value >value) present=present->left;
        else if(present->value<value) present=present->right;
        else{
            return;
        }
    }
    if(value>previous->value){
        previous->right=getNode(value);
    }
    else{
        previous->left=getNode(value);
    }
}

int lengthOf(Node* root){
    initstack();
    inorder_push(root);
    return t+1;
}

int height(Node* root){
    if(root==NULL) return -1;
    else
    {
        int hl=height(root->left);
        int hr=height(root->right);
        return (1+(hl>hr?hl:hr));
    }
    
}

int heightDifference(Node* root,Node* root1){
    return height(root1)-height(root);
}


void clearSet(Node* a){
    if(a==NULL) return;
    else{
        clearSet(a->left);
        clearSet(a->right);
        free(a->left);
        free(a->right);
    }
}

int range(Node *root) {
	int l = kthlargest(root,1);
	int r = kthsmallest(root,1);
	return l-r;
}

Node* tdelete(Node *t, int key)
  {
    Node *prev, *curr, *p, *q, *temp;
    prev=NULL;
    curr=t;
   while((curr!=NULL)&&(curr->value!=key))
   {
     prev=curr;
     if(key<curr->value)
      curr=curr->left;
     else
      curr=curr->right;
    }
    if(curr==NULL)
    {
      printf("Key not found..\n");
      return t;
    }
    if((curr->left==NULL)||(curr->right==NULL))
    {
      if(curr->left==NULL)
        q=curr->right;
      else
        q=curr->left;
    if(prev==NULL)//deleting root
      return q;
    if(curr==prev->left)
        prev->left=q;
     else
        prev->right=q;
    free(curr);
   }
   else
   {
     p=NULL;//for the parent of inorder successor     
     temp=curr->right;
     while(temp->left!=NULL)
     {
       p=temp;
       temp=temp->left;
     }
     if(p!=NULL)
      p->left=temp->right;
     else 
      curr->right =temp->right;
     curr->value=temp->value;
     free(temp);
    }
    return t;
   }
