#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"

/*������������*/
//��ʼ��ջ
void initstack(Stack* s)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		s->data[i] = { 0 };
	}
	s->top = -1;
}
//���ջ
void clearstack(Stack* s)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		s->data[i] = { 0 };
	}
	s->top = -1;
}
//����ջ
void destroystack(Stack* s)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		s->data[i] = { 0 };
	}
	s->top = -1;
	s =NULL;
	free (s);
}
//�ж�ջ�Ƿ�Ϊ��
bool isemptystack(Stack* s)
{
	if (s->top == -1)
		return true;
	else
		return false;
}
//��ջ�����ҷǿգ���e����S��ջ��Ԫ��
Data gettop(Stack* s, Data* e)
{
	if (s != NULL && s->top != -1)
	{
		*e = s->data[s->top];
		return *e;
	}
	else
	{
		return 0;
	}
}
//��ջ���ڣ�������Ԫ�ص�ջS�в���Ϊջ��Ԫ��
bool push(Stack* s, Data e)
{
	if (s->top == MAXSIZE - 1)/*ջ��*/
	{
		return false;
	}
	s->top++;
	s->data[s->top] = e;
	return true;
}
//ɾ��ջS��ջ��Ԫ�أ�����e������ֵ
Data pop(Stack* s, Data* e)
{
	if (s->top == -1)/*ջ��*/
		return false;
	*e = s->data[s->top];//?????????
	s->top--;
	return *e;
}
int countstack(Stack* s)
{
	return s->top + 1;
}