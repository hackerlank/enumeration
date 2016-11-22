// uva-322-ships.cpp : �������̨Ӧ�ó������ڵ㡣
//

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
int h,w;
char s[20][20];
int a[20][20];//0 δ�ж� 1 ���� -1 û�� 
int b[20][20];//0 δ�ж� 1 ���� -1 û�� 
int used[20][20];//7 pieces
int zero[256];
int num_one;//�Ѿ�ȷ���д��ķ�����
int num_zero;//δȷ���ķ�����
int num_piece;
int num_avail;//��ǰ������ת״̬�µĿ��н���Ŀ
int res_avail;//�ܹ��Ŀ��н���Ŀ
int pos_in;
int pos[256];
int pre_pos[256];//ֻ����ౣ��1����δ�����  pos��pre_pos��ͬ˵��������н�
int i1,i2,i3,i4,i5,i6,i7;
typedef struct Po
{
	int x;
	int y;
} P;
P parr[7];
int piece[7][4][4][2] = 
{
	{
		{{0,0},{0,1},{1,1},{1,0}}
	},
	{
		{{0,0},{0,1},{0,2},{0,3}},
		{{0,0},{1,0},{2,0},{3,0}}
	},
	{
		{{0,0},{1,0},{0,1},{1,-1}},
		{{0,0},{1,0},{1,1},{2,1}}
	},
	{
		{{0,0},{0,1},{1,1},{1,2}},
		{{0,0},{1,0},{1,-1},{2,-1}}
	},
	{
		{{0,0},{1,0},{1,1},{1,2}},
		{{0,0},{1,0},{2,0},{2,-1}},
		{{0,0},{0,1},{0,2},{1,2}},
		{{0,0},{0,1},{1,0},{2,0}}
	},
	{
		{{0,0},{1,0},{1,-1},{1,-2}},
		{{0,0},{0,1},{1,1},{2,1}},
		{{0,0},{0,1},{0,2},{1,0}},
		{{0,0},{1,0},{2,0},{2,1}}
	},
	{
		{{0,0},{1,0},{1,-1},{1,1}},
		{{0,0},{1,0},{2,0},{1,-1}},
		{{0,0},{0,1},{0,2},{1,1}},
		{{0,0},{1,0},{2,0},{1,1}}
	}
};
int ok(int x, int y)
{
	if(x>=0&&x<h&&y>=0&&y<w)
		return 1;
	return 0;
}
int ok_piece(int x, int y,int angle, int id)
{
	//��id��piece�ĵ�angle����תͼ��  ��0,0��ʼ��һ�ҵ���Ϊx,y���Ƿ�����
	for(int i = 0;i<4;i++)
	{
		int nx = x+piece[id-1][angle][i][0];
		int ny = y+piece[id-1][angle][i][1];
		if(!ok(nx,ny))
			return 0;
		if(b[nx][ny]!=1)
			return 0;
	}
	return 1;
}
void change_piece(int x, int y, int angle, int id, int v)
{
	for(int i = 0;i<4;i++)
	{
		int nx = x+piece[id-1][angle][i][0];
		int ny = y+piece[id-1][angle][i][1];
		b[nx][ny] = v;
		if(v==-1)
		{
			if(used[nx][ny]==1)//ԭ����1
				num_one--;//����һ��1
		}
		else
		{
			if(used[nx][ny]==1)//ԭ����1
				num_one++;//��ԭһ��1
		}
	}
}
int same()//�жϵ�ǰ��δʹ�õ���Щ0������֮ǰ��ĳ�����н��Ӧ��0�����Ƿ�һ��
{
	if(pre_pos[0]!=pos[0])
		return 0;
	if(pos[0]==0)
		return 0;
	for(int i = 1;i<=pos[0];i++)
		if(pos[i]!=pre_pos[i])
			return 0;
	return 1;
}
int check()//1 ��ǰ����Ա�����  0 ��ǰ������һ�����н�
{
	//���㵱ǰ�Ŀ��н���b��Ϊ1�ĵ� ��û��ʹ�ù��ĵ�
	int k = 1;
	if(pos_in==0)
	{
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(b[i][j]==1)
				{
					int in = i*w+j;
					pre_pos[k++] = in;
				}
			}
		}
		if(k>1)
		{
			sort(pre_pos+1,pre_pos+k-1);
		}
		pre_pos[0] = k-1;//����
		pos_in++;
		num_avail++;
		return 1;
	}
	else
	{
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(b[i][j]==1)
				{
					int in = i*w+j;
					pos[k++] = in;
				}
			}
		}
		if(k>1)
		{
			sort(pos,pos+k-1);
		}
		pos[0] = k-1;
		if(same())//��һ����  Ӧ����һ���  ������ǰ��
			return 1;
		num_avail++;
		return 0;
	}
}
int flag;
void dfs(int id)//��ǰÿ����״�Ѿ��̶�
{
	if(id==8)
	{
		if(num_one==0)//ԭ����1ȫ������
		{
			if(check())
			{
				return;
			}
			else
			{
				if(num_avail>1)
				{
					flag = 0;//�õ�������н�  ����
					return;
				}
			}
		}
	}
	else
	{
		int angle;
		switch(id)
		{
		case 1:
			angle = i1;
			break;
		case 2:
			angle = i2;
			break;
		case 3:
			angle = i3;
			break;
		case 4:
			angle = i4;
			break;
		case 5:
			angle = i5;
			break;
		case 6:
			angle = i6;
			break;
		case 7:
			angle = i7;
			break;
		}
		for(int i = 0;i<h&&flag;i++)
		{
			for(int j = 0;j<w&&flag;j++)
			{
				if(ok_piece(i,j,angle,id))
				{
					change_piece(i,j,angle,id,-1);
					parr[id-1].x = i;
					parr[id-1].y = j;
					dfs(id+1);
					change_piece(i,j,angle,id,1);
				}
			}
		}	
	}
	return;
}

//�жϵ�ǰ������1�γɵ�ͼ���Ƿ���7��piece  �ǵĻ��м�����з���
int getpiece()//
{
	int sum = 0;//���н���Ŀ
	
	for(i1 = 0;i1<1;i1++)//����  һ��
	{
		if(h==1||w==1)
			continue;
		for(i2 = 0;i2<2;i2++)//����  ����
		{
			if(i2==0&&w<4)
				continue;
			if(i2==1&&h<4)
				continue;
			for(i3 = 0;i3<2;i3++)//����
			{
				if(i3==0&&w<3)
				continue;
				if(i3==1&&h<3)
					continue;
				for(i4 = 0;i4<2;i4++)//����
				{
					if(i4==0&&w<3)
						continue;
					if(i4==1&&h<3)
						continue;
					for(i5 = 0;i5<4;i5++)//����
					{
						if((i5==0||i5==2)&&w<3)
							continue;
						if((i5==1||i5==3)&&h<3)
							continue;
						for(i6 = 0;i6<4;i6++)//����
						{
							if((i6==0||i6==2)&&w<3)
								continue;
							if((i6==1||i6==3)&&h<3)
								continue;
							for(i7 = 0;i7<4;i7++)//����
							{
								if((i7==0||i7==2)&&w<3)
									continue;
								if((i7==1||i7==3)&&h<3)
									continue;
								//ȷ��ÿ����״��ǰ��ת״̬
								//����ǰ�����Ƿ��д���ת״̬�Ŀ��н�
								num_avail = 0;//��ǰ��״���н���Ŀ
								flag = 1;
								dfs(1);
								sum+=num_avail;
								if(sum>1)
									return sum;//�Ѿ��ҵ�������н�  ���ü�������
							}
						}
					}
				}
			}
		}
	}
	return sum;
}
//res_avail��ʾ��ǰĳ��0��ָ��Ϊmiss -1��ʱ��һ�����ڵĿ��н���Ŀ  ��res_avail=1������yes
void get_avail()
{
	memcpy(b,a,sizeof(a));
	pos_in = 0;
	memset(pos,0,sizeof(pos));
	memset(pre_pos,0,sizeof(pre_pos));
	for(int i = 0;i<h;i++)
	{
		for(int j = 0;j<w;j++)
		{
			if(b[i][j]==0)//ѡȡ0��תΪ1����ǰ��״̬�¿��н���Ŀ
			{
				b[i][j] = 1;
			}
		}
	}
	res_avail=getpiece();//�õ���ǰ��ת״̬�Ŀ��н���Ŀ
}
//��ĳ��0��Ϊmiss -1  ������ĳ��missʹ��res_avail = 1��Ϊyes ������miss��ʹ��res_avail��Ϊ1 ��Ϊno
int miss()
{
	for(int i = 0;i<h;i++)
	{
		for(int j = 0;j<w;j++)
		{
			if(a[i][j]==0)
			{
				a[i][j] = -1;//miss
				res_avail = 0;
				get_avail();
				if(res_avail==1)
					return 1;
				a[i][j] = 0;
			}
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int ncase = 1;
	while(scanf("%d%d",&w,&h))
	{
		if(w==0&&h==0)
			break;
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));
		memset(used,0,sizeof(used));
		memset(zero,0,sizeof(zero));
		getchar();
		for(int i = 0;i<h;i++)
		{
			gets(s[i]);
		}
		//if(ncase>1)
			//printf("\n");
		printf("Game #%d\n",ncase++);
		num_one = 0;
		num_zero = 0;
		for(int i = 0;i<h;i++)
		{
			for(int j = 0;j<w;j++)
			{
				if(s[i][j]=='.')
				{
					a[i][j] = 0;//Ϊ0  ˵��δ֪
					zero[num_zero++] = i*w+j;
				}
				else if(s[i][j]=='o')
					a[i][j] = -1;//ȷ��û��
				else
				{
					a[i][j] = 1;//ȷ���д�
					used[i][j] = 1;
					num_one++;
				}
			}
		}
		if(num_one+num_zero<=28)
		{
			printf("yes.\n");
		}
		else if(num_one==28)//�жϵ�ǰ�Ƿ��Ѿ����ɿ��н�
		{
			for(int i = 0;i<h;i++)
			   for(int j = 0;j<w;j++)
					if(a[i][j]==0)
						a[i][j] = -1;
			get_avail();
			if(getpiece())
			{
				printf("yes.\n");
			}
			else
			{
				printf("no.\n");
			}
		}
		else if(num_one+num_zero==28)
		{
			for(int i = 0;i<h;i++)
			   for(int j = 0;j<w;j++)
					if(a[i][j]==0)
						a[i][j] = 1;
			get_avail();
			if(getpiece())
			{
				printf("yes.\n");
			}
			else
			{
				printf("no.\n");
			}
		}
		else
		{
			int res = miss();
			if(res)
				printf("yes.\n");
			else
				printf("no.\n");
		}
		printf("\n");
		getchar();
	}
	return 0;
}

