#pragma once
struct StackNode
{
	int data;
	 StackNode* next=NULL;
};
//#define LinkStackPtr StackNode* ;
struct LinkStack
{
	StackNode* top=NULL;
	int count;
};
//函数原型
bool pop(LinkStack* S, int* e);
//初始化一个链栈
void initstack(LinkStack* S);
//确定链栈是否为空
bool isEmpty(const LinkStack* S);
//确定链栈是否为满
bool isFull(const LinkStack* S);
//确定链栈的项数
unsigned int countstack(const LinkStack* S);
//在链栈的尾端添加项
bool push(LinkStack* S, int e);
//把函数作用于链栈中的每一项（如释放空间）
void dowork( LinkStack* S, void(*func)(StackNode* s));
//释放内存空间
void Emptystack(LinkStack* S);