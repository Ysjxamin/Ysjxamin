#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<stdbool.h>

//Item类型 的定义
typedef int Item;

//节点的定义
typedef struct node
{
	Item item;
	struct node* next;
}Node;

//队列的定义
typedef struct quene
{
	Node* front;//指向队列首项
	Node* rear; //指向队列尾项
	int items;  //队列中的项数
}Quene;

#define MAXQUENE 10;
//函数

//初始化队列
void initquene(Quene* qe);
//检查队列是否已满
bool IsFullQuene(const Quene* qe);
//检查队列是否为空
bool IsEmptyQuene(const Quene* qe);
//确定队列中的项数
 int CountQuene(const Quene* qe);
//在队列末尾添加项
bool EnQuene(Item item, Quene* qe);
//从队列开头删除项???????????
bool DeQuene(Item *item, Quene* qe);
//清空队列
void EmptyQuene(Quene* qe);


#endif

