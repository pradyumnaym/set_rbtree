#include<stdio.h>
#include<stdlib.h>
#include "header.h"
//#define test "y0"

int main()
{
	printf("\n/******* SET DATA STRUCTURE *******\\\n");
	Node* a[100];
	Node* b[100];
	
	for(int i=0;i<100;i++){
		a[i]=NULL;b[i]=NULL;
	}
	int choice = 0;
	int tree,number,result;
	
	Node **root,**root1;
	root=&a[1];
	root1=&b[1];

	printf("\n 0.Clear Set\n 1.change set\n 2.display elements of the set\n 3.Insert Element\n 4.kth largest element\n 5.Kth smallest element\n 6.Union of two sets\n 7.Intersection of two sets\n 8.Difference of two sets\n 9.Delete an element\n 10.Symmetric Difference\n 11.Height Difference from normal BST implementation\n 12.Length of the set\n 13.Height of the tree\n 14.Level of a node\n 15.Range of the tree\n 16.Search an element\n 17.Display instructions\n 18.Exit\n\n");
	while(choice < 18) {
		
		printf("Enter choice: ");
		scanf("%d",&choice);
		printf("\n");
		
		switch(choice){
			case 0: clearSet(*root);
				clearSet(*root1);
				if(*root) free(*root);
				if(*root1)free(*root1);
				*root=NULL;
				*root1=NULL;
				break;

			case 1:	printf("Enter which set you want to use: ");
				scanf("%d",&tree);
				root=&a[tree];
				root1=&b[tree];
				printf("\n\n");
				break;

			case 2: inOrder(*root);
				break;

			case 3: printf("enter the element: ");
				scanf("%d",&number);
				Insert(root,number);
				insertBST(root1,number);
				printf("\n");
				break;

			case 4: printf("Enter k: ");
				scanf("%d",&number);
				printf("The kth largest number is %d\n\n",kthlargest(*root,number));
				break;

			case 5: printf("Enter k: ");
				scanf("%d",&number);
				printf("The kth smallest number is %d\n\n",kthsmallest(*root,number));
				break;

			case 6: printf("enter the second set number and the set to store the result: ");
				scanf("%d %d",&tree,&number);
				a[number]=Union(*root,a[tree]);
				printf("The result is:\n");
				inOrder(a[number]);
				break;

			case 7: printf("enter the second set number and the set to store the result: ");
				scanf("%d %d",&tree,&number);
				a[number]=Intersection(*root,a[tree]);
				printf("The result is:\n");
				inOrder(a[number]);
				break;

			case 8: printf("enter the second set number and the set to store the result: ");
				scanf("%d %d",&tree,&number);
				a[number]=Set_difference(*root,a[tree]);
				printf("The result is:\n");
				inOrder(a[number]);
				break;

			case 10:printf("enter the second set number and the set to store the result: ");
				scanf("%d %d",&tree,&number);
				a[number]=Symmetric_sd(*root,a[tree]);
				printf("The result is the set below and the result is stored in set %d\n",number);
				inOrder(a[number]);
				break;

			case 9: printf("Enter the element: ");
				scanf("%d",&number);
				deleteNode(*root,number);
				*root1=tdelete(*root1,number);
				inOrder(*root1);
				break;

			case 11:printf("This tree would have had %d more levels in the BST\n",heightDifference(*root,*root1));
				break;

			case 12:printf("The length of the set is: %d\n\n",lengthOf(*root));
				break;

			case 13:printf("The height of the tree is: %d\n\n",height(*root));
				break;

			case 14:printf("Enter element whose level is to be found: ");
				scanf("%d",&number);
				printf("\nLevel of %d: %d\n\n",number,search(*root,number,1));
				break;
			
			case 15:printf("Range of set: %d\n\n",range(*root));
				break;

			case 16:printf("Enter element to be searched: ");
				scanf("%d",&number);
				int result = search(*root,number,0);
				if(result == 0) printf("\nNull set\n\n");
				else if(result == -1) printf("\nElement not in set\n\n");
				else printf("\nElement is present in set\n\n");
				break;

			case 17:printf("\n 0.Clear Set\n 1.change set\n 2.display elements of the set\n 3.Insert Element\n 4.kth largest element\n 5.Kth smallest element\n 6.Union of two sets\n 7.Intersection of two sets\n 8.Difference of two sets\n 9.Delete an element\n 10.Symmetric Difference\n 11.Height Difference from normal BST implementation\n 12.Length of the set\n 13.Height of the tree\n 14.Level of a node\n 15.Range of the tree\n 16.Search an element\n 17.Display instructions\n 18.Exit\n\n");
				break; 
		}
	}

}
