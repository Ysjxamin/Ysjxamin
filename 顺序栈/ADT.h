#pragma once
#define MAXSIZE 100
typedef int Data;
//�������Ͷ���
struct Stack
{
	Data data[MAXSIZE] = { 0 };
	int top = 1;
};
/*������������*/
//��ʼ��
void initstack(Stack* s);
//���ջ
void clearstack(Stack* s);
//����ջ
void destroystack(Stack* s);
//�ж�ջ�Ƿ�Ϊ��
bool isemptystack(Stack* s);
//��ջ�����ҷǿգ���e����S��ջ��Ԫ��
Data gettop(Stack* s, Data* e);
//��ջ���ڣ�������Ԫ�ص�ջS�в���Ϊջ��Ԫ��
bool push(Stack* s, Data e);
//ɾ��ջS��ջ��Ԫ�أ�����e������ֵ
Data pop(Stack* s, Data* e);
int countstack(Stack* s);