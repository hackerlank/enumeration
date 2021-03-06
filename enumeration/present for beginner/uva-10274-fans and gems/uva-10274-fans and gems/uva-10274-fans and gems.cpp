// uva-10274-fans and gems.cpp : 定义控制台应用程序的入口点。
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
typedef char State[13][21];  
State map;  
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};  
char dir_name[] = {'D', 'L', 'R', 'U'};  
int N,M; 
inline void swap(char &ch1, char &ch2){ char t=ch1; ch1=ch2; ch2=t; }
inline bool is_gem_fly(char ch){  
    if(ch=='1'||ch=='2'||ch=='3'||ch=='@') return true;  
    return false;  
}
inline bool move(State &s, int dir){  
    bool flag=false;  
    if(dir==0){ // 下  
        for(int i=1; i<M-1; ++i){  
            for(int j=N-1; j>0; --j)if(s[j][i]==' '){  
                int k = j-1;  
                while(s[k][i]==' ') --k;  
                if(is_gem_fly(s[k][i])){  
                    swap(s[j][i], s[k][i]); flag=true;  
                }  
                else
                    j=k;  
            }  
        }  
    }  
    else if(dir==1){ // 左  
        for(int i=1; i<N-1; ++i){  
            for(int j=1; j<M-1; ++j)if(s[i][j]==' '){  
                int k = j+1;  
                while(s[i][k]==' ') ++k;  
                if(is_gem_fly(s[i][k])){  
                    swap(s[i][j], s[i][k]); flag=true;  
                }  
                else
                    j=k;  
            }  
        }  
    }  
    else if(dir==2){ // 右  
        for(int i=1; i<N-1; ++i){  
            for(int j=M-1; j>1; --j)if(s[i][j]==' '){  
                int k = j-1;  
                while(s[i][k]==' ') --k;  
                if(is_gem_fly(s[i][k])){  
                    swap(s[i][j], s[i][k]); flag=true;  
                }  
                else
                    j=k;  
            }  
        }  
    }  
    else if(dir==3){ // 上  
        for(int i=1; i<M-1; ++i){  
            for(int j=1; j<N-1; ++j)if(s[j][i]==' '){  
                int k = j+1;  
                while(s[k][i]==' ')++k;  
                if(is_gem_fly(s[k][i])){  
                    swap(s[j][i], s[k][i]); flag=true;  
                }  
                else
                    j=k;  
            }  
        }  
    }  
    if(flag)return true;  
    return false;  
}

void dfs(State &s, char ch, int x, int y)
{
	s[x][y] = ' ';
	for(int i = 0;i<4;i++)
	{
		int nx = x+dir[i][0];
		int ny = y+dir[i][1];
		if(s[nx][ny]==ch)  
            dfs(s, ch, nx, ny);
	}
}
inline bool remove(State &s){  
    bool ok=false;  
    for(int i=1; i<N-1; ++i){  
        for(int j=1; j<M-1; ++j)if(is_gem_fly(s[i][j]) && s[i][j]!='@'){  
            bool flag=false;  
            for(int k=0; k<4; ++k){  
                int dx=i+dir[k][0], dy=j+dir[k][1];  
                if(dx>=0 && dx<N && dy>=0 && dy<M && s[i][j]==s[dx][dy]){  //相邻有一样的
                    flag=true;   
                    break;  
                }  
            }  
            if(flag){  
                ok = true;   
                dfs(s,s[i][j],i,j);  
            }  
        }  
    }  
    if(ok) return true;  
    return false;  
}
inline void run(State &s, int dir){  // 往哪个方向的步骤  
    while(move(s, dir)){  
        remove(s);  
    }  
}
const int MAXN = 100000;  
const int HashSize = 1000003;  
State que[MAXN];  
int head[HashSize], next[MAXN], father[MAXN], step[MAXN], ans;  
char path[MAXN];
inline void init_lookup_table(){   
    ans = -1;  
    father[0]=0;   
    step[0] = 0;  
    memset(head, 0, sizeof(head));   
    memset(que, 0, sizeof(que));  
}
int hash(State& s)
{
	int seed = 131;
	int v = 0;
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<M;j++)
		{
			v = (v*seed + s[i][j])&0x7FFFFFFF;
		}
	}
	return v%HashSize;
}
bool try_to_insert(int s)
{
	int h = hash(que[s]);
	int u = head[h];
	while(u)
	{
		if(memcmp(que[u],que[s],sizeof(que[s]))==0)
			return 0;
		u = next[u];
	}
	next[s] = head[h];
	head[h] = s;
	return 1;
}
inline bool is_ok(State &s){  
    for(int i=1; i<N-1; ++i){  
        for(int j=1; j<M-1; ++j)  
            if(s[i][j]=='1'||s[i][j]=='2'||s[i][j]=='3')return false;  
    }  
    return true;  
}
int bfs()
{
	init_lookup_table();  
    int front=0, rear=1;  
    memcpy(que[0], map, sizeof(map));  
    try_to_insert(0);
	while(front<rear)
	{
		State &s = que[front];  
        if(step[front] > 18){  
            ++front; continue;  
        }
		if(is_ok(s)){  
            ans = front;  
            return true;  
        }
		for(int i=0; i<4; ++i){  
            State &t = que[rear];  
            memcpy(t, s, sizeof(s));  
            run(t, i);  //选择一个方向运行到底
            if(try_to_insert(rear)){  
                step[rear] = step[front]+1;  
                father[rear] = front;  
                path[rear] = dir_name[i];  
                ++rear;  
            }  
        }  
        ++front;
	}
	return 0;
}
void print_path(int cur){  
    if(cur){  
        print_path(father[cur]);  
        printf("%c", path[cur]);  
    }  
}
int main(){
    int T;
	char str[1000];
	scanf("%d%*c",&T);
	while(T--){
		scanf("%d%d%*c",&N,&M);
		for(int i=0; i<N; ++i)
			gets(map[i]);
		gets(str);
		if(!bfs())
			printf("-1\n");
		else{
			print_path(ans);
			printf("\n");
		}
	}
	return 0;
}

