#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"

/*函数操作定义*/
//初始化栈
void initstack(Stack* s)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		s->data[i] = { 0 };
	}
	s->top = -1;
}
//清空栈
void clearstack(Stack* s)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		s->data[i] = { 0 };
	}
	s->top = -1;
}
//销毁栈
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
//判断栈是否为空
bool isemptystack(Stack* s)
{
	if (s->top == -1)
		return true;
	else
		return false;
}
//若栈存在且非空，用e返回S的栈顶元素
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
//若栈存在，插入新元素到栈S中并成为栈顶元素
bool push(Stack* s, Data e)
{
	if (s->top == MAXSIZE - 1)/*栈满*/
	{
		return false;
	}
	s->top++;
	s->data[s->top] = e;
	return true;
}
//删除栈S中栈顶元素，并用e返回其值
Data pop(Stack* s, Data* e)
{
	if (s->top == -1)/*栈空*/
		return false;
	*e = s->data[s->top];//?????????
	s->top--;
	return *e;
}
int countstack(Stack* s)
{
	return s->top + 1;
}