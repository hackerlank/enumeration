// uva-10001-eden's garden.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
// Garden of Eden ������԰��
// PC/UVa IDs: 110806/10001, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-08-11
// UVa Run Time: 0.660s
//
// ��Ȩ���У�C��2011�����metaphysis # yeah dot net
//
// �����ʹ�û��ݷ�Ѱ�Ҹ���״̬��ǰ���������ҵ�ǰ������Ϊ�ɴ���޷��ҵ�ǰ������Ϊ����԰״̬��
// identifier ��Ӧ�Ĺ��� ��0-255  ������ֻ��8λ ÿλ��Ӧ000-111

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define CODESIZE 8

bool finished;
bool is_garden;

// ���ݵ�ǰϸ������������ϸ����״̬��ö�Ӧ�ı任�����뼴����������
int indexer(int a, int b, int c)//000-111�е�ĳ��ֵ
{
	return (a << 2) + (b << 1) + c;
}

void evolution(vector <int> &a, vector <int> &b, int automaton[])//a->b
{
	int last = a.size() - 1;

	b[0] = automaton[indexer(a[last], a[0], a[1])];
	for (int i = 1; i < last; i++)
		b[i] = automaton[indexer(a[i - 1], a[i], a[i + 1])];
	b[last] = automaton[indexer(a[last - 1], a[last], a[0])];
}

// �Ƚ�����״̬�Ƿ���ͬ��
bool equal(vector <int> &a, vector <int> &b)
{
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

// ����Ѱ��ǰ����
void backtrack(vector <int> &ancestor, vector <int> &target,
        int automaton[], int current)//0--current+1�Ѿ��ֽ�����  ��ǰ��ʼ�ж�cur+2λ
{
	if (current == (ancestor.size() - 2))
	{
		vector <int> now(ancestor.size());
		
		evolution(ancestor, now, automaton);
		
		if (equal(now, target))
		{
			finished = true;
			is_garden = false;
		}
	}
	else
	{
		for (int i = 0; i <= 1; i++)//������һ�ָ���tar[cur]�����ans[cur]��ans[cur+1]����ʱ����tar[cur+1]ֻ���ans[cur+2]����0,1���ַ�֧չ��
		{
			int index = indexer(ancestor[current], ancestor[current + 1], i);//��0 1��ǰ2��ֵ�õ�������
			if (automaton[index] == target[current + 1])
			{
				ancestor[current + 2] = i;
				backtrack(ancestor, target, automaton, current + 1);
			
				if (finished)
					return;
			}
		}
	}
}

// �ж��Ƿ���ǰ�����ڡ�
bool no_ancestor(vector <int> &target, int automaton[])
{
	int cells = target.size();
	vector <int> ancestor(cells);

	for (int i = 0; i < CODESIZE; i++)
		if (automaton[i] == target[0])//ĳ�����������ĳλ״̬
		{	
			ancestor[cells - 1] = ((i & 4) >> 2);//�ı��Ӧλ��״̬ iΪ0-111��ĳ��ֵ ��i�ֽ������������ֵ
			ancestor[0] = ((i & 2) >> 1);
			ancestor[1] = (i & 1);
			
			finished = false;
			is_garden = true;

			backtrack(ancestor, target, automaton, 0);

			if (is_garden == false)
				return false;
		}

	return true;
}

// �ж������������Ƿ�Ϊ����԰״̬��
bool is_garden_of_eden(int identifier, int cells, string state)
{
	// �ж�һЩ�����ϸ���Զ�����
	if (identifier == 204)//���򣺵����Լ�
		return false;
	
	// ���Զ������Ϊ 0 ʱ���з� 0 ����Ϊ����԰��
	if (identifier == 0)//���� ����ֵ��ȡ0
	{
		for (int i = 0; i < state.length(); i++)
			if (state[i] != '0')
				return true;
		return false;
	}
	
	// ���Զ������Ϊ 255 ʱ���з� 1 ����Ϊ����԰��
	if (identifier == 255)//��������ֵȡ1
	{
		for (int i = 0; i < state.length(); i++)
			if (state[i] != '1')
				return true;
		return false;
	}
	
	// ��ȡ���״̬���Զ�����Ӧ�ı���任����
	vector <int> ancestor(cells);
	for (int i = 0; i < cells; i++)
		ancestor[i] = (state[i] - '0');
		
	int automaton[CODESIZE];
	for (int i = 0; i < CODESIZE; i++)//ȡ8λ������ ÿλ��Ӧ000-111��ĳ��ֵ
	{
		automaton[i] = identifier % 2;
		identifier /= 2;
	}
	
	return no_ancestor(ancestor, automaton);
}

int main(int ac, char *av[])
{
	int identifier, cells;
	string state;

	// �������ݡ�
	while (cin >> identifier >> cells >> state)
	{
		bool result = is_garden_of_eden(identifier, cells, state);
		cout << (result ? "GARDEN OF EDEN" : "REACHABLE") << endl;
	}

	return 0;
}

