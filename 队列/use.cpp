#include<stdio.h>
#include"Quene.h"
#pragma warning(disable : 4996)
int main(void)
{
	Quene Line;
	Item value;
	char ch='a';
	initquene(&Line);
	while (ch!='D')
	{
		printf("		   菜单\n");
		printf("----------------------------------------------------\n");
		printf("	A.增加元素\n");
		printf("	B.删除元素\n");
		printf("	C.显示项数\n");
		printf("	D.清空队列\n");
		printf("----------------------------------------------------\n");
		printf("请输入你的选择？\n");
		//ch = getchar();
		scanf("%c", &ch);
		switch (ch)
		{
		case 'A':
			printf("请输入你要填入的数字\n");
			scanf("%d", &value);
			if (IsFullQuene(&Line))
			{
				printf("队列已满不可加入\n");
			}
			else
			{
				printf("%d已填入队列中\n", value);
				EnQuene(value, &Line);
				printf("队列中有%d个元素\n", CountQuene(&Line));
			}
			break;
		case'B':
			if (IsEmptyQuene(&Line))
			{
				printf("队列为空，无数据可删除\n");
			}
			else
			{
				DeQuene(&value, &Line);
				printf("删除已完成\n");
				printf("队列中有%d个元素\n", CountQuene(&Line));
			}
			break;
		case'C':
			printf("队列中有%d个元素\n", CountQuene(&Line));
			break;
		case 'D':
			printf("队列中有%d个元素\n", CountQuene(&Line));
			EmptyQuene(&Line);
			printf("再见！\n");
			break;
		}

	}
	return 0;
}