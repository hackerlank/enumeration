// hdu-1381-hashx.cpp : �������̨Ӧ�ó������ڵ㡣
//��nc���Ƶ�����ʾ�ַ�����ö�ٳ���Ϊn���Ӵ�����ֵ���ظ���ȥ��

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define N 16000007  
int hashx[8000000],assi[27],n,nc;  
char str[N];  
int a[N],len; 
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int t,i,j,sum,k;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&nc);
		getchar();
		scanf("%s",str);
		len = strlen(str);
		k = 0;
		for(i = 0; i < len; i++)  //ת��Ϊ����
        {  
            a[i] = str[i] - 'a';  
        }
		i = 0;
		while(str[i]!='\0')  //��ÿ������  ת��Ϊnc���Ƶ�����
        {  
            if(assi[a[i]]==0)  
                assi[a[i]]=k++;  
            if(k==nc)  
                break;  
            i++;  
        } 
		int cnt=len-n+1;//n�����Ӵ�����
		for(i=0;i<len-n+1;i++)  //ÿ���Ӵ�
        {  
            sum=0;  
            for(j=i;j<i+n;j++)  //����ֵ
            {  
                sum=sum*nc+assi[a[j]];  
            }  
            sum%=N;  
            if(hashx[sum]==0)  
                hashx[sum]=1;  
            else  //�������ظ���  ȥ��
                cnt--;  
        }  
        printf("%d\n",cnt);  
        if(t>0)  
            printf("\n");
	}
}

