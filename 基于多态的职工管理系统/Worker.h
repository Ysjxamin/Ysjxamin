#pragma once
#include<iostream>
using namespace std;
#include<string>
class Worker
{
public:
	virtual void showinfo() = 0;

	virtual string getname() = 0;

	int id;
	string name;
	int did;
};
