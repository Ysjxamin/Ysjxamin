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
		printf("		   �˵�\n");
		printf("----------------------------------------------------\n");
		printf("	A.����Ԫ��\n");
		printf("	B.ɾ��Ԫ��\n");
		printf("	C.��ʾ����\n");
		printf("	D.��ն���\n");
		printf("----------------------------------------------------\n");
		printf("���������ѡ��\n");
		//ch = getchar();
		scanf("%c", &ch);
		switch (ch)
		{
		case 'A':
			printf("��������Ҫ���������\n");
			scanf("%d", &value);
			if (IsFullQuene(&Line))
			{
				printf("�����������ɼ���\n");
			}
			else
			{
				printf("%d�����������\n", value);
				EnQuene(value, &Line);
				printf("��������%d��Ԫ��\n", CountQuene(&Line));
			}
			break;
		case'B':
			if (IsEmptyQuene(&Line))
			{
				printf("����Ϊ�գ������ݿ�ɾ��\n");
			}
			else
			{
				DeQuene(&value, &Line);
				printf("ɾ�������\n");
				printf("��������%d��Ԫ��\n", CountQuene(&Line));
			}
			break;
		case'C':
			printf("��������%d��Ԫ��\n", CountQuene(&Line));
			break;
		case 'D':
			printf("��������%d��Ԫ��\n", CountQuene(&Line));
			EmptyQuene(&Line);
			printf("�ټ���\n");
			break;
		}

	}
	return 0;
}