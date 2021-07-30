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
	cout << "职工编号:" << this->id
		<< "\t职工姓名:" << this->name
		<< "\t岗位" << this->getname()
		<< "\t职能:" << "负责完成经理下发的任务" << endl;
}
string Manager::getname()
{
	return (string)"经理";
}
