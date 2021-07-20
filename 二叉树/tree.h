#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>


#define MAXNAME 20
//����ʵ���������Item
typedef struct item
{
	char petname[MAXNAME];
	char petkind[MAXNAME];
}Item;
#define MAXITEM 20
//����ڵ�
typedef struct node
{
	Item item;
	struct node* left;
	struct node* right;
}Node;
//������
typedef struct tree
{
	Node* tree;
	int size;
}Tree;
/*����ԭ��*/
//��ʼ����

void inittree(Tree *ptree);
//ȷ�����Ƿ�Ϊ��
bool IsFullTree(Tree* ptree);
//ȷ�����Ƿ�����
bool IsEmptyTree(Tree* ptree);
//ȷ����������
int CountTree(Tree* ptree);
//���������һ����
bool AddItem(const Item* pt, Tree* ptree);
//�����в���һ����
bool SeekTree(const Item* pt,Tree* ptree);
//������ɾ��һ����
bool DeleteItem(const Item* pt, Tree* ptree);
//�Ѻ���Ӧ�������е�ÿһ��
void DoWork(Tree* ptree, void(*fun)(Item item));
//�����
void DeleteAll(Tree* ptree);


#endif
