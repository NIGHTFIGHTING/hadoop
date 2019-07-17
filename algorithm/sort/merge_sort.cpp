#include<stdio.h>
#include<stdlib.h>

//    陆芦脕陆脳茅脫脨脨貌碌脛  潞脧虏垄鲁脡脪禄赂枚脨脗碌脛 

void Sort(int* arr,int low,int high)
{
  //  路脰脳茅
  int iBegin1 = low;
  int iEnd1 = (low+high)/2;

  int iBegin2 = iEnd1+1;
  int iEnd2 = high;

  //  脡锚脟毛脪禄赂枚脨脗碌脛脢媒脳茅   脳掳  脜脜潞脙脨貌碌脛陆谩鹿没
  int* temp = (int*)malloc(4*(high-low+1));
  int k = 0;
  //  卤脠陆脧脙驴脪禄脳茅碌脛 碌脷脪禄赂枚脭陋脣脴
  while(iBegin1 <= iEnd1 && iBegin2 <= iEnd2)
  {  
      //  脮脪脪禄赂枚脨隆碌脛 麓忙碌陆 temp
      if(arr[iBegin1] < arr[iBegin2])
          temp[k++] = arr[iBegin1++];
      else
          temp[k++] = arr[iBegin2++];
  }

  //  脫脨脪禄脳茅脫脨脢拢脫脿
  while(iBegin1 <= iEnd1)
      temp[k++] = arr[iBegin1++];

  while(iBegin2 <= iEnd2)
      temp[k++] = arr[iBegin2++];

  //  掳脩 脨脗碌脛脢媒脳茅碌脛脭陋脣脴 路脜禄脴碌陆露脭脫娄碌脛脦禄脰脙
  for(k=0;k<(high-low+1);k++)
      arr[low+k] = temp[k];

  free(temp);
}

void MergeSort(int* arr,int low,int high)
{
  if(low < high)  //  脫脨脕陆赂枚脪脭脡脧脪陋脜脜脨貌
  {
      int mid = (low+high)/2;
      //  路脰脳茅
      MergeSort(arr,low,mid);
      MergeSort(arr,mid+1,high);
      //  潞脧虏垄
      Sort(arr,low,high);
  }
}

void AA(int* arr,int n)
{
  if(arr == NULL || n <= 0)
      return;

  MergeSort(arr,0,n-1);
}


int main()
{

  int arr[10] = {2,3,1,4,5,2,6,8,7,0};
      
  AA(arr,10);

  for(int i=0;i<10;i++)
      printf("%d ",arr[i]);

  system("ls");
  return 0;
}
