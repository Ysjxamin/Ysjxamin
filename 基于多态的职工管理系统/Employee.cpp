#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"Worker.h"
#include"Employee.h"
 Employee::Employee(int id,string name,int did)
{
	this->id = id;
	this->name = name;
	this->did = did;
}
 void Employee::showinfo()
 {
		 cout << "ְ�����:" << this->id
			 << "\tְ������:" << this->name
			 << "\t��λ" << this->getname()
			 << "\tְ��:" << "���ֺ���" << endl;
 }
 string Employee::getname()
 {
	 return (string)"Ա��";
 }
