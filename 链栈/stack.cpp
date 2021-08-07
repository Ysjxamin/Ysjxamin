#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"
//����ԭ��
//��ʼ��һ����ջ
void initstack(LinkStack* S)
{
	S->top = NULL;
	S->count = 0;
}
//ȷ����ջ�Ƿ�Ϊ��
bool isEmpty(const LinkStack* S)
{
	if (S->top == NULL)
		return true;
	else
		return false;

}
//ȷ����ջ�Ƿ�Ϊ��
bool isFull(const LinkStack* S)
{
	bool full;
	StackNode* s;
	s = (StackNode*)malloc(sizeof(StackNode));
	if (s == NULL)
		full = true;
	else
		full = false;
	free(s);
	return full;
}
//ȷ����ջ������
unsigned int countstack(const LinkStack* S)
{
	return S->count;
}
//����ջ��ջ�������
bool push(LinkStack* S, int e)
{
	StackNode* s=NULL;
	s = (StackNode*)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;//�ѵ�ǰ��ջ��Ԫ�ظ�ֵ���½���ֱ�Ӻ��
	S->top = s;
	S->count++;
	return true;
}
//ɾ��ջ����Ԫ��
bool pop(LinkStack* S, int* e)
{
	StackNode* p;
	if (isEmpty(S))
	{
		return false;
	}
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	free(p);
	S->count--;
	return true;
}
//�Ѻ�����������ջ�е�ÿһ����ͷſռ䣩
void dowork( LinkStack* S,static void(*func)(StackNode* s))
{
	//������ջ�Ŀ�ʼ
	StackNode* s = (StackNode*)malloc(sizeof(StackNode));
	 s = S->top;
	while (s!= NULL)
	{
		(*func)(s);
	}
}
//�ͷ��ڴ�ռ�
void Emptystack(LinkStack* S)
{
	StackNode* s = S->top;
	while (s != NULL)
	{
		StackNode* pnew;
		pnew = s;
		s = s->next;
		free(pnew);
	}
	S->top = NULL;
	S->count = 0;
}