// uva-11198-dance number.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
struct node
{
	int a[9],time;
}q[40321];
int prime[16]={0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0},visit[40321],
    Exp[11]={0,1,1,2,6,24,120,720,5040},top,tail,f;//7!Ϊ��8λ��ָ��   ������*�׳���Ϊ����ӳ���ֵ

int hash(int team[])
{
	 int I,J,K,S=0;
	 for (I=8;I>=2;I--)//��һλ������Ϊ0  ������
	 {
		  K=0;
		  for (J=1;J<I;J++)
		  if (abs(team[J])>abs(team[I])) ++K;//������
		  S=S+K*Exp[I];
	 }
     return S;
};
int main()
{
	int n=0,i,j,k,team[9],t,temp;
    while (scanf("%d",&q[1].a[1]),q[1].a[1])
    {
		for (i=2;i<=8;i++)
			scanf("%d",&q[1].a[i]);
		memset(visit,0,sizeof(visit));
		visit[hash(q[1].a)]=1;//��ʼ����
		top=1; tail=1; f=0;
		q[1].time=0;

		while ((f==0)&&(top<=tail))  //�Ժ�bfs����д�ɷǵݹ�İ�ȫ��ջ�����ĺܵ��ۣ�����һ������뵽
		{
			if (hash(q[top].a)==0) 
			{
				f=1;break;
			}
			for (i=1;i<=7;i++)//j�Ƿ���Ի���i�Ա�
				for (j=i+1;j<=8;j++)
				{
					if ((q[top].a[i]*q[top].a[j]<0)&&(prime[abs(q[top].a[i])+abs(q[top].a[j])]==1))
					{
						for (k=1;k<=8;k++)   
							team[k]=q[top].a[k];  
						t=team[j];
						for (k=j;k>i;k--)    
							team[k]=team[k-1];    
						temp=team[i+1]; 
						team[i+1]=t;//j����i�ұ�
						if (visit[hash(team)]==0) 
						{
							visit[hash(team)]=1; //״̬���
							++tail; 
							for (k=1;k<=8;k++) 
								q[tail].a[k]=team[k];
							q[tail].time=q[top].time+1;
						}

					team[i+1]=temp;   team[i]=t;//�ŵ����
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}
 
					for (k=1;k<=8;k++)   
						team[k]=q[top].a[k];  
					t=team[i];
					for (k=i;k<j;k++)    
						team[k]=team[k+1];    
					temp=team[j-1]; 
					team[j-1]=t;  //i����j�����
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}

					team[j-1]=temp;   team[j]=t;  //i����j�ұ�
					if (visit[hash(team)]==0) 
					{
						visit[hash(team)]=1; 
						++tail; 
						for (k=1;k<=8;k++) 
							q[tail].a[k]=team[k];
						q[tail].time=q[top].time+1;
					}
				}
			}
			++top;
		}
		printf("Case %d: ",++n);
		if (f)  printf("%d\n",q[top].time);
		else   printf("-1\n");
	}
 return 0;
}



