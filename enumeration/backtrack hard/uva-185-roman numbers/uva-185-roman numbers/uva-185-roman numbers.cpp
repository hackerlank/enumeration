// uva-185-roman numbers.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
char str[30];
char tstr[30];
char roman1[10];
char roman2[10];
char roman3[10];
int used[10];
int value[27];
char pre_zero[2];//��¼��������ȡ0������ĸ
int translate(char* s)
{
	int len = strlen(s);
	int sum = 0;
	for(int i = 0;i<len-1;i++)
	{
		if(value[s[i]-'A']<value[s[i+1]-'A'])
		{
			sum-=value[s[i]-'A'];
		}
		else
			sum+=value[s[i]-'A'];
	}
	sum+=value[s[len-1]-'A'];
	return sum;
}

int judge_roman()
{
	int a = translate(roman1);
	int b = translate(roman2);
	int c = translate(roman3);
	if(a+b==c)
		return 1;
	return 0;
}
int y[27];//��ǰ·��ö�������ĸ�����ĸ�����ֵ
int sum_len;
int cnt;//�ϸ���Ŀ
int num1,num2,num3;

int get_weishu(int a)
{
	int sum = 0;
	if(a)
	{
		a/=10;
		sum++;
	}
	return sum;
}

void dfs(int cur)
{
	if(cnt>=2)
		return;
	if(sum_len==cur)
	{
		if(num1+num2==num3)
		{
			cnt++;
		}
		return;
	}
	int temp = 0;
	if(cur==0)//��һ����ĸ
	{
		for(int i = 1;i<=9;i++)
		{
			num1 = i;
			used[i] = 1;
			temp = y[tstr[cur]-'A'];
			y[tstr[cur]-'A'] = i;
			dfs(cur+1);
			y[tstr[cur]-'A'] = temp;
			used[i] = 0;
		}
	}
	else if(cur==strlen(roman1))//�ڶ�������һ����ĸ
	{
		if(y[tstr[cur]-'A']>-1)//֮ǰ�õ���ֵ
		{
			num2 = y[tstr[cur]-'A'];
			if(num2==0)
				return;//����ǰ��0
			dfs(cur+1);
		}
		else
		{
			for(int i = 1;i<10;i++)
			{
				if(used[i]==0)//δ��ʹ�ù�
				{
					num2 = i;
					used[i] = 1;
					temp = y[tstr[cur]-'A'];
					y[tstr[cur]-'A'] = i;
					dfs(cur+1);
					y[tstr[cur]-'A'] = temp;
					used[i] = 0;
				}
			}
		}
	}
	else if(cur==strlen(roman1)+strlen(roman2))//����������һ����ĸ
	{
		int t = num1+num2;
		int x = get_weishu(t);//�õ�ǰ2�����ӵ�λ��
		if(x>strlen(roman3))//�������λ��
			return;
		if(y[tstr[cur]-'A']>-1)//֮ǰ�õ���ֵ
		{
			num3 = y[tstr[cur]-'A'];
			if(num3==0)
				return;//����ǰ��0
			dfs(cur+1);
		}
		else
		{
			for(int i = 1;i<10;i++)
			{
				if(used[i]==0)//δ��ʹ�ù�
				{
					num3 = i;
					used[i] = 1;
					temp = y[tstr[cur]-'A'];
					y[tstr[cur]-'A'] = i;
					dfs(cur+1);
					y[tstr[cur]-'A'] = temp;
					used[i] = 0;
				}
			}
		}
	}
	else if(cur>0&&cur<strlen(roman1))//��һ����
	{
		if(y[tstr[cur]-'A']>-1)//֮ǰ�õ���ֵ
		{
			num1*=10;
			num1+=y[tstr[cur]-'A'];
			dfs(cur+1);
			num1-=y[tstr[cur]-'A'];
			num1/=10;
		}
		else
		{
			for(int i = 0;i<10;i++)
			{
				if(used[i]==0)//δ��ʹ�ù�
				{
					num1 *= 10;
					num1 += i;
					used[i] = 1;
					temp = y[tstr[cur]-'A'];
					y[tstr[cur]-'A'] = i;
					dfs(cur+1);
					y[tstr[cur]-'A'] = temp;
					num1-=i;
					num1/=10;
					used[i] = 0;
				}
			}
		}
	}
	else if(cur>strlen(roman1)&&cur<strlen(roman1)+strlen(roman2))//�ڶ�����
	{
		if(y[tstr[cur]-'A']>-1)//֮ǰ�õ���ֵ
		{
			num2*=10;
			num2+=y[tstr[cur]-'A'];
			dfs(cur+1);
			num2-=y[tstr[cur]-'A'];
			num2/=10;
		}
		else
		{
			for(int i = 0;i<10;i++)
			{
				if(used[i]==0)//δ��ʹ�ù�
				{
					num2 *= 10;
					num2 += i;
					used[i] = 1;
					temp = y[tstr[cur]-'A'];
					y[tstr[cur]-'A'] = i;
					dfs(cur+1);
					y[tstr[cur]-'A'] = temp;
					num2-=i;
					num2/=10;
					used[i] = 0;
				}
			}
		}
	}
	else if(cur>strlen(roman1)+strlen(roman2))//��������
	{
		if(y[tstr[cur]-'A']>-1)//֮ǰ�õ���ֵ
		{
			num3*=10;
			num3+=y[tstr[cur]-'A'];
			dfs(cur+1);
			num3-=y[tstr[cur]-'A'];
			num3/=10;
		}
		else
		{
			for(int i = 0;i<10;i++)
			{
				if(used[i]==0)//δ��ʹ�ù�
				{
					num3 *= 10;
					num3 += i;
					used[i] = 1;
					temp = y[tstr[cur]-'A'];
					y[tstr[cur]-'A'] = i;
					dfs(cur+1);
					y[tstr[cur]-'A'] = temp;
					num3-=i;
					num3/=10;
					used[i] = 0;
				}
			}
		}
	}
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(value,0,sizeof(value));
	memset(used,0,sizeof(used));
	value['I'-'A'] = 1;
	value['V'-'A'] = 5;
	value['X'-'A'] = 10;
	value['L'-'A'] = 50;
	value['C'-'A'] = 100;
	value['D'-'A'] = 500;
	value['M'-'A'] = 1000;
	while(gets(str))
	{
		if(str[0]=='#')
			break;
		int len = strlen(str);
		int i = 0;
		int j = 0;
		for(;i<len;i++)
		{
			if(str[i]!='+')
			{
				roman1[j++] = str[i];
			}
			else
				break;
		}
		i++;
		roman1[j++] = '\0';
		j = 0;
		for(;i<len;i++)
		{
			if(str[i]!='=')
			{
				roman2[j++] = str[i];
			}
			else
				break;
		}
		i++;
		roman2[j++] = '\0';
		j = 0;
		for(;i<len;i++)
		{
			roman3[j++] = str[i];
		}
		roman3[j++] = '\0';
		int res = judge_roman();
		if(res)
			printf("Correct ");
		else
			printf("Incorrect ");
		pre_zero[0] = roman1[0];
		pre_zero[1] = roman2[0];
		sum_len = len-2;
		num1 = num2 = num3 = 0;
		for(i = 0,j = 0;i<len;i++)
		{
			if(str[i]!='+'&&str[i]!='=')
				tstr[j++] = str[i];
		}
		for(i = 0;i<27;i++)
			y[i] = -1;
		cnt = 0;
		dfs(0);
		if(cnt==0)
			printf("impossible\n");
		else if(cnt==1)
			printf("valid\n");
		else
			printf("ambiguous\n");
	}
	return 0;
}

