#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


struct Node
{
    int nValue;
    Node* pNext;
    Node* pPre;
};

void Push_Front(Node** pHead,int nValue)
{
    if(pHead == NULL)
        return ;

    Node* temp = (Node*)malloc(sizeof(Node));
    temp->nValue = nValue;
    temp->pPre = NULL;

    temp->pNext = *pHead;
    if(*pHead != NULL)
        (*pHead)->pPre = temp;
    //  脥路卤盲鲁脡脨脗脌麓脕脣
    (*pHead) = temp;
}

void Sort(Node* pHead)
{
    //  脜脜脨貌脪禄赂枚脥掳碌脛

    Node* pi = pHead->pNext;
    Node* pj;

    while(pi)
    {
        pj = pi->pPre;   //  脙驴麓脦录脟脳隆i 碌脛脟掳脪禄赂枚

        int temp = pi->nValue;
        //  虏茅脮脪麓忙路脜 temp 碌脛脛脟赂枚陆脷碌茫
        while(pj != NULL && pj->nValue > temp)
        {
            pj->pNext->nValue = pj->nValue;
            pj = pj->pPre;
        }

        //  掳脩temp  路脜碌陆 j+1
        if(pj == NULL)
        {
            pHead->nValue = temp;
        }
        else
        {
            pj->pNext->nValue = temp;
        }

        pi = pi->pNext;
    }
}

void BucketSort(int* arr,int n)
{
    if(arr == NULL || n <= 0)
        return;
    //  脮脪碌陆  脳卯麓贸脰碌潞脥  脳卯脨隆脰碌
    int MIN = arr[0];
    int MAX = arr[0];

    for(int i=1;i<n;i++)
    {
        if(arr[i] > MAX)
            MAX = arr[i];
        else if(arr[i] < MIN)
            MIN = arr[i];
    }

    int nIndexMax = MAX/10;
    int nIndexMin = MIN/10;
    //  麓麓陆篓 脥掳
    Node** pBucket = (Node**)malloc(4*(nIndexMax-nIndexMin+1));
    memset(pBucket,0,4*(nIndexMax-nIndexMin+1));

    //  掳脩脣霉脫脨碌脛脭陋脣脴 路脜碌陆露脭脫娄碌脛脥掳脌茂
    for(int i=0;i<n;i++)
    {
        int index = arr[i]/10-nIndexMin;
        Push_Front(&pBucket[index],arr[i]);
    }

    //  掳脩脙驴赂枚脥掳 脜脜脨貌
    for(int i=0;i<(nIndexMax-nIndexMin+1);i++)
    {
        if(pBucket[i] != NULL)
            Sort(pBucket[i]);
    }
    int k=0;
    for(int i=0;i<(nIndexMax-nIndexMin+1);i++)
    {
        //   掳脩 脥掳脌茂碌脛 露芦脦梅  路脜禄脴碌陆 脭颅脌麓碌脛脢媒脳茅脌茂  脥卢脢卤脡戮鲁媒脥掳
        Node* temp = NULL;
        while(pBucket[i])
        {
            temp = pBucket[i];
            pBucket[i] = pBucket[i]->pNext;

            arr[k++] = temp->nValue;
            free(temp);
        }
    }

    free(pBucket);
}

int main()
{
    int arr[10] = {2,3,1,4,5,2,6,8,7,0};

    BucketSort(arr,10);

    for(int i=0;i<10;i++)
        printf("%d ",arr[i]);


    system("pause");
    return 0;
}
