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
		 cout << "职工编号:" << this->id
			 << "\t职工姓名:" << this->name
			 << "\t岗位" << this->getname()
			 << "\t职能:" << "游手好闲" << endl;
 }
 string Employee::getname()
 {
	 return (string)"员工";
 }
