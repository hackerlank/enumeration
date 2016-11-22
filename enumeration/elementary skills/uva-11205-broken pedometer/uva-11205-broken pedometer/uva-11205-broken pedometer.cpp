// uva-11205-broken pedometer.cpp : �������̨Ӧ�ó������ڵ㡣
//�������ֲ�ͬ�е���С����

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>
using namespace std;

char b[101][17];
int a[101][17], flag[17], _min;

int subset(int n, int p, int cur)
{
    if(cur == p)
    {
        int ct = 0;
        for(int i = 0; i < p; i++)
            if(flag[i])//ĳһ�б���ʾ
            {
                for(int j = 0; j < n; j++)//�������� ȡ���ñ�ʾ��
                    b[j][ct] = a[j][i] + '0';
                ++ct;
            }
        for(int i = 0; i < n; i++)
            b[i][ct] = 0;
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++) // �����Ӽ�Ӧ������ͬ�ſ�����
                if(!strcmp(b[i], b[j]))
                    return 0;
        if(_min > ct)
            _min = ct;
        return 1;
    }
    flag[cur] = 0;
    subset(n, p, cur + 1);
    flag[cur] = 1;
    subset(n, p, cur + 1);
    return 0;
}
int main()
{
    int t, p, n, ct;
    scanf("%d", &t);
    while(t--)
    {
        memset(flag, 0, sizeof(flag));
        scanf("%d%d", &p, &n);
        getchar();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < p; j++)
                scanf("%d", &a[i][j]);
        _min = p;
        ct = subset(n, p, 0);
        printf("%d\n", _min);
    }
    return 0;
}

