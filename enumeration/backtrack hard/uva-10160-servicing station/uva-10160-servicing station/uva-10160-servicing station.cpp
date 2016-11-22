/*
1�����ڽӱ�����ڽӾ�������Ź�ϵ�����Լ���һ������������
2��ÿ���ҵ�һ�����÷����������¸��������֮�����������и�����������������Ϳ���ֱ�ӽ������������
3�����һ�����Ѿ��������ˡ����Ҹõ�û�����ǵ��� ����֮��ĵ�û�����ӵ��ĵ㣬��ô�õ���Զ���ᱻ���ǵ����Ϳ���ֱ�ӽ���������������
��һ���Ҫע����ǡ���Ǹ��ǲ����õ�����0,1����ǡ���Ϊһ�����ǿ����ظ����ǵġ����õ���vis[] ++, vis[]--�ķ�������ǵ�
*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int n, m;
int x, y;
int snum[40];//����
int map[40][40];
int f[40];
int minn;

bool cmp(int a, int b)
{
    return a > b;
}

void dfs(int star, int num, int tnum)//star��ǰ���ǵĳ��� //num �Ѿ����ǹ��ĵ� //tnum ���÷������Ŀ
{
    if (tnum >= minn)
		return;
    if (num == n)
    {
		minn = tnum;
		return;
    }
    if (star > n)
		return;
    for (int i = 1; i < star; i ++)//���Ѿ����ǹ��ĳ��� ����δ�������������ڽӳ����Ѿ������� ��star��û������������i�ڽ� ����֮�󲻿����ٱ����� ���ط�֧
		if (!f[i] && map[i][0] < star)
			return;
    int jia = 0;
	//���Ƿ���star�����÷�����֧
    for (int i = 0; i < snum[star]; i ++)//����star���ڽӳ���
    {
		if (f[map[star][i]] == 0)//�ҵ�δ���ǹ����ڽӵ�
			jia ++;
		f[map[star][i]] ++;//��һ�㸲��
    }
    if (jia)//�����ҵ��ĸ��ǵ�
		dfs(star + 1, num + jia, tnum + 1);
    for (int i = 0; i < snum[star]; i ++)
    {
		f[map[star][i]] --;
    }
    dfs(star + 1, num, tnum);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    while (scanf("%d%d", &n, &m) != EOF && n + m)
    {
		minn = n;
		memset(snum, 0, sizeof(snum));
		memset(map, 0, sizeof(map));
		memset(f, 0, sizeof(f));
		for (int i = 0; i < m; i ++)
		{
			scanf("%d%d", &x, &y);
			map[x][snum[x] ++] = y;
			map[y][snum[y] ++] = x;
		}
		for (int i = 1; i <= n; i++) 
		{
			map[i][snum[i] ++] = i;//�����Լ����Լ��ĸ���
			sort(map[i], map[i] + snum[i], cmp);//�ڽӵ��ĳ��н�������
		}
		dfs(1, 0, 0);
		printf("%d\n", minn);
    }
    return 0;
}