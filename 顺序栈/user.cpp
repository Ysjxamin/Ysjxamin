#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"
#include <iostream>
using namespace std;
#pragma warning(disable : 4996)
static void addstack(Stack* s, Data e);

static void detop(Stack* s, Data* e);

static void showtop(Stack* s, Data e);

static void showmenu();
int main()
{
	Stack* s=(Stack*)malloc(sizeof(Stack));
	Data e=0;
	initstack(s);
	int ret=0;
	showmenu();
	while (1)
	{
		cout << "请输入你的选择：" << endl;
		cin >> ret;
		switch (ret)
		{
		case 1:
			addstack(s, e);
			break;
		case 2:
			detop(s, &e);
			break;
		case 3:
			showtop(s,e);
			break;
		case 4:
			clearstack(s);
			break;
		case 5:
			destroystack(s);
			break;
		case 6:
			cout << "栈中元素个数为： " << countstack(s)<<endl;
			break;
		default:
			break;
		}
	}
	/*cout << "请输入要入栈的元素：" << endl;
	cin >> e;
	push(s, e);
	cout << "此时处于栈顶的元素为：" << gettop(s, &e) << endl;
	cout << "请输入要入栈的元素：" << endl;
	cin >> e;
	push(s, e);
	cout << "此时处于栈顶的元素为：" << gettop(s, &e) << endl;
	cout << "top的值为：" << s->top << endl;
	cout << "请输入要入栈的元素：" << endl;
	cin >> e;
	push(s, e);
	pop(s, &e);*/
	system("pause");
	return 0;
}
static void addstack(Stack* s, Data e)
{
	cout << "请输入要入栈的元素：" << endl;
	cin >> e;
	push(s, e);
}
static void detop(Stack* s, Data* e)
{
	pop(s, e);
}
static void showtop(Stack*s,Data e)
{
	cout << "此时位于栈顶的元素为：" << gettop(s, &e) << endl;
}
static void showmenu()//前面要加函数类型
{
	cout << "************************************" << endl;
	cout << "************欢迎使用栈**************" << endl;
	cout << "**********1.添加元素************" << endl;
	cout << "**********2.删除元素************" << endl;
	cout << "**********3.显示栈顶************" << endl;
	cout << "**********4.清空栈************" << endl;
	cout << "**********5.销毁栈************" << endl;
	cout << "**********6.栈中元素个数************" << endl;
	cout << "**********7.清空所有文档************" << endl;
	cout << "************************************" << endl;
}