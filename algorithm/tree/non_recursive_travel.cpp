#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;


struct Tree
{
	int nValue;
	Tree* pLeft;
	Tree* pRight;     //  左右指针
};

void CreateTree(Tree** tree)
{
	(*tree) = (Tree*)malloc(sizeof(Tree));
	(*tree)->nValue = 1;

	(*tree)->pLeft = (Tree*)malloc(sizeof(Tree));
	(*tree)->pLeft->nValue = 2;

	(*tree)->pLeft->pLeft = (Tree*)malloc(sizeof(Tree));
	(*tree)->pLeft->pLeft->nValue = 4;
	(*tree)->pLeft->pLeft->pLeft = NULL;
	(*tree)->pLeft->pLeft->pRight = NULL;

	(*tree)->pLeft->pRight = (Tree*)malloc(sizeof(Tree));
	(*tree)->pLeft->pRight->nValue = 5;
	(*tree)->pLeft->pRight->pLeft = NULL;
	(*tree)->pLeft->pRight->pRight = NULL;



	(*tree)->pRight = (Tree*)malloc(sizeof(Tree));
	(*tree)->pRight->nValue = 3;

	(*tree)->pRight->pLeft = (Tree*)malloc(sizeof(Tree));
	(*tree)->pRight->pLeft->nValue = 6;
	(*tree)->pRight->pLeft->pLeft = NULL;
	(*tree)->pRight->pLeft->pRight = NULL;

	(*tree)->pRight->pRight = (Tree*)malloc(sizeof(Tree));
	(*tree)->pRight->pRight->nValue = 7;
	(*tree)->pRight->pRight->pLeft = NULL;
	(*tree)->pRight->pRight->pRight = NULL;

}



struct Stack 
{
	Tree* tree;
	Stack* pNext;
};


void Push(Stack** pTop,Tree* tree)
{
	if (pTop == NULL || tree == NULL)
	{
		return;
	}

	Stack* temp = (Stack*)malloc(sizeof(Stack));
	temp->tree = tree;

	temp->pNext = (*pTop);
	(*pTop) = temp;
}

Tree* Pop(Stack** pTop)
{
	if (pTop == NULL || (*pTop) == NULL)
	{
		return NULL;
	}

	Stack* pDel = (*pTop);
	(*pTop) = (*pTop)->pNext;
	Tree* tree = pDel->tree;
	free(pDel);
	pDel = NULL;
	return tree;

}

void FrontPrint(Tree* tree)    //  前 遍历
{
	Stack* pTop = NULL;
		
	while(1)
	{
		while(tree)   //  把 所有的左 放到栈里
		{	
			printf("%d ",tree->nValue);    //  根

			Push(&pTop,tree);       //  吧这个节点放到栈里

			tree = tree->pLeft;
		}

		tree = Pop(&pTop);    //   通过 出栈  遍历右子树
		
		if (tree == NULL)    //  栈是空 就结束  
		{
			break;
		}
		
		//  遍历右子树
		tree = tree->pRight;
	}

}


void MidPrint(Tree* tree)    //  前 遍历
{
	Stack* pTop = NULL;

	while(1)
	{
		while(tree)   //  把 所有的左 放到栈里
		{	

			Push(&pTop,tree);       //  吧这个节点放到栈里

			tree = tree->pLeft;
		}

		tree = Pop(&pTop);    //   通过 出栈  遍历右子树

		if (tree == NULL)    //  栈是空 就结束  
		{
			break;
		}

		printf("%d ",tree->nValue);    //  根
		//  遍历右子树
		tree = tree->pRight;
	}

}


void EndPrint(Tree* tree)    //  前 遍历
{
	Stack* pTop = NULL;
	
	Tree* bj = NULL;

	while(1)
	{
		while(tree)   //  把 所有的左 放到栈里
		{	

			Push(&pTop,tree);       //  吧这个节点放到栈里

			tree = tree->pLeft;
		}
		
		//  栈如果是NULL  结束
		if (pTop == NULL)    
		{
			break;
		}
		//   通过栈顶元素  遍历右子树
		if (pTop->tree->pRight == NULL || pTop->tree->pRight == bj)
		{
			//  把这个节点删除
			bj = Pop(&pTop);
			printf("%d ",bj->nValue);
		}
		else
		{
			//  通过栈顶元素  遍历右子树
			tree = pTop->tree->pRight;
		}
	}
}


// 非递归方式前序遍历
void pre_order_nr(Tree* root) {
    if (root == nullptr) {
        return ;
    }
    stack<Tree*> sta;
    while(1) {
        std::cout << root->nValue << " ";
        if (root->pRight) {
            sta.push(root->pRight);
        }
        if (root->pLeft) {
            sta.push(root->pLeft);
        }
        if (sta.empty()) {
            break;
        }
        root = sta.top();
        sta.pop();
    }
}




int main()
{

	Tree* root = NULL;
	CreateTree(&root);

	FrontPrint(root);
	printf("\n");
    pre_order_nr(root);
	printf("\n");


	MidPrint(root);
	printf("\n");

	EndPrint(root);
	printf("\n");



	//system("ls");
	return 0;
}
