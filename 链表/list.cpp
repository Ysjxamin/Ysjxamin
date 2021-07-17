#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*局部函数*/
static void CopyToNode(Item item, Node* pnode);
static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;
}

/*接口函数*/
//函数原型
//初始化一个链表
void initlist(List* plist)
{
	*plist = NULL;
}
//确定链表是否为空

bool isEmpty(const List* plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
	
}
//确定链表是否为满
bool isFull(const List* plist)
{
	Node* pt;
	bool full;
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;//内存已满
	else
		full = false;//内存未满
	free(pt);//判断完即释放内存
	return full;
}

//确定链表的项数
unsigned int countlist(const List* plist)
{
	unsigned int count = 0;
	Node* pnode = *plist;//设置链表的开始且需要一个新指针pnode，否则丢失plist的位置
	while (pnode != NULL)
	{
		count++;
		pnode = pnode->next;
	}
	return count;
}

//在链表的尾端添加项
bool additemtolist( List* plist, Item item)
{
	Node* pnew = (Node*)malloc(sizeof(Node));
	Node* scan = *plist;
	//pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;
	CopyToNode(item, pnew);
	pnew->next = NULL;//尾插法新节点的next为空
	if (scan == NULL)//空链表
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;
		scan->next = pnew;
	}
	return true;
}
//把函数作用于链表中的每一项（如释放空间）
void dowork(const List* plist, void(*func)(Item item))
{
	Node* pnode=*plist;//设置链表的开始
	while (pnode != NULL)
	{
		(*func)(pnode->item);
		pnode = pnode->next;
	}

}
//释放内存空间
void Emptylist(List* plist)
{
	Node* pnode;
	while (*plist != NULL)
	{
		pnode = (*plist)->next;
		free(*plist);
		*plist = pnode;
	}
}
