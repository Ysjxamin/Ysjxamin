#include <stdio.h>
#include <stdlib.h>
#include "Quene.h"

//局部函数
static void CopyToNode(Item item, Node* pn);
static void CopyToItem(Node*pn,Item*pi);

//初始化队列
void initquene(Quene* qe)
{
	qe->front = qe->rear = NULL;
	qe->items = 0;
}
//检查队列是否已满
bool IsFullQuene(const Quene* qe)
{
	return qe->items == MAXQUENE;
}
//检查队列是否为空
bool IsEmptyQuene(const Quene* qe)
{
	return qe->items == 0;
}
//确定队列中的项数
 int CountQuene(const Quene* qe)
{
	return qe->items;
}
//在队列末尾添加项
bool EnQuene(Item item, Quene* qe)
{
	Node* pnew;
	if (IsFullQuene(qe))
	{
		return false;
	}
	pnew = (Node*)malloc(sizeof(Node));
	//if (pnew == NULL)
	//{
	//	printf("分配内存失败\n");
	//	return false;
	//}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (IsEmptyQuene(qe))
	{
		qe->front = pnew;
		qe->rear = pnew;
	}
	else
	{
		qe->rear->next = pnew;
		qe->rear = pnew;
	}
		qe->items++;
	return true;
}
//从队列开头删除项
bool DeQuene(Item *psave, Quene* qe)
{
	Node* pt;
	if (IsEmptyQuene(qe))
		return false;
	CopyToItem(qe->front, psave);
	pt = qe->front;
	qe->front = qe->front->next;
	free(pt);
	qe->items--;
	if (qe->items == 0)
		qe->rear = NULL;
	return true;

}
//清空队列
void EmptyQuene(Quene* qe)
{
	Item value;
	while (!IsEmptyQuene(qe))
	{
		DeQuene(&value, qe);
	}
}
//局部函数
static void CopyToNode(Item item, Node* pn)
{
	pn->item = item;
}
static void CopyToItem(Node* pn, Item* pi)
{
	*pi = pn->item;
}