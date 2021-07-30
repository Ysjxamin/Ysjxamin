#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"Worker.h"
#include"Boss.h"
Boss::Boss(int id, string name, int did)
{
	this->id = id;
	this->name = name;
	this->did = did;
}
void Boss::showinfo()
{
	cout << "职工编号:" << this->id
		<< "\t职工姓名:" << this->name
		<< "\t岗位" << this->getname()
		<< "\t职能:" << "吃饭睡觉打豆豆" << endl;
}
string Boss::getname()
{
	return (string)"霸道总裁";
}