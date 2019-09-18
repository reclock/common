// pai_xu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <regex>
#include <iostream>
using namespace std;

//冒泡排序

//比较相邻的元素。如果第一个比第二个大，就交换他们两个。
//对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
//针对所有的元素重复以上的步骤，除了最后一个。
//持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较
void bubbleSort(int ret[],int len)
{
	int temp=0;
	for (int i = 0;i < len-1;i++)
	{
		for (int m=0;m<len-i-1;m++)
		{
			if (ret[m] > ret[m+1])
			{
				temp = ret[m+1];
				ret[m+1]=ret[m];
				ret[m]=temp;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//选择排序

//  首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。
//	再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
//	重复第二步，直到所有元素均排序完毕。
//////////////////////////////////////////////////////////////////////////
void selectSort(int arr[],int len)
{
	int temp = 0;
	for (int m = 0;m<len;m++)
	{
		int temp = m;
		for (int j=m;j<len;j++)
		{
			if(arr[temp] > arr[j])
			{
				temp = j;
 			}
		}
		int tempNum = arr[temp];
		arr[temp] = arr[m];
		arr[m] = tempNum;
	}
}



//////////////////////////////////////////////////////////////////////////
//插入排序

//将第一待排序序列第一个元素看做一个有序序列，把第二个元素到最后一个元素当成是未排序序列。
//从头到尾依次扫描未排序序列，将扫描到的每个元素插入有序序列的适当位置。
//（如果待插入的元素与有序序列中的某个元素相等，则将待插入元素插入到相等元素的后面。）
//////////////////////////////////////////////////////////////////////////
void insertSort(int arr[],int length)
{
	for (int i = 0;i<length-1;i++)
	{
		int temp = i;
		for (int j=i;j>=0;j--)
		{
			if (arr[j] > arr[j+1])
			{
				temp =arr[j];
				arr[j] = arr[j+1];
				arr[j+1]=temp;
			}
		}	
	}
}

//希尔排序
void shellSort(int arr[],int len)
{
	int temp,gap = len/2;
	while(gap>0)
	{
		for(int i =gap;i<len;i++)
		{
			temp = arr[i];
			int index = i-gap;
			while(index>=0 && arr[index]>temp)
			{
				arr[index + gap] = arr[index];
				index -= gap;
			}
			arr[index+gap] = temp;
		}
		gap/=2;
	}
}


//快速排序


//从数列中挑出一个元素，称为 "基准"（pivot）;

//重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；

//递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序；

int* quickSort(int arr[],int start,int last)
{
	int i = start;
	int j = last;
	int temp = arr[i];
	if(i < j)
	{
		while(i < j)
		{
			while (i < j && arr[j] >= temp)
			{
				j--;
			}
			if(i< j)
			{
				arr[i] = arr[j];
				i++;
			}

			while(i < j && arr[i] < temp)
			{
				i++;
			}
			if(i<j)
			{
				arr[j] = arr[i];
				j--;
			}

		}
		arr[i] = temp;

		quickSort(arr,start,i-1);
		quickSort(arr,i+1,last);
		
	}
	return arr;
}




int _tmain(int argc, _TCHAR* argv[])
{
	int ret[]={10,2,3,6,19,23,44,21,11,4};
	int lenth = sizeof(ret)/sizeof(int);
	//bubbleSort(ret,lenth);
	selectSort(ret,lenth);
	//insertSort(ret,&lenth);
	//shellSort(ret,&lenth);
	
	//int *t = quickSort(ret,0,9);





	for (int n = 0;n <lenth;n++)
	{
		printf("%d ",ret[n]);
	}

	getchar();
	return 0;
}

