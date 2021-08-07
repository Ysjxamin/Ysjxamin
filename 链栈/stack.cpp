#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"
//函数原型
//初始化一个链栈
void initstack(LinkStack* S)
{
	S->top = NULL;
	S->count = 0;
}
//确定链栈是否为空
bool isEmpty(const LinkStack* S)
{
	if (S->top == NULL)
		return true;
	else
		return false;

}
//确定链栈是否为满
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
//确定链栈的项数
unsigned int countstack(const LinkStack* S)
{
	return S->count;
}
//在链栈的栈顶添加项
bool push(LinkStack* S, int e)
{
	StackNode* s=NULL;
	s = (StackNode*)malloc(sizeof(StackNode));
	s->data = e;
	s->next = S->top;//把当前的栈顶元素赋值给新结点的直接后继
	S->top = s;
	S->count++;
	return true;
}
//删除栈顶的元素
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
//把函数作用于链栈中的每一项（如释放空间）
void dowork( LinkStack* S,static void(*func)(StackNode* s))
{
	//设置链栈的开始
	StackNode* s = (StackNode*)malloc(sizeof(StackNode));
	 s = S->top;
	while (s!= NULL)
	{
		(*func)(s);
	}
}
//释放内存空间
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