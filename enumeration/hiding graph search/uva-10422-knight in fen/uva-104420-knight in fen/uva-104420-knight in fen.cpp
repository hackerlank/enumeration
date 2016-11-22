// uva-104420-knight in fen.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
int a[5][5],move[8][2]={{-1,-2},{-1,2},{-2,1},{-2,-1},{2,1},{2,-1},{1,-2},{1,2}},
    b[5][5]={{1,1,1,1,1},{0,1,1,1,1},{0,0,2,1,1},{0,0,0,0,1},{0,0,0,0,0}},min;
int dfs(int x,int y,int step,int way)//way  �������ķ���
{
	int i,j,X,Y,sum=0,t;
	if (step>=min) return 0;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			if (a[i][j]!=b[i][j]) ++sum;
	if (sum==0) //�ﵽĿ��״̬
	{
		if (step<min) 
			min=step; 
		return 0;
	}
	if ((sum+1)/2+step>=min) 
		return 0; //SUM��ʾ��Ŀ��״̬��ͬ��λ�ø�������������Ҫ(�ƶ�һ�����2��λ����Ŀ��״̬��ͬ��sum/2+sum%2=��sum+1��/2�����ܱ�ΪĿ��״̬
	for (i=0;i<8;i++)
	{
		X=x+move[i][0];
		Y=y+move[i][1];
		if ((X>=0)&&(X<5)&&(Y>=0)&&(Y<5)&&(way+i!=7)) //��ʼ��moveʱ���෴�������±��Ϊ7�������Ϳ���ÿ�α����߻�ͷ·ʡ�����ع���
		{//way+i��Ϊ7��i����ʱ���򲻷�  ���Ƿ��ص�����
			t=a[x][y];a[x][y]=a[X][Y];a[X][Y]=t;
			dfs(X,Y,step+1,i);
			t=a[x][y];a[x][y]=a[X][Y];a[X][Y]=t;
		}
	}
}
int main()
{int i,j,x,y,n;
 char s[6];
 scanf("%d\n",&n);
 while (n--)
 {
  for (i=0;i<5;i++)
  {gets(s);
   for (j=0;s[j]!='\0';j++)
   if (s[j]==' ') {a[i][j]=2;x=i;y=j;}
             else a[i][j]=s[j]-'0';
  }
  min=11;//����11��
  dfs(x,y,0,8);//way = 8  ���������෴��  Ϊ��ʼ��
  if (min==11) printf("Unsolvable in less than 11 move(s).\n");
  else printf("Solvable in %d move(s).\n",min);
 }
 return 0;
}

