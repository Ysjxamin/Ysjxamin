#include<stdio.h>
#include<stdlib.h>
#include"list.h"
#include <iostream>
#pragma warning(disable : 4996)
void showmovies(Item item);
char* s_gets(char* st, int n);
int main()
{
	//变量
	List movies;
	Item temp;
	//初始化
	initlist(&movies);
	if (isFull(&movies))
	{
		printf("内存空间不足，有缘再见！");
		exit(1);
	}


	//获取用户输入并储存
	puts("请输入第一本电影的标题");
	while (s_gets(temp.title, NSIZE) != NULL && temp.title[0] != '\0')
	{
		puts("输入你的评分<0-10>");
		scanf("%d", &temp.rating);
		while (getchar() != '\n')
			continue;
		if (additemtolist(&movies, temp) == false)
		{
			printf("分配内存失败");
			break;
		}
		puts("请输入下一部电影");
	}

	//显示
	if (isEmpty(&movies))
	{
		printf("链表为空");
	}
	else
	{
		printf("电影列表如下：\n");
		dowork(&movies, showmovies);//????????????
	}

	//清理
	Emptylist(&movies);
	printf("再见！");
	return 0;
}
	//全局函数定义
	void showmovies(Item item)
	{
		printf("Movie:  %s  Rating:  %d\n", item.title, item.rating);
	}
	char* s_gets(char* st, int n)
	{
		char* ret_val;
		char* find;
		ret_val = fgets(st, n, stdin);
		if (ret_val)
		{
			find = strchr(st, '\n');
			if (find)
				*find = '\0';
			else
				while (getchar() != '\n')
					continue;
		}
		return ret_val;
	}