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
	//测试代码
	//Worker* worker = new Employee(1, "李敏", 2);
	//worker->showinfo();
	//delete worker;
	//worker = new Manager(2, "阿敏",4); 
	//worker->showinfo();
	//delete worker;
	//worker = new Boss(3, "李四", 5);
	//worker->showinfo();
	//delete worker;

	WorkerManager ex;
	while (1)
	{
		ex.showmenu();
		int choice;
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出管理程序
			ex.exitpro();
			break;
		case 1://增加职工信息
			ex.addemp();
			break;
		case 2://显示职工信息
			ex.showemp();
			break;
		case 3://删除离职职工
			ex.deleteemp();
			break;
		case 4://修改职工信息
			ex.changeemp();
			break;
		case 5://查找职工信息
			ex.Find_Emp();
			break;
		case 6://按照编号排序
			ex.Sort_Emp();
			break;
		case 7://清空所有文档
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