#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>

#define NSIZE 50
//��Ӱ�ṹ��
typedef struct film
{
	char title[NSIZE];
	int rating;
}Item;


//���ṹ��
typedef struct node
{
	Item item;
	struct node* next=NULL;
}Node;

//������
typedef Node* List;
//����ԭ��
//��ʼ��һ������
void initlist(List* plist);
//ȷ�������Ƿ�Ϊ��
bool isEmpty(const List* plist);
//ȷ�������Ƿ�Ϊ��
bool isFull(const List* plist);

//ȷ�����������
unsigned int countlist(const List* plist);

//�������β�������
bool additemtolist( List* plist, Item item);
//�Ѻ��������������е�ÿһ����ͷſռ䣩
void dowork(const List* plist, void(*func)(Item item));
//�ͷ��ڴ�ռ�
void Emptylist(List* plist);
#endif