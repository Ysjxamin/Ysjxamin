#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>

#define NSIZE 50
//电影结构体
typedef struct film
{
	char title[NSIZE];
	int rating;
}Item;


//结点结构体
typedef struct node
{
	Item item;
	struct node* next=NULL;
}Node;

//链表定义
typedef Node* List;
//函数原型
//初始化一个链表
void initlist(List* plist);
//确定链表是否为空
bool isEmpty(const List* plist);
//确定链表是否为满
bool isFull(const List* plist);

//确定链表的项数
unsigned int countlist(const List* plist);

//在链表的尾端添加项
bool additemtolist( List* plist, Item item);
//把函数作用于链表中的每一项（如释放空间）
void dowork(const List* plist, void(*func)(Item item));
//释放内存空间
void Emptylist(List* plist);
#endif