#pragma once
struct StackNode
{
	int data;
	 StackNode* next=NULL;
};
//#define LinkStackPtr StackNode* ;
struct LinkStack
{
	StackNode* top=NULL;
	int count;
};
//����ԭ��
bool pop(LinkStack* S, int* e);
//��ʼ��һ����ջ
void initstack(LinkStack* S);
//ȷ����ջ�Ƿ�Ϊ��
bool isEmpty(const LinkStack* S);
//ȷ����ջ�Ƿ�Ϊ��
bool isFull(const LinkStack* S);
//ȷ����ջ������
unsigned int countstack(const LinkStack* S);
//����ջ��β�������
bool push(LinkStack* S, int e);
//�Ѻ�����������ջ�е�ÿһ����ͷſռ䣩
void dowork( LinkStack* S, void(*func)(StackNode* s));
//�ͷ��ڴ�ռ�
void Emptystack(LinkStack* S);