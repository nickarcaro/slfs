#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//Compile con: g++ -o sl StanLee.cpp
//Ejecute con: ./sl

struct File
{
	string name;
	string data;
};

struct Inode
{
	Inode *parent; //Puntero hacia el padre
	bool active; //Variable para saber si está utilizado
	char type; // 'f' para file, 'd' para directory

	//Elementos del file
	File *file; //puntero al archivo, la estructura de este está más arriba.
	int fileSize; //tamaño del archivo
	int creationDate; //fecha de creación

	//Elementos directory
	string dirName; //Nombre del directorio
	vector<Inode*> subInodes; //Punteros a los otros archivos o directorios
};

/*Esta es la clase para el árbol, falta
 implementar las funciones para desplazarse
 por este, o buscar inodes específicos.*/
class InodeTree
{
private:
	Inode *root = new Inode;

public:
	InodeTree()
	{
		//Aquí se inicializa el primer inode (root)
		root->active = true;
		root->type = 'd';
		
		root->dirName = "/";
	}

	//Esta funcion devuelve el root
	Inode* getRoot()
	{
		return root;
	}
	
	
};

//Esta función limpia la pantalla de la consola
static void clearScreen()
	{
		cout << "\033[2J";
		cout << "\033[1;1H";
	}


class StanLeeFS
{
	/*El inode actual va a servir para la 
	  navegación por el sistema de archivos, 
	  nos dice en que inode estamos actualmente.*/
	Inode *actual;
	InodeTree tree;
public:
	StanLeeFS()
	{
		actual = tree.getRoot();

	}
	Inode* getRoot()
	{
		return actual;
	}
	void mkdir(string name)
	{
		//cout << actual->dirName;
		Inode *newInode = new Inode;
		newInode->parent = actual;
		newInode->active = true;
		newInode->type = 'd';
		newInode->dirName = name;

		actual->subInodes.push_back(newInode);

		//cout << actual->subInodes[0]->dirName;
		
	}
	void ls()
	{
		//cout << actual->subInodes[0]->dirName;


		for (int i = 0; i < actual->subInodes.size(); ++i)
		{
			if (actual->subInodes[i]->type == 'd')
			{
				cout << actual->subInodes[i]->dirName << endl;
			}
			else if (actual->subInodes[i]->type == 'f')
			{
				
				cout << actual->subInodes[i]->file->name << endl;
			}
		}

	}

	/*findDir() busca en direcciones de tipo
	  "foo/bar/cat/dog", de encontrar la
	  dirección retorna el inode 
	  correspondiente, pero de no ser así
	  retorna NULL.*/
	Inode* findDir(string dir, Inode *inode)
	{
		if (!inode->dirName.compare(dir))
		{
			cout << "aaa";
			return inode;
		}
		else
		{
			//foo/bar/mew
			string temp;
			stringstream ss(dir);
			getline(ss, temp, '/');

			//temp=foo
			bool found = false;
			for (int i = 0; i < inode->subInodes.size(); ++i)
			{
				if (!inode->subInodes[i]->dirName.compare(temp))
				{
					if (temp.compare(dir))
					{
						dir.erase(0, temp.size()+1);
					}
					cout << dir;
					bool found = true;
					return findDir(dir, inode->subInodes[i]);
				}
			}
			
			if (!found)
			{
				return NULL;
			}
		}
	}
	void mkfile(string name, string data)
	{
		Inode *newInode = new Inode;
		newInode->parent = actual;
		newInode->active = true;
		newInode->type = 'f';
		//Falta poner filesize y creationDate
		
		File *newFile = new File;

		newFile->name = name + ".txt";
		newFile->data = data;

		newInode->file = newFile;

		actual->subInodes.push_back(newInode);

	}

	string cd(string dir)
	{
		
	}

	/*TODO:
		implementar:
			mkdir()
			cd()
			createFile()*/

	
	
};

int main()
{
	StanLeeFS sl;
	

	clearScreen();

	bool run = true;
	
	string state = "/";
	string str;

	while(run && cin >> str)
	{
		// "q" para salir del programa
		if(!str.compare("q"))
		{
			run = false;
		}
		else if(!str.compare("ls"))
		{
			sl.ls();
		}
		else if(!str.compare("cd"))
		{
			cin >> str; // este es el parametro donde queremos ir
			//sl.cd(str)
		}
		else if(!str.compare("mkdir"))
		{

			//uso: mkdir <Nombre directorio>
			cin >> str;
			sl.mkdir(str);
		}
		else if(!str.compare("mkfile"))
		{
			//uso: mkfile <Nombre archivo> "<Datos>"
			cin >> str;
			string name = str;

			getline(cin, str);
			string data = str;

			

			sl.mkfile(name, data);
		}
		else if (!str.compare("fd"))
		{
			Inode *inode = sl.findDir("foo/bar", sl.getRoot());
			if (inode != NULL)
			{
				cout << "It works!" << endl;
			}
		}
	}

	
	return 0;
}