#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"Worker.h"
class Boss : public Worker
{
public:
	Boss(int id, string name, int did);
	void showinfo();
	string getname();
};

