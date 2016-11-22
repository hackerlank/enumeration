// uva-10391-compound words.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

const int MAXSIZE = 120002;
int num, head[MAXSIZE], next[MAXSIZE];
char a[120002][50];
int Hash(char *str) // BKDR�ַ�����ϣ����
{
    int seed = 131, sum = 0;
    while(*str)
        sum = sum * seed + (*str++);
    return (sum & 0x7FFFFFFF) % MAXSIZE;
}
void insert(int s) // �����е��ʲ����ϣ��
{
    int h = Hash(a[s]);
    next[s] = head[h];
    head[h] = s;
}
int find(char *s) // ���ҵ���
{
    int h = Hash(s);
    int u = head[h];//��һ������
    while(u)
    {
        if(!strcmp(a[u], s))
            return 1;
        u = next[u];
    }
    return 0;
}
int main()
{
    int num = 1, len;
    char str1[50], str2[50];
    while(scanf("%s", a[num++]) != EOF)
        insert(num-1);
    for(int i=1; i<=num; i++)
    {
        len = strlen(a[i]);
        for(int j=1; j<len; j++)//�ֽ�Ϊj:len-j�����Ӵ�
        {
            for(int k=0; k<j; k++)
                str1[k] = a[i][k];
            str1[j] = 0;
            strcpy(str2, &a[i][j]);
            if(find(str1) && find(str2))
            {
                printf("%s\n", a[i]);
                break;
            }
        }
    }
    return 0;
}

