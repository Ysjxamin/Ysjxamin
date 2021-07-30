#pragma once
#include<iostream>
using namespace std;
#include"WorkerManage.h"
#include"Worker.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<fstream>
#define FILE "employee.txt"
int i=0;
WorkerManager::WorkerManager()//通过为结构或类定义默认构造函数（如 B() {} ）或构造函数（其中所有参数都具有默认值，例如），来解决此问题
{
	//this->employarray = null;
	//this->fileisempty = true;
	ifstream ifs;
	ifs.open(FILE, ios::in);
	//文件不存在情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->empsize = 0;
		this->employarray = NULL;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//文件存在且为空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->employarray = NULL;
		this->empsize = 0;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//文件存在
	int num = this->getsize();
	cout << "职工人数为： " << num << endl;
	this->empsize = num;
	this->employarray = new Worker * [this->empsize];
	this->initemp();
	this->fileisempty = false;
	/*for (int i = 0; i < this->empsize; i++)
	{
		cout << "职工编号为  " << this->employarray[i]->id
			<< "\t职工姓名为 " << this->employarray[i]->name
			<< "\t职工岗位为 " << this->employarray[i]->did << endl;
	}*/
}

void WorkerManager::showmenu()//前面要加函数类型
{
	cout <<"************************************"<< endl;
	cout <<"********欢迎使用职工管理系统********"<< endl;
	cout <<"**********0.退出管理程序************"<< endl;
	cout <<"**********1.增加职工信息************"<< endl;
	cout <<"**********2.显示职工信息************"<< endl;
	cout <<"**********3.删除离职职工************"<< endl;
	cout <<"**********4.修改职工信息************"<< endl;
	cout <<"**********5.查找职工信息************"<< endl;
	cout <<"**********6.按照编号排序************"<< endl;
	cout <<"**********7.清空所有文档************"<< endl;
	cout <<"************************************"<< endl;
}
void WorkerManager::exitpro()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::addemp()
{
	cout << "请输入要添加的职工数量：" << endl;
	int addsize = 0;
	cin >> addsize;
	if (addsize > 0)
	{
		int newSize = this->empsize+addsize;
		Worker** newspace = new Worker* [newSize];
		//保存原来数据
		if (this->employarray != NULL)
		{
			for (i = 0; i < this->empsize; i++)
			{
				newspace[i] = this->employarray[i];
			}
		}
		//添加新的数据
		for (i = 0; i < addsize; i++)
		{
			int ID;
			string NAME;
			int Select;
			cout << "请输入第 " << i + 1 << "个职工编号" << endl;
			cin >> ID;
			cout << "请输入第 " << i + 1 << "个职工姓名" << endl;
			cin >> NAME;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.霸道总裁" << endl;
			cin >> Select;
			Worker* worker = NULL;
			//指针初始化且避免野指针
			switch (Select)
			{
			case 1:
				worker = new Employee(ID, NAME, 1);
				break;
			case 2:
				worker = new Manager(ID, NAME, 2);
				break;
			case 3:
				worker = new Boss(ID, NAME, 3);
				break;
			default:
				break;
			}
			//创建职工职责后将新增数据保存到新数组中
			newspace[this->empsize + i] = worker;
		}
			//释放原有空间
			delete[](this->employarray);
			//更新指向数组
			this->employarray = newspace;//整个指针数组的地址
			this->empsize = newSize;
			this->save();
		cout << "成功添加 " << addsize << "名职工" << endl;
	}
	else
	{
		cout << "输入有误！" << endl;

	}
	system("pause");
	system("cls");                             
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILE, ofs.out);
	for ( i=0; i < this->empsize; i++)
	{
		ofs << this->employarray[i]->id 
			<< "\t"<<this->employarray[i]->name 
			<< "\t"<<this->employarray[i]->did << endl;
	}
	ofs.close();
}
int WorkerManager::getsize()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	int ID;
	string NAME;
	int did;
	int num=0;
	while (ifs >> ID && ifs >> NAME && ifs >> did)
	{
		num++;
	}
	ifs.close();
	return num;
}
void WorkerManager::initemp()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	int ID;
	string NAME;
	int did;
	int index=0;
	Worker* worker = NULL;
	while (ifs >> ID && ifs >> NAME && ifs >> did)
	{
		if (did == 1)
		{
			worker = new Employee(ID, NAME, did);
		}
		else if (did == 2)
		{
			worker = new Manager(ID, NAME, did);
		}
		else
		{
			worker = new Boss(ID, NAME, did);
		}
		this->employarray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkerManager::showemp()
{
	if (fileisempty)
	{
		cout << "文件不存在或文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->empsize; i++)
		{
			this->employarray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isexist(int id)
{
	int index=-1;
	for (int i = 0; i < this->empsize; i++)
	{
		if (this->employarray[i]->id == id)
		{
			index = i;
			break;
		}
   }
	return index;
}
void WorkerManager::deleteemp()
{
	cout << "请输入你要删除的职工编号" << endl;
	int id;
	cin >> id;
	int ret = this->isexist(id);
	if (ret != -1)
	{
		for (int i = ret; i < (this->empsize - 1); i++)
		{
			this->employarray[i] = this->employarray[i + 1];
		}
		this->empsize--;
		this->save();
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "删除失败，未找到该职工" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::changeemp()
{
	int id;
	if (this->fileisempty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入你要修改的编号：" << endl;
		cin >> id;
		int index=this->isexist(id);
		if (index != -1)
		{
			delete this->employarray[index];
			int newID;
			string newNAME;
			int newSelect;
			cout << "请输入新的职工编号" << endl;
			cin >> newID;
			cout << "请输入新的职工姓名" << endl;
			cin >> newNAME;
			cout << "请选择新的职工的岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.霸道总裁" << endl;
			cin >> newSelect;
			Worker* worker = NULL;
			//指针初始化且避免野指针
			switch (newSelect)
			{
			case 1:
				worker = new Employee(newID, newNAME, 1);
				break;
			case 2:
				worker = new Manager(newID, newNAME, 2);
				break;
			case 3:
				worker = new Boss(newID, newNAME, 3);
				break;
			default:
				break;
			}
			this->employarray[index] = worker;
			cout << "修改成功！" << endl;
			this->save();
		}
		else
		{
			cout << "修改失败，查无此职工" << endl;
		}
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //按职工号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = this->isexist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->employarray[ret]->showinfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) //按姓名查找
		{
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < this->empsize; i++)
			{
				if (this->employarray[i]->name == name)
				{
					cout << "查找成功,职工编号为："
						<< this->employarray[i]->id
						<< " 号的信息如下：" << endl;

					flag = true;

					this->employarray[i]->showinfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < this->empsize; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->empsize; j++)
			{
				if (select == 1) //升序
				{
					if (this->employarray[minOrMax]->id > this->employarray[j]->id)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (this->employarray[minOrMax]->id < this->employarray[j]->id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = this->employarray[i];
				this->employarray[i] = this->employarray[minOrMax];
				this->employarray[minOrMax] = temp;
			}

		}

		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->showemp();
	}
	system("pause");
	system("cls");
}
//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILE, ios::trunc);
		ofs.close();

		if (this->employarray != NULL)
		{
			for (int i = 0; i < this->empsize; i++)
			{
				if (this->employarray[i] != NULL)
				{
					delete this->employarray[i];
				}
			}
			this->empsize = 0;
			delete[] this->employarray;
			this->employarray = NULL;
			this->fileisempty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager()
{
	if (this->employarray != NULL)
	{
		delete[]this->employarray;
		this->employarray = NULL;
	}

}