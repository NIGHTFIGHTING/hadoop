#include <stdio.h>
#include <stdlib.h>

struct Tree
{
	int nValue;
	Tree* pLeft;
	Tree* pRight;
};


void InsertTree(Tree** tree,int nInsertValue)
{
	if (tree == NULL)
	{
		return;
	}
	if (*tree == NULL)
	{
		(*tree) = (Tree*)malloc(sizeof(Tree));
		(*tree)->nValue = nInsertValue;
		(*tree)->pLeft = NULL;
		(*tree)->pRight = NULL;
		return;
	}

	//  从 根节点比较   找  存放 nInsertValue 的位置
	while(1)
	{
		if (nInsertValue > (*tree)->nValue)   //  看 和 根节点  谁大
		{
			//  放在右
			if((*tree)->pRight == NULL)
			{
				//  放上  结束
				(*tree)->pRight = (Tree*)malloc(sizeof(Tree));
				(*tree)->pRight->nValue = nInsertValue;
				(*tree)->pRight->pLeft = NULL;
				(*tree)->pRight->pRight = NULL;
				return;
			}
			tree = &((*tree)->pRight);
		}
		else
		{
			//  放在左
			if((*tree)->pLeft == NULL)
			{
				//  放上  结束
				(*tree)->pLeft = (Tree*)malloc(sizeof(Tree));
				(*tree)->pLeft->nValue = nInsertValue;
				(*tree)->pLeft->pLeft = NULL;
				(*tree)->pLeft->pRight = NULL;
				return;
			}
			tree = &((*tree)->pLeft);
		}
	}
}


Tree* CreateTree(int* arr,int nLength)
{
	Tree* root = NULL;

	for(int i=0;i<nLength;i++)
		InsertTree(&root,arr[i]);

	return root;
}


void MidPrint(Tree* tree)
{
	if (tree == NULL)
	{
		return;
	}
	MidPrint(tree->pLeft);
	printf("%d ",tree->nValue);
	MidPrint(tree->pRight);
}


void TreeToList(Tree* tree,Tree** pHead,Tree** pEnd)
{
	if (tree == NULL)
	{
		return;
	}

	TreeToList(tree->pLeft,pHead,pEnd);
	//   ---------把这个节点 放到  链表上-------------------
	if ((*pHead)==NULL)
	{
		(*pHead) = tree;
	}
	else
	{
		(*pEnd)->pRight = tree;
		tree->pLeft = (*pEnd);
	}
	(*pEnd) = tree;
	//   ---------------------------------------------------
	TreeToList(tree->pRight,pHead,pEnd);
}


int main()
{

	int arr[10] = {3,2,5,6,7,8,1,0,4,9};

	Tree* tree = CreateTree(arr,10);

	MidPrint(tree);
	

	Tree* pHead = NULL;
	Tree* pEnd = NULL;
	
	TreeToList(tree,&pHead,&pEnd);
	


	printf("\n");
	while(pHead)
	{
		printf("%d ",pHead->nValue);
		pHead = pHead->pRight;
	}	
	printf("\n");
	while(pEnd)
	{
		printf("%d ",pEnd->nValue);
		pEnd = pEnd->pLeft;
	}




	system("pause");
	return 0;
}