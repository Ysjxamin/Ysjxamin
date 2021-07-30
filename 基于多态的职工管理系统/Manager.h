#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"Worker.h"
class Manager : public Worker
{
public:
	Manager(int id, string name, int did);
	void showinfo();
	string getname();
};

