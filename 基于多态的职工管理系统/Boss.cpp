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
	cout << "ְ�����:" << this->id
		<< "\tְ������:" << this->name
		<< "\t��λ" << this->getname()
		<< "\tְ��:" << "�Է�˯���򶹶�" << endl;
}
string Boss::getname()
{
	return (string)"�Ե��ܲ�";
}