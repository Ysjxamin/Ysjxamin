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
		cout << "���������ѡ��" << endl;
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
			cout << "ջ��Ԫ�ظ���Ϊ�� " << countstack(s)<<endl;
			break;
		default:
			break;
		}
	}
	/*cout << "������Ҫ��ջ��Ԫ�أ�" << endl;
	cin >> e;
	push(s, e);
	cout << "��ʱ����ջ����Ԫ��Ϊ��" << gettop(s, &e) << endl;
	cout << "������Ҫ��ջ��Ԫ�أ�" << endl;
	cin >> e;
	push(s, e);
	cout << "��ʱ����ջ����Ԫ��Ϊ��" << gettop(s, &e) << endl;
	cout << "top��ֵΪ��" << s->top << endl;
	cout << "������Ҫ��ջ��Ԫ�أ�" << endl;
	cin >> e;
	push(s, e);
	pop(s, &e);*/
	system("pause");
	return 0;
}
static void addstack(Stack* s, Data e)
{
	cout << "������Ҫ��ջ��Ԫ�أ�" << endl;
	cin >> e;
	push(s, e);
}
static void detop(Stack* s, Data* e)
{
	pop(s, e);
}
static void showtop(Stack*s,Data e)
{
	cout << "��ʱλ��ջ����Ԫ��Ϊ��" << gettop(s, &e) << endl;
}
static void showmenu()//ǰ��Ҫ�Ӻ�������
{
	cout << "************************************" << endl;
	cout << "************��ӭʹ��ջ**************" << endl;
	cout << "**********1.���Ԫ��************" << endl;
	cout << "**********2.ɾ��Ԫ��************" << endl;
	cout << "**********3.��ʾջ��************" << endl;
	cout << "**********4.���ջ************" << endl;
	cout << "**********5.����ջ************" << endl;
	cout << "**********6.ջ��Ԫ�ظ���************" << endl;
	cout << "**********7.��������ĵ�************" << endl;
	cout << "************************************" << endl;
}