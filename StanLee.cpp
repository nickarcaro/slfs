#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

struct File
{
	string name;
	string data;
};

struct Inode
{
	Inode *parent;
	bool active;
	char type; // 'f' para file, 'd' para directory

	//Elementos del file
	File *file;
	int fileSize;
	int creationDate;

	//Elementos directory
	string *dirName;
	vector<Inode*> subInodes;
};

class InodeTree
{
private:
	Inode root;

public:
	InodeTree()
	{
		root.active = true;
		root.type = 'd';
		string name = "root";
		root.dirName = &name;
	}
	Inode* getRoot()
	{
		return &root;
	}
	
	
};

static void clearScreen()
	{
		cout << "\033[2J";
		cout << "\033[1;1H";
	}

class StanLeeFS
{
	Inode *actual;
	InodeTree tree;
public:
	StanLeeFS()
	{
		actual = tree.getRoot();
		
	}

	
	
};

int main()
{
	StanLeeFS sl;
	

	//cout << *i.dirName << endl;
	return 0;
}