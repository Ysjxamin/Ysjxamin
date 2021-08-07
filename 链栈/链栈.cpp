// 链栈.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<stdlib.h>
#include"ADT.h"
#include <iostream>
using namespace std;
static void addstack(LinkStack* S, int e);

static void detop(LinkStack* S, int* e);

static void showtop(LinkStack* S, int e);

static void showmenu();

static void clearstack(LinkStack* S, StackNode* s);

static void clearstacknode(StackNode* s);
int main()
{
    LinkStack* S;
    S = (LinkStack*)malloc(sizeof(LinkStack));
    S->count = 0;
    int e=0;
    int ret = 0;
    StackNode* s=NULL;
    showmenu();
    while (1)
    {
        cout << "请输入你的选择：" << endl;
        cin >> ret;
        switch (ret)
        {
        case 1:
            addstack(S, e);
            break;
        case 2:
            detop(S, &e);
            break;
        case 3:
            showtop(S, e);
            break;
        case 4:
            Emptystack(S);
            cout << "清空成功" << endl;
            break;
        case 5:
            //Emptystack(S);
            //cout << "销毁成功" << endl;
            break;
        case 6:
            cout << "栈中元素个数为： " << countstack(S) << endl;
            break;
        case 7:
            initstack(S);
            cout << "初始化成功" << endl;
            break;
        default:
            break;
        }
    }
    free(S);
}
   /* initstack(s);
    cout << "请输入第一个数" << endl;
    cin >> e;
    push(s, e);
    cout << "此时栈中的元素个数：" << s->count<< endl;
    cout << "请输入第二个数" << endl;
    cin >> e;
    push(s, e);
    cout << "此时栈中的元素个数：" << countstack(s) << endl;
    cout << "请输入第三个数" << endl;
    cin >> e;
    push(s, e);
    cout << "此时栈中的元素个数：" << s->count << endl;
    pop(s, &e);
    cout << "删除栈顶元素后元素个数：" << s->count << endl;
    pop(s, &e);
    cout << "删除栈顶元素后元素个数：" << s->count << endl;
    pop(s, &e);
    cout << "删除栈顶元素后元素个数：" << s->count << endl;
    free(s);
    free(s);*/
static void addstack(LinkStack* S, int e)
{
    cout << "请输入要入栈的元素：" << endl;
    cin >> e;
    push(S, e);
}
static void detop(LinkStack* S, int* e)
{
    if (pop(S, e))
        cout << "删除成功！" << endl;
    else
        cout << "栈已空，无法删除！" << endl;
}
static void showtop(LinkStack* s, int e)
{
    if (s->top == NULL)
        cout << "栈已清空" << endl;
    else
        cout << "此时位于栈顶的元素为：" << s->top->data << endl;
}
static void showmenu()//前面要加函数类型
{
    cout << "************************************" << endl;
    cout << "************欢迎使用链栈**************" << endl;
    cout << "**********1.添加元素************" << endl;
    cout << "**********2.删除元素************" << endl;
    cout << "**********3.显示栈顶************" << endl;
    cout << "**********4.清空栈************" << endl;
    //cout << "**********5.销毁栈************" << endl;
    cout << "**********6.栈中元素个数************" << endl;
    cout << "**********7.初始化栈************" << endl;
    cout << "************************************" << endl;
}
/*static void clearstacknode(StackNode* s)
{
    StackNode* pnew;
    s->data = 0;
    pnew = s;
    s = s->next;
    free(pnew);
    
}
static void clearstack(LinkStack* S,StackNode* s)
{
    dowork(S,clearstacknode);
}*/
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
