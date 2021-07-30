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
WorkerManager::WorkerManager()//ͨ��Ϊ�ṹ���ඨ��Ĭ�Ϲ��캯������ B() {} �����캯�����������в���������Ĭ��ֵ�����磩�������������
{
	//this->employarray = null;
	//this->fileisempty = true;
	ifstream ifs;
	ifs.open(FILE, ios::in);
	//�ļ����������
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->empsize = 0;
		this->employarray = NULL;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//�ļ�������Ϊ�����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->employarray = NULL;
		this->empsize = 0;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//�ļ�����
	int num = this->getsize();
	cout << "ְ������Ϊ�� " << num << endl;
	this->empsize = num;
	this->employarray = new Worker * [this->empsize];
	this->initemp();
	this->fileisempty = false;
	/*for (int i = 0; i < this->empsize; i++)
	{
		cout << "ְ�����Ϊ  " << this->employarray[i]->id
			<< "\tְ������Ϊ " << this->employarray[i]->name
			<< "\tְ����λΪ " << this->employarray[i]->did << endl;
	}*/
}

void WorkerManager::showmenu()//ǰ��Ҫ�Ӻ�������
{
	cout <<"************************************"<< endl;
	cout <<"********��ӭʹ��ְ������ϵͳ********"<< endl;
	cout <<"**********0.�˳��������************"<< endl;
	cout <<"**********1.����ְ����Ϣ************"<< endl;
	cout <<"**********2.��ʾְ����Ϣ************"<< endl;
	cout <<"**********3.ɾ����ְְ��************"<< endl;
	cout <<"**********4.�޸�ְ����Ϣ************"<< endl;
	cout <<"**********5.����ְ����Ϣ************"<< endl;
	cout <<"**********6.���ձ������************"<< endl;
	cout <<"**********7.��������ĵ�************"<< endl;
	cout <<"************************************"<< endl;
}
void WorkerManager::exitpro()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::addemp()
{
	cout << "������Ҫ��ӵ�ְ��������" << endl;
	int addsize = 0;
	cin >> addsize;
	if (addsize > 0)
	{
		int newSize = this->empsize+addsize;
		Worker** newspace = new Worker* [newSize];
		//����ԭ������
		if (this->employarray != NULL)
		{
			for (i = 0; i < this->empsize; i++)
			{
				newspace[i] = this->employarray[i];
			}
		}
		//����µ�����
		for (i = 0; i < addsize; i++)
		{
			int ID;
			string NAME;
			int Select;
			cout << "������� " << i + 1 << "��ְ�����" << endl;
			cin >> ID;
			cout << "������� " << i + 1 << "��ְ������" << endl;
			cin >> NAME;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�Ե��ܲ�" << endl;
			cin >> Select;
			Worker* worker = NULL;
			//ָ���ʼ���ұ���Ұָ��
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
			//����ְ��ְ����������ݱ��浽��������
			newspace[this->empsize + i] = worker;
		}
			//�ͷ�ԭ�пռ�
			delete[](this->employarray);
			//����ָ������
			this->employarray = newspace;//����ָ������ĵ�ַ
			this->empsize = newSize;
			this->save();
		cout << "�ɹ���� " << addsize << "��ְ��" << endl;
	}
	else
	{
		cout << "��������" << endl;

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
		cout << "�ļ������ڻ��ļ�Ϊ��" << endl;
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
	cout << "��������Ҫɾ����ְ�����" << endl;
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
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::changeemp()
{
	int id;
	if (this->fileisempty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵı�ţ�" << endl;
		cin >> id;
		int index=this->isexist(id);
		if (index != -1)
		{
			delete this->employarray[index];
			int newID;
			string newNAME;
			int newSelect;
			cout << "�������µ�ְ�����" << endl;
			cin >> newID;
			cout << "�������µ�ְ������" << endl;
			cin >> newNAME;
			cout << "��ѡ���µ�ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�Ե��ܲ�" << endl;
			cin >> newSelect;
			Worker* worker = NULL;
			//ָ���ʼ���ұ���Ұָ��
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
			cout << "�޸ĳɹ���" << endl;
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴�ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;


		if (select == 1) //��ְ���Ų���
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = this->isexist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->employarray[ret]->showinfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) //����������
		{
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < this->empsize; i++)
			{
				if (this->employarray[i]->name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< this->employarray[i]->id
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->employarray[i]->showinfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Sort_Emp()
{
	if (this->fileisempty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < this->empsize; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->empsize; j++)
			{
				if (select == 1) //����
				{
					if (this->employarray[minOrMax]->id > this->employarray[j]->id)
					{
						minOrMax = j;
					}
				}
				else  //����
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

		cout << "����ɹ�,�������Ϊ��" << endl;
		this->save();
		this->showemp();
	}
	system("pause");
	system("cls");
}
//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
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
		cout << "��ճɹ���" << endl;
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