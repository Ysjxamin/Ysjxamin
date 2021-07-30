#pragma once
#include<iostream>
using namespace std;
#include"Worker.h"
class WorkerManager
{
public:
    //≤Àµ•ΩÁ√Ê
	void Clean_File();
	void Sort_Emp();
	void Find_Emp();
	void showmenu();
	void exitpro();
	void addemp();
	void save();
	void initemp();
	void showemp();
	int getsize();
	void changeemp();
	bool fileisempty;
	int isexist(int id);
	void deleteemp();
	WorkerManager();
	int empsize=0;
	Worker** employarray;
	~WorkerManager();
};