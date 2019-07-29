#include<stdio.h>
#include<stdlib.h>
   
//int Sort(int* arr,int low,int high)   //  ½«  ´Ólow µ½ high  ÅÅÐò
//{
//    int temp = arr[low];   //  ÖÐ¼ä±äÁ¿
//
//    while(1)
//    {
//        while(1)   //  ÔÚ high  ÕÒÒ»¸ö  ±Ètemp Ð¡µÄ  ´æµ½  low
//        {
//            if(low == high)
//            {
//                arr[low] = temp;
//                return low;
//            }
//            if(arr[high] < temp)
//            {
//                //  ÈÓµ½ ÁíÒ»±ß
//                arr[low] = arr[high];
//                low++;
//                break;
//            }
//            high--;   //  ¼ÌÐøÕÒ
//        }
//        while(1)    //  ÔÚ low   ÕÒÒ»¸ö  ±Ètemp ´óµÄ  ´æµ½  high
//        {
//            if(low == high)
//            {
//                arr[low] = temp;
//                return low;
//            }
//            if(arr[low] >= temp)
//            {
//                //  ÈÓµ½ ÁíÒ»±ß
//                arr[high] = arr[low];
//                high--;
//                break;
//            }
//            low++;   //  ¼ÌÐøÕÒ
//        }
//    }
//}


typedef bool (*PFUN)(int a,int b);

bool AA(int a,int b)
{
  return !((a+b)%2);
}

//空间复杂度log(N)


int Sort(int* arr,int low,int high,PFUN pfun)   //  ½«  ´Ólow µ½ high  ÅÅÐò
{
  int nSmall = low-1;   //  nSmall Ç°ÃæËùÓÐµÄ  ¶¼ÊÇ ±È  highÐ¡µÄ
                       //  nSmall µ½ low  µÄÕâÐ´ÔªËØ ¶¼ high ´óµÄ
                      //   low ºóÃæµÄÔªËØ  ¶¼Ã»ÓÐ±È½ÏµÄ
  for(;low<high;low++)
  {
      //  ÕÒÒ»¸ö±Èarr[high] Ð¡µÄ
      if(pfun(arr[low],arr[high]))
      {
          nSmall++;    //  ÕÒµ½Ò»¸öÐ¡µÄÁË  °Ñ Ð¡µÄ Êý×éµÄ·¶Î§À©´ó

          if(nSmall != low)   //  (nSmall == low) Ã»ÓÐ´óµÄ½»»»
          {
              //  ½»»»
              arr[nSmall] =  arr[nSmall]^arr[low];
              arr[low] =  arr[nSmall]^arr[low];
              arr[nSmall] =  arr[nSmall]^arr[low];
          }
      }
  }
  //   °Ñ high  ·Åµ½ ÖÐ¼ä¶ÔÓ¦µÄÎ»ÖÃ
  nSmall++;
  if(nSmall != high)
  {
      arr[nSmall] =  arr[nSmall]^arr[high];
      arr[high] =  arr[nSmall]^arr[high];
      arr[nSmall] =  arr[nSmall]^arr[high];
  }

  return nSmall;   // ·µ»ØÖÐ¼äÔªËØµÄÏÂ±ê
}   

void QuickSort(int* arr,int low,int high,PFUN pfun)
{
  if(low < high)   //   low µ½ high  ÕâÒ»¶ÎÓÐÁ½¸öÒÔÉÏ  ÒªÅÅÐò
  {
      int mid = Sort(arr,low,high,pfun);
      //  Í¨¹ý  mid  ·Ö×é 
      QuickSort(arr,low,mid-1,pfun);
      QuickSort(arr,mid+1,high,pfun);
  }
}


int main()
{

  int arr[10] = {2,3,1,4,5,2,6,8,7,0};
      
  QuickSort(arr,0,9,&AA);

  for(int i=0;i<10;i++)
      printf("%d ",arr[i]);

  system("ls");
  return 0;
}
