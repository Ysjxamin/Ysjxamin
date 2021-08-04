#pragma once
#define MAXSIZE 100
typedef int Data;
//数据类型定义
struct Stack
{
	Data data[MAXSIZE] = { 0 };
	int top = 1;
};
/*函数操作定义*/
//初始化
void initstack(Stack* s);
//清空栈
void clearstack(Stack* s);
//销毁栈
void destroystack(Stack* s);
//判断栈是否为空
bool isemptystack(Stack* s);
//若栈存在且非空，用e返回S的栈顶元素
Data gettop(Stack* s, Data* e);
//若栈存在，插入新元素到栈S中并成为栈顶元素
bool push(Stack* s, Data e);
//删除栈S中栈顶元素，并用e返回其值
Data pop(Stack* s, Data* e);
int countstack(Stack* s);