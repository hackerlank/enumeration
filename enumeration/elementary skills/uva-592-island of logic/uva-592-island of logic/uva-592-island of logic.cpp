/*
    ˼·��ö�����������
    this is impossible. ���������������������
    No facts are deducible. ������������������������֮��û�н�����Ҳ����˵ԭ���������Ƶ����κν�������
    fact�� �������������֮��Ľ�����
*/
#include "stdafx.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char kind[][20] = {"divine", "human", "evil"};
const int MAX_P = 5+5; //�������
int person[MAX_P]; //��¼ABCD��������
char name[MAX_P];  //��¼��Ӧ������(���ǵ�ֻ��������A��C����������B�����)
int name_order[MAX_P]; //��¼A��B��C��D��E�ֱ���ֵ�˳��
int lying[MAX_P];  //0:lying 1:not lying
int time; //0:day, 1:night
int cur_p; //����
struct line //̨��
{
    int who_said; //who said
    int kind;// 0������1��2; 1:����3
    int time; //0:day, 1:night
    int person; //person: 0-4
    int has_not; //not: 0, 1
    int id; //0-3, 3:lying
};
const int MAX_L = 50+5;
line lines[MAX_L];
int cur_l;
//����
int found;
int result[MAX_P];
int r_time;

void dicide()
{
    for(int i=0; i<cur_p; i++) {//�����г��ֵ�
        switch(person[i]) {
            case 0: lying[i] = 0; break;//diving����˵��
            case 2: lying[i] = 1; break;//evil��˵��
            case 1: lying[i] = time;//����������
        }
    }
    int ok = 1;
    for(int i=0; i<cur_l; i++) {//��ÿ��̨�ʷ���
        int flag = 1; //0������ȡ���� 1�����۲���Ҫȡ��
        if(lying[lines[i].who_said]) 
			flag = !flag; //���˵����˵�ѣ�Ҫȡ��
        if(lines[i].kind==0) { //����1��2
            if(lines[i].has_not) 
				flag = !flag;  //���ԭ����京��not, Ҫȡ��
            if(lines[i].id != 3) {//�ж��Լ�or���˵Ľ�ɫ
                if(flag && person[lines[i].person]!=lines[i].id) {//�жϵĽ�ɫ��ö�ٴ�ʱ�ȶ��Ľ�ɫ��һ��
                    ok = 0; break;
                }
                if(!flag && person[lines[i].person]==lines[i].id) {
                    ok = 0; break;
                }
            } else { // X is lying.//ĳ��˵��  ������˵�Լ�or����
                if(flag && !lying[lines[i].person]) {//�ж�˵�ѵĶ��������Ƿ������ö�����ʱ˵�ѣ�
                    ok = 0; break;
                }
                if(!flag && lying[lines[i].person]) {
                    ok = 0; break;
                }
            }
        } else { //����3
            if(flag && time != lines[i].time) {//��ʱö�ٵ�������˵���е�������һ�� ��flag = 1
                ok = 0; break;
            }
            if(!flag && time == lines[i].time) {
                ok = 0; break;
            }
        }
    }
    if(ok) {
        if(!found) {
            memcpy(result, person, sizeof(person));//������ɫ��Ϣ
            r_time = time;
            found = 1;
        } else {
            for(int i=0; i<cur_p; i++) {//��ǰö�������ֽ�ɫʱȷ������ɫ��Ϣ  ��ǰ���п��ܵĽ�ɫ��Ϣ Ӧȡ������ͬ�Ĳ���
                if(person[i] != result[i]) {//��ì����Ŀ
                    result[i] = -1;
                }
            }
            if(r_time != time) r_time = -1;
        }
    }
}

void dfs(int cur)
{
    if(cur == cur_p) {//���г��ֵ��˾�������ĳ�����
        time = 0;//��������ҹö���������
        dicide();
        time = 1;
        dicide();
        return;
    }
    for(int i=0; i<3; i++) {
        person[cur] = i;
        dfs(cur+1);
    }
}

int insert_p(char n)
{
    for(int i=0; i<cur_p; i++) if(name[i] == n) {//�Ѿ����ֹ�
        return i;
    }
    name[cur_p] = n;
    name_order[n-'A'] = cur_p;//��һ�γ���λ��
    return cur_p++;

}
int main ()
{
    int T = 0;
    while(scanf("%d", &cur_l) == 1) {
        if(!cur_l) break;
        char buff[10];
        cur_p = 0;
        memset(name_order, -1, sizeof(name_order));
        for(int i=0; i<cur_l; i++) {
            scanf("%s", buff);
            lines[i].who_said = insert_p(buff[0]);
            scanf("%s", buff);
            if(buff[1] == 't') { //����3
                lines[i].kind = 1;
                scanf("%s", buff); // is
                scanf("%s", buff); // day | night;
                if(buff[0] == 'd') lines[i].time = 0;
                else lines[i].time = 1;//��¼ʱ��
            } else { //����1��2
                lines[i].kind = 0;
                if(buff[0] == 'I') {// i am....
                    lines[i].person = lines[i].who_said;//����˵
                } else {
                    lines[i].person = insert_p(buff[0]);//˵����  ���뱻˵��
                }
                scanf("%s", buff);
                scanf("%s", buff);
                if(buff[0] == 'n') { // not
                    lines[i].has_not = 1;
                    scanf("%s", buff);
                }else {
                    lines[i].has_not = 0;
                }
                switch(buff[0]) {
                    case 'd': lines[i].id = 0; break; //divine
                    case 'h': lines[i].id = 1; break; //human
                    case 'e': lines[i].id = 2; break; //evil
                    case 'l': lines[i].id = 3; break; //lying
                }
            }
        }
        printf("Conversation #%d\n", ++T);
        found = false;
        dfs(0);
        int ok = 0;
        if(found) {
            for(int i=0; i<MAX_P; i++) {
                int order = name_order[i];//��ȡ���ֵ�˳��
                if(order != -1 && result[order] != -1){
                    ok = 1;
                    printf("%c is %s.\n", i+'A', kind[result[order]]);//���˽�ɫ�ѵõ��ж�
                }
            }
            if(r_time != -1) {//�����õ��ж�
                ok = 1;
                printf("It is %s.\n", r_time?"night":"day");
            }
            if(!ok) printf("No facts are deducible.\n");
        } else {
            printf("This is impossible.\n");
        }
        printf("\n");
    }
    return 0;
}
