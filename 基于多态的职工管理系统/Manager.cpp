#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"Manager.h"
#include"Employee.h"
Manager::Manager(int id, string name, int did)
{
	this->id = id;
	this->name = name;
	this->did = did;
}
void Manager::showinfo()
{
	cout << "ְ�����:" << this->id
		<< "\tְ������:" << this->name
		<< "\t��λ" << this->getname()
		<< "\tְ��:" << "������ɾ����·�������" << endl;
}
string Manager::getname()
{
	return (string)"����";
}
