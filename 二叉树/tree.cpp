#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"tree.h"

/*局部数据类型*/
typedef struct pair
{
	Node* parent;
	Node* child;
}Pair;

/*局部函数类型*/
static Node* MakeNode(const Item* pnew);
static bool ToLeft(const Item* as1,const Item* as2);//导航根据排序规则
static bool ToRight(const Item* as1, const Item* as2);
static void AddNode(Node* new_node,Node * tree);
static Pair seekitem(const Item* item,const Tree* tree);
static void dowork(const Node* root,void(*fun)(Item item));
static void DeleteNode(Node** ppdad);
static void DeleteAllNode(Node* tree);

/*函数定义*/

//初始化树
void inittree(Tree* ptree)
{
	ptree->tree = NULL;
	ptree->size = 0;
}

//确定树是否为空
bool IsEmptyTree(Tree* ptree)
{
	if (ptree->tree == NULL)
		return true;
	else
		return false;
}
//确定树是否已满
bool IsFullTree(Tree* ptree)
{
	return ptree->size == MAXITEM;
}

//确定树的项数
int CountTree(Tree* ptree)
{
	return ptree->size;
}

//在树中添加一个项
//先检查树是否满，再检查是否有重复
bool AddItem(const Item* pt, Tree* ptree)
{
	Node* new_node;
	if (IsFullTree(ptree)==true)
	{
		printf("树已经满了，无法添加新的项");
		return false;
	}
	if (seekitem(pt,ptree).child != NULL)
	{
		printf("找到重复项，不予添加");
		return false;
	}
	new_node = MakeNode(pt);//指向新节点
	if (new_node == NULL)
	{
		printf("分配内存失败");
		return false;
	}
	/*已经成功创建新节点*/
	ptree->size++;
	//将新节点连接到树中
	//分两种情况
	//若树为空则新节点为树的根结点
	//若树不为空则在树中寻找适当位置插入
	if (ptree->tree == NULL)
		ptree->tree = new_node;
	else
		AddNode(new_node,ptree->tree);
	return true;
}
//在树中查找一个项 查找到则返回true 否则为false
bool SeekTree(const Item* pt, Tree* ptree)
{
	if (seekitem(pt,ptree).child== NULL)//查找项目是否查到 未找到则child为NULL
		return false;
	else
		return true;
}
//在树中删除一个项
/*先查找*/
bool DeleteItem(const Item* pt, Tree* ptree)
{
	Pair look;
	look = seekitem(pt,ptree);
	if (look.child == NULL)//查看是否查到——未查到
		return false;
	if (look.parent == NULL)//待删除的节点为根节点
		DeleteNode(&ptree->tree);
	else if (look.parent->left == look.child)//待删除的节点为左节点
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);//待删除的节点为右节点
	ptree->size--;
	return true;
}

//把函数应用于树中的每一项
void DoWork(Tree* ptree, void(*fun)(Item item))//作用于树
{
	if (ptree != NULL)
		dowork(ptree->tree,fun);//作用于节点
}
//清空树
void DeleteAll(Tree* ptree)//删除树
{
	if (ptree != NULL)
		DeleteAllNode(ptree->tree);//删除节点
	ptree->tree = NULL;
	ptree->size = 0;
}
/*局部函数*/

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
//additem实现检查以及将item与新节点结合，本函数仅仅需要实现将新节点插入树中
static void AddNode(Node* new_node, Node* tree)
{
	//如果新节点需在左边
	if (ToLeft(&new_node->item, &tree->item))
	{
		if (tree->left == NULL)//一直递归调用到左子树为空
		{
			tree->left = new_node;//即连接到此空位上
		}
		else
		{
			AddNode(new_node, tree->left);//递归调用
		}
	}
	//如果新节点需在右边
	else if (ToRight(&new_node->item, &tree->item))
	{
		if (tree->right == NULL)//一直递归调用到左子树为空
		{
			tree->right = new_node;//即连接到此空位上
		}
		else
		{
			AddNode(new_node, tree->right);//递归调用
		}
	}
	//如果新节点不三不四，无法插入因重复
	else
	{
		printf("出现重复项，插入失败");
		exit(1);
	}
}

static bool ToLeft(const Item* as1, const Item* as2)//导航根据排序规则
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
			break;//若是这种，说明必是相等的情况，即GET!
	}
	return look;
}
static void DeleteNode(Node** ppdad)
{
	Node* psave;
	if ((*ppdad)->left == NULL)//保存好被删节点父节点与其子节点的联系
	{
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->right;
		free(psave);
	}
	else if ((*ppdad)->right == NULL)//保存好被删节点父节点与其子节点的联系
	{
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->left;
		free(psave);
	}
	else//有两个节点
	{
		for (psave = (*ppdad)->left;psave->right != NULL; psave = psave->right)
			continue;
		psave->right = (*ppdad)->right;
		psave = (*ppdad);
		(*ppdad) = (*ppdad)->left;
		free(psave);
	}
}