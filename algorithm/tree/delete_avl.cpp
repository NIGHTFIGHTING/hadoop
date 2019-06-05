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


void FindValue(Tree* tree,int nDelValue,Tree** pDel,Tree** pFather)
{
	if (tree == NULL || pDel == NULL || pFather == NULL)
	{
		return;
	}
	
	(*pFather) = NULL;
	(*pDel)    = NULL;

	while(tree != NULL)
	{
		// 和根节点比较
		if(tree->nValue == nDelValue)
		{
			//  记住 要删除的节点
			(*pDel) = tree;
			return;
		}
		else
		{
			//   tree  有可能是父亲节点 
			(*pFather) = tree;
			//   去 左边  或者右边继续查找
			if (tree->nValue > nDelValue)
			{
				tree = tree->pLeft;
			}
			else
			{
				tree = tree->pRight;
			}
		}
	}

	//  没找到
	(*pFather) = NULL;
}

void DelOneChild(Tree* pDel,Tree* pFather)
{
	if (pDel == NULL)
	{
		return ;
	}

	//  看 要删除的  这个节点  是在他父亲的左边还是右边
	if (pDel == pFather->pLeft)
	{
		//  让 pFather 的左指针  指向 pDel 不为空的那个子节点
		pFather->pLeft = pDel->pLeft?pDel->pLeft:pDel->pRight;
	}
	else
	{
		pFather->pRight = pDel->pLeft?pDel->pLeft:pDel->pRight;
	}

	//  删除 pDel
	free(pDel);
	pDel = NULL;
}


void DeleteTree(Tree** tree,int nDelValue)
{
	if (tree == NULL)
	{
		return;
	}

	//   找到  要删除的节点
	Tree* pDel = NULL;
	Tree* pFather = NULL;
	
	FindValue(*tree,nDelValue,&pDel,&pFather);

	//  看  是否找到了
	if (pDel == NULL)
	{
		printf("没找到要删除的节点");
		return;
	}


	//    看  要删除的节点  是否有两个子节点
	if (pDel->pLeft != NULL && pDel->pRight != NULL)
	{
		//   把它转换成 只有一个子节点
		Tree* bj = pDel;

		pDel = pDel->pRight;
		pFather = bj;
		//   在 右子树 找一个最小
		while(pDel->pLeft)
		{
			pFather = pDel;
			pDel = pDel->pLeft;
		}
		//   pDel  和 bj  这个节点里的值交换
		bj->nValue = pDel->nValue;
	}
	
	//   一定  只有一个子节点   要删除的节点是不是根节点
	if (pDel == (*tree))
	{
		//  让 根 指向 不为空那个子节点
		(*tree) = pDel->pLeft?pDel->pLeft:pDel->pRight;
		//  删除标记
		free(pDel);
		pDel = NULL;
		return;
	}

	DelOneChild(pDel,pFather);
}

int main()
{

	int arr[10] = {3,24,1,5,2,7,8,9,0,6};

	Tree* tree = CreateTree(arr,10);
	
	DeleteTree(&tree,9);

	MidPrint(tree);



	system("pause");
	return 0;
}