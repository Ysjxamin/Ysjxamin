#pragma once
#include<iostream>
using namespace std;
#include"WorkerManage.h"
#include"Employee.h"
#include"Worker.h"
#include"Boss.h"
#include"Manager.h"
int main()
{
	//���Դ���
	//Worker* worker = new Employee(1, "����", 2);
	//worker->showinfo();
	//delete worker;
	//worker = new Manager(2, "����",4); 
	//worker->showinfo();
	//delete worker;
	//worker = new Boss(3, "����", 5);
	//worker->showinfo();
	//delete worker;

	WorkerManager ex;
	while (1)
	{
		ex.showmenu();
		int choice;
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳��������
			ex.exitpro();
			break;
		case 1://����ְ����Ϣ
			ex.addemp();
			break;
		case 2://��ʾְ����Ϣ
			ex.showemp();
			break;
		case 3://ɾ����ְְ��
			ex.deleteemp();
			break;
		case 4://�޸�ְ����Ϣ
			ex.changeemp();
			break;
		case 5://����ְ����Ϣ
			ex.Find_Emp();
			break;
		case 6://���ձ������
			ex.Sort_Emp();
			break;
		case 7://��������ĵ�
			ex.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
			
	}
	system("pause");
	return 0;
}