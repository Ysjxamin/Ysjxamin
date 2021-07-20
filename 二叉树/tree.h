#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>


#define MAXNAME 20
//根据实际情况定义Item
typedef struct item
{
	char petname[MAXNAME];
	char petkind[MAXNAME];
}Item;
#define MAXITEM 20
//定义节点
typedef struct node
{
	Item item;
	struct node* left;
	struct node* right;
}Node;
//定义树
typedef struct tree
{
	Node* tree;
	int size;
}Tree;
/*函数原型*/
//初始化树

void inittree(Tree *ptree);
//确定树是否为空
bool IsFullTree(Tree* ptree);
//确定树是否已满
bool IsEmptyTree(Tree* ptree);
//确定树的项数
int CountTree(Tree* ptree);
//在树中添加一个项
bool AddItem(const Item* pt, Tree* ptree);
//在树中查找一个项
bool SeekTree(const Item* pt,Tree* ptree);
//在树中删除一个项
bool DeleteItem(const Item* pt, Tree* ptree);
//把函数应用于树中的每一项
void DoWork(Tree* ptree, void(*fun)(Item item));
//清空树
void DeleteAll(Tree* ptree);


#endif
