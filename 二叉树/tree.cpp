#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

/*�ֲ���������*/
typedef struct pair
{
	Node* parent;
	Node* child;
}Pair;

/*�ֲ���������*/
static Node* MakeNode(const Item* pnew);
static bool ToLeft(const Item* as1,const Item* as2);//���������������
static bool ToRight(const Item* as1, const Item* as2);
static void AddNode(Node* new_node,Node * tree);
static Pair seekitem(const Item* item,const Tree* tree);
static void dowork(const Node* root,void(*fun)(Item item));
static void DeleteNode(Node** ppdad);
static void DeleteAllNode(Node* tree);

/*��������*/

//��ʼ����
void inittree(Tree* ptree)
{
	ptree->tree = NULL;
	ptree->size = 0;
}

//ȷ�����Ƿ�Ϊ��
bool IsEmptyTree(Tree* ptree)
{
	if (ptree->tree == NULL)
		return true;
	else
		return false;
}
//ȷ�����Ƿ�����
bool IsFullTree(Tree* ptree)
{
	return ptree->size == MAXITEM;
}

//ȷ����������
int CountTree(Tree* ptree)
{
	return ptree->size;
}

//���������һ����
//�ȼ�����Ƿ������ټ���Ƿ����ظ�
bool AddItem(const Item* pt, Tree* ptree)
{
	Node* new_node;
	if (IsFullTree(ptree)==true)
	{
		printf("���Ѿ����ˣ��޷�����µ���");
		return false;
	}
	if (seekitem(pt,ptree).child != NULL)
	{
		printf("�ҵ��ظ���������");
		return false;
	}
	new_node = MakeNode(pt);//ָ���½ڵ�
	if (new_node == NULL)
	{
		printf("�����ڴ�ʧ��");
		return false;
	}
	/*�Ѿ��ɹ������½ڵ�*/
	ptree->size++;
	//���½ڵ����ӵ�����
	//���������
	//����Ϊ�����½ڵ�Ϊ���ĸ����
	//������Ϊ����������Ѱ���ʵ�λ�ò���
	if (ptree->tree == NULL)
		ptree->tree = new_node;
	else
		AddNode(new_node,ptree->tree);
	return true;
}
//�����в���һ���� ���ҵ��򷵻�true ����Ϊfalse
bool SeekTree(const Item* pt, Tree* ptree)
{
	if (seekitem(pt,ptree).child== NULL)//������Ŀ�Ƿ�鵽 δ�ҵ���childΪNULL
		return false;
	else
		return true;
}
//������ɾ��һ����
/*�Ȳ���*/
bool DeleteItem(const Item* pt, Tree* ptree)
{
	Pair look;
	look = seekitem(pt,ptree);
	if (look.child == NULL)//�鿴�Ƿ�鵽����δ�鵽
		return false;
	if (look.parent == NULL)//��ɾ���Ľڵ�Ϊ���ڵ�
		DeleteNode(&ptree->tree);
	else if (look.parent->left == look.child)//��ɾ���Ľڵ�Ϊ��ڵ�
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);//��ɾ���Ľڵ�Ϊ�ҽڵ�
	ptree->size--;
	return true;
}

//�Ѻ���Ӧ�������е�ÿһ��
void DoWork(Tree* ptree, void(*fun)(Item item))//��������
{
	if (ptree != NULL)
		dowork(ptree->tree,fun);//�����ڽڵ�
}
//�����
void DeleteAll(Tree* ptree)//ɾ����
{
	if (ptree != NULL)
		DeleteAllNode(ptree->tree);//ɾ���ڵ�
	ptree->tree = NULL;
	ptree->size = 0;
}
/*�ֲ�����*/

static void dowork(const node* root, void(*fun)(item item))
{
	if (root != NULL)
	{
		dowork(root->left, fun);
		(*fun)(root->item);
		dowork(root->right, fun);
	}
}

static void DeleteAllNode(Node* tree)
{
	Node* psave;
	if (tree != NULL)
	{
		psave = tree->right;
		DeleteAllNode(tree->left);
		free(tree);
		DeleteAllNode(tree->right);
	}
}
//additemʵ�ּ���Լ���item���½ڵ��ϣ�������������Ҫʵ�ֽ��½ڵ��������
static void AddNode(Node* new_node, Node* tree)
{
	//����½ڵ��������
	if (ToLeft(&new_node->item, &tree->item))
	{
		if (tree->left == NULL)//һֱ�ݹ���õ�������Ϊ��
		{
			tree->left = new_node;//�����ӵ��˿�λ��
		}
		else
		{
			AddNode(new_node, tree->left);//�ݹ����
		}
	}
	//����½ڵ������ұ�
	else if (ToRight(&new_node->item, &tree->item))
	{
		if (tree->right == NULL)//һֱ�ݹ���õ�������Ϊ��
		{
			tree->right = new_node;//�����ӵ��˿�λ��
		}
		else
		{
			AddNode(new_node, tree->right);//�ݹ����
		}
	}
	//����½ڵ㲻�����ģ��޷��������ظ�
	else
	{
		printf("�����ظ������ʧ��");
		exit(1);
	}
}

static bool ToLeft(const Item* as1, const Item* as2)//���������������
{
	int out;
	if (out = strcmp(as1->petname, as2->petname) < 0)
		return true;
	else if (out == 0 && strcmp(as1->petkind, as2->petkind) < 0)
		return true;
	else
		return false;
}
static bool ToRight(const Item* as1, const Item* as2)
{
	int out;
	if (out = strcmp(as1->petname, as2->petname) > 0)
		return true;
	else if (out == 0 && strcmp(as1->petkind, as2->petkind) > 0)
		return true;
	else
		return false;
}

static Node* MakeNode(const Item* pnew)
{
	Node* new_node;
	new_node = (Node*)malloc(sizeof(Node));
	if (new_node != NULL)
	{
		new_node->item = *pnew;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return new_node;
}

static Pair seekitem(const Item* item, const Tree* tree)
{
	Pair look;
	look.parent = NULL;
	look.child = tree->tree;
	if (look.child == NULL)
		return look;
	while (look.child != NULL)
	{
		if (ToLeft(item, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}
		else if (ToRight(item, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		else
			break;//�������֣�˵��������ȵ��������GET!
	}
	return look;
}
static void DeleteNode(Node** ppdad)
{
	Node* psave;
	if ((*ppdad)->left == NULL)//����ñ�ɾ�ڵ㸸�ڵ������ӽڵ����ϵ
	{
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->right;
		free(psave);
	}
	else if ((*ppdad)->right == NULL)//����ñ�ɾ�ڵ㸸�ڵ������ӽڵ����ϵ
	{
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->left;
		free(psave);
	}
	else//�������ڵ�
	{
		for (psave = (*ppdad)->left;psave->right != NULL; psave = psave->right)
			continue;
		psave->right = (*ppdad)->right;
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->left;
		free(psave);
	}
}