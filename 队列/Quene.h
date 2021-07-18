#ifndef _QUEUE_H_
#define _QUEUE_H_
#include<stdbool.h>

//Item���� �Ķ���
typedef int Item;

//�ڵ�Ķ���
typedef struct node
{
	Item item;
	struct node* next;
}Node;

//���еĶ���
typedef struct quene
{
	Node* front;//ָ���������
	Node* rear; //ָ�����β��
	int items;  //�����е�����
}Quene;

#define MAXQUENE 10;
//����

//��ʼ������
void initquene(Quene* qe);
//�������Ƿ�����
bool IsFullQuene(const Quene* qe);
//�������Ƿ�Ϊ��
bool IsEmptyQuene(const Quene* qe);
//ȷ�������е�����
 int CountQuene(const Quene* qe);
//�ڶ���ĩβ�����
bool EnQuene(Item item, Quene* qe);
//�Ӷ��п�ͷɾ����???????????
bool DeQuene(Item *item, Quene* qe);
//��ն���
void EmptyQuene(Quene* qe);


#endif

