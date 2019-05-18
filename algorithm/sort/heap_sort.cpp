#include<stdio.h>
#include<stdlib.h>


#define LEFT   2*nRootID+1 
#define RIGHT  2*nRootID+2



void Sort(int* arr,int n,int nRootID)
{
	while(1)
	{
		// 有两个子节点
		if(RIGHT < n)
		{
			//  左右比较
			if(arr[LEFT] > arr[RIGHT])
			{
				if(arr[LEFT] > arr[nRootID])
				{
					//  交换
					arr[LEFT] = arr[LEFT]^arr[nRootID];
					arr[nRootID] = arr[LEFT]^arr[nRootID];
					arr[LEFT] = arr[LEFT]^arr[nRootID];
					//  以左边为根 继续比较
					nRootID = LEFT;
					continue;
				}
				break;
			}
			else
			{
				if(arr[RIGHT] > arr[nRootID])
				{
					//  交换
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];
					arr[nRootID] = arr[RIGHT]^arr[nRootID];
					arr[RIGHT] = arr[RIGHT]^arr[nRootID];
					//  以左边为根 继续比较
					nRootID = RIGHT;
					continue;
				}
				break;
			}
		}
		else if(LEFT < n)    // 有一个
		{
			//   直接拿 左 和根比较
			if(arr[LEFT] > arr[nRootID])
			{
				//  交换
				arr[LEFT] = arr[LEFT]^arr[nRootID];
				arr[nRootID] = arr[LEFT]^arr[nRootID];
				arr[LEFT] = arr[LEFT]^arr[nRootID];
			}
			break;
		}
		else   //        两个都没有
		{
			break;
		}
	}
}


void Sort(int* arr,int n,int nRootID)
{
	for(int MAX = LEFT;MAX < n;MAX = LEFT) //   每次  认为 LEFT 是 最大的  拿MAX记住下标 
	{
		if(RIGHT < n)  //    有右边
		{
			if(arr[LEFT] < arr[RIGHT])
			{
				MAX = RIGHT;
			}
		}
		//   MAX  一定记住的 是最大的那个子节点   和根比较
		if(arr[MAX] > arr[nRootID])
		{
			// 交换
			arr[MAX]     = arr[MAX]^arr[nRootID];
			arr[nRootID]  = arr[MAX]^arr[nRootID];
			arr[MAX]     = arr[MAX]^arr[nRootID];
			//  以交换的那个节点为根继续比较
			nRootID = MAX;
			continue;
		}
		break;
	}
}




void HeapSort(int* arr,int n)
{
	//  创建  初始堆
	for(int i=n/2-1;i>=0;i--)
		Sort(arr,n,i);
	//  交换调整
	for(int i=n-1;i>0;i--)
	{
		arr[0] = arr[0]^arr[i];
		arr[i] = arr[0]^arr[i];
		arr[0] = arr[0]^arr[i];
		//  重新调整
		Sort(arr,i,0);
	}
}


int main()
{
	int arr[10] = {2,3,1,4,5,2,6,8,7,0};
		
	HeapSort(arr,10);

	for(int i=0;i<10;i++)
		printf("%d ",arr[i]);

	system("pause");
	return 0;
}
