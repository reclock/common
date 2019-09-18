// pai_xu.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <regex>
#include <iostream>
using namespace std;

//ð������

//�Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
//��ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԡ��ⲽ���������Ԫ�ػ�����������
//������е�Ԫ���ظ����ϵĲ��裬�������һ����
//����ÿ�ζ�Խ��Խ�ٵ�Ԫ���ظ�����Ĳ��裬ֱ��û���κ�һ��������Ҫ�Ƚ�
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
//ѡ������

//  ������δ�����������ҵ���С����Ԫ�أ���ŵ��������е���ʼλ�á�
//	�ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�Ȼ��ŵ����������е�ĩβ��
//	�ظ��ڶ�����ֱ������Ԫ�ؾ�������ϡ�
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
//��������

//����һ���������е�һ��Ԫ�ؿ���һ���������У��ѵڶ���Ԫ�ص����һ��Ԫ�ص�����δ�������С�
//��ͷ��β����ɨ��δ�������У���ɨ�赽��ÿ��Ԫ�ز����������е��ʵ�λ�á�
//������������Ԫ�������������е�ĳ��Ԫ����ȣ��򽫴�����Ԫ�ز��뵽���Ԫ�صĺ��档��
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

//ϣ������
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


//��������


//������������һ��Ԫ�أ���Ϊ "��׼"��pivot��;

//�����������У�����Ԫ�رȻ�׼ֵС�İڷ��ڻ�׼ǰ�棬����Ԫ�رȻ�׼ֵ��İ��ڻ�׼�ĺ��棨��ͬ�������Ե���һ�ߣ�������������˳�֮�󣬸û�׼�ʹ������е��м�λ�á������Ϊ������partition��������

//�ݹ�أ�recursive����С�ڻ�׼ֵԪ�ص������кʹ��ڻ�׼ֵԪ�ص�����������

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

