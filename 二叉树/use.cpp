#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#pragma warning(disable : 4996)
char menu(void);
void addpet(Tree* pt);
void droppet(Tree* pt);
void showpets( Tree* pt);
void findpet( Tree* pt);
void printitem(Item item);
void uppercase(char* str);
char* s_gets(char* st, int n);
//Tree pets;
int main()
{
	Tree pets;
	inittree(&pets);
	char ch = 'a';
	while (ch != 'D')
	{
		printf("		   菜单\n");
		printf("----------------------------------------------------\n");
		printf("	A.增加宠物\n");
		printf("	B.展示宠物\n");
		printf("	C.查找宠物\n");
		printf("	D.计算数量\n");
		printf("	E.删除宠物\n");
		printf("	F.退出\n");
		printf("----------------------------------------------------\n");
		printf("请输入你的选择？\n");
		//ch = getchar();
		scanf("%c", &ch);
		while (getchar() != '\n');
		system("cls");
		switch (ch)
		{
		case 'A':
			addpet(&pets);
			break;
		case'B':
			showpets(&pets);
			break;
		case'C':
			findpet(&pets);
			break;
		case'D':
			printf("%d pets in club\n",CountTree(&pets));
			break;
		case'E':
			droppet(&pets);
			break;
		case 'F':
			DeleteAll(&pets);
			puts("Bye.");
			break;
		}
	}
	return 0;
}
void addpet(Tree* pt)
{
	Item temp;

	if (IsFullTree(pt))
		puts("No room in the club!");
	else
	{
		printf("Please enter name of pet:\n");
		//s_gets(temp.petname, MAXNAME);
		scanf("%s", &temp.petname);
		while (getchar() != '\n');
		printf("Please enter pet kind:\n");
		scanf("%s", &temp.petkind);
		while (getchar() != '\n');
		//s_gets(temp.petkind, MAXNAME);
		uppercase(temp.petname);
		uppercase(temp.petkind);
		AddItem(&temp, pt);
	}
}
void droppet(Tree* pt)
{
	Item temp;

	if (IsEmptyTree(pt))
	{
		puts("No entries!");
		return;     /* quit function if tree is empty */
	}

	puts("Please enter name of pet you wish to delete:");
	s_gets(temp.petname, MAXNAME);
	puts("Please enter pet kind:");
	s_gets(temp.petkind, MAXNAME);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s the %s ", temp.petname, temp.petkind);
	if (DeleteItem(&temp, pt))
		printf("is dropped from the club.\n");
	else
		printf("is not a member.\n");
}
void showpets( Tree* pt)
{
	if (IsEmptyTree(pt))
		puts("No entries!");
	else
		DoWork(pt, printitem);
}
void findpet( Tree* pt)
{
	Item temp;

	if (IsEmptyTree(pt))
	{
		puts("No entries!");
		return;     /* quit function if tree is empty */
	}

	puts("Please enter name of pet you wish to find:");
	s_gets(temp.petname, MAXNAME);
	puts("Please enter pet kind:");
	s_gets(temp.petkind, MAXNAME);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s the %s ", temp.petname, temp.petkind);
	if (SeekTree(&temp, pt))
		printf("is a member.\n");
	else
		printf("is not a member.\n");
}
void printitem(Item item)
{
	printf("Pet: %-19s  Kind: %-19s\n", item.petname,
		item.petkind);
}

void uppercase(char* str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');   // look for newline
		if (find)                  // if the address is not NULL,
			*find = '\0';          // place a null character there
		else
			while (getchar() != '\n')
				continue;          // dispose of rest of line
	}
	return ret_val;
}




















