#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*�ֲ�����*/
static void CopyToNode(Item item, Node* pnode);
static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;
}

/*�ӿں���*/
//����ԭ��
//��ʼ��һ������
void initlist(List* plist)
{
	*plist = NULL;
}
//ȷ�������Ƿ�Ϊ��

bool isEmpty(const List* plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
	
}
//ȷ�������Ƿ�Ϊ��
bool isFull(const List* plist)
{
	Node* pt;
	bool full;
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;//�ڴ�����
	else
		full = false;//�ڴ�δ��
	free(pt);//�ж��꼴�ͷ��ڴ�
	return full;
}

//ȷ�����������
unsigned int countlist(const List* plist)
{
	unsigned int count = 0;
	Node* pnode = *plist;//��������Ŀ�ʼ����Ҫһ����ָ��pnode������ʧplist��λ��
	while (pnode != NULL)
	{
		count++;
		pnode = pnode->next;
	}
	return count;
}

//�������β�������
bool additemtolist( List* plist, Item item)
{
	Node* pnew = (Node*)malloc(sizeof(Node));
	Node* scan = *plist;
	//pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;
	CopyToNode(item, pnew);
	pnew->next = NULL;//β�巨�½ڵ��nextΪ��
	if (scan == NULL)//������
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;
		scan->next = pnew;
	}
	return true;
}
//�Ѻ��������������е�ÿһ����ͷſռ䣩
void dowork(const List* plist, void(*func)(Item item))
{
	Node* pnode=*plist;//��������Ŀ�ʼ
	while (pnode != NULL)
	{
		(*func)(pnode->item);
		pnode = pnode->next;
	}

}
//�ͷ��ڴ�ռ�
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
