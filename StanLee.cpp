#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

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
	int size; //tamaño de todo en su interior;

	//Elementos del file
	File *file; //puntero al archivo, la estructura de este está más arriba.
	char* creationDate; //fecha de creación

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
		root->parent = root;
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

	string actualDir;
public:
	StanLeeFS()
	{
		actual = tree.getRoot();
		actualDir = actual->dirName;

	}
	string getState()
	{
		return actualDir + " ";
	}
	void mkdir(string name)
	{
		std::chrono::time_point<std::chrono::system_clock> end; //se llama al reloj del sistema en este punto

		end = std::chrono::system_clock::now();  //se inicializa el conteo del tiempo del mkdir
		//cout << actual->dirName;
		Inode *newInode = new Inode;
		newInode->parent = actual;
		newInode->active = true;
		newInode->type = 'd';
		newInode->dirName = name;

		std::time_t end_time = std::chrono::system_clock::to_time_t(end); //se convierte en variable time_t

		actual->subInodes.push_back(newInode);

		cout << "Creación  " << std::ctime(&end_time);
        newInode->creationDate = std::ctime(&end_time);   //se añade el tiempo en formato dia/mes dia numerico hora:min:seg año

		//cout << actual->subInodes[0]->dirName;
		
	}
	void ls()
	{
		//cout << actual->subInodes[0]->dirName;


		for (int i = 0; i < actual->subInodes.size(); ++i)
		{
			if (actual->subInodes[i]->type == 'd')
			{
				cout << endl << actual->subInodes[i]->dirName;
			}
			else if (actual->subInodes[i]->type == 'f')
			{
				
				cout << endl << actual->subInodes[i]->file->name;
			}
		}
		cout << endl;

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
		std::chrono::time_point<std::chrono::system_clock>  end; //se llama al reloj del sistema en este punto
		end = std::chrono::system_clock::now(); //se inicializa el conteo del tiempo del mkdir
		Inode *newInode = new Inode;
		newInode->parent = actual;
		newInode->active = true;
		newInode->type = 'f';
		//Falta poner filesize y creationDate
		
		File *newFile = new File;

		newFile->name = name + ".txt";
		newFile->data = data;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end); //se convierte en variable time_t

		newInode->file = newFile;

		actual->subInodes.push_back(newInode);

		clearScreen();
		cout << newFile->name<< " created on  " << std::ctime(&end_time);
		newInode->creationDate = std::ctime(&end_time); //se añade el tiempo en formato dia/mes dia numerico hora:min:seg año

	}
	string getDirStr(Inode *i, string dir)
	{
		cout << endl << dir;
		string iDir = i->dirName;
		if (!iDir.compare("/"))
		{
			if (dir.size() > 0)
			{
				return dir;
			}
			else
			{
				return iDir;
			}
		}
		else
		{
			return getDirStr(i->parent, "/" + iDir);
		}
	}

	string cd(string dir)
	{
		//Ir al parent
		if (!dir.compare(".."))
		{
			if(!actual->dirName.compare("/"))
			{

				return getState();
			}
			else
			{

				actual = actual->parent;
				cout << actual->dirName;
				actualDir = getDirStr(actual, "");
				return actualDir + " ";
			}
		}
		else
		{
			Inode *newActual = findDir(dir, actual);
			if (newActual != NULL)
			{
				actual = newActual;
				if (!actualDir.compare("/"))
				{
					actualDir = actualDir + dir;
				}
				else
				{
					actualDir = actualDir + "/" + dir;
				}
				return actualDir;
			}
			else
			{

				return "";
			}
		}
	}
	void cat(string str)
	{
		string data = "";
		for (int i = 0; i < actual->subInodes.size(); ++i)
		{
			if(!actual->subInodes[i]->file->name.compare(str))
			{
				data = actual->subInodes[i]->file->data;
			}
		}
		clearScreen();
		if (data.size() > 0)
		{
			
			cout << str << ": " << data << endl;
		}
		else
		{
			cout << "There's no such file" << endl;
		}

	}

	/*TODO:
		implementar:
			sl() : soft link
			hl() : hard link*/

	
	
};

int main()
{
	StanLeeFS sl;
	

	clearScreen();

	bool run = true;
	
	string state = "/";
	string str;
	cout << sl.getState();

	while(run && cin >> str)
	{
		clearScreen();
		cout << sl.getState();
		// "q" para salir del programa
		if(!str.compare("q"))
		{
			run = false;
			clearScreen();
		}
		else if(!str.compare("ls"))
		{
			clearScreen();
			sl.ls();
			cout << endl << sl.getState();
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
			cout << endl << sl.getState();
		}
		else if (!str.compare("cd"))
		{
			cin >> str;

			string newDir = sl.cd(str);
			if (newDir.size() > 0)
			{
				clearScreen();
				cout << sl.getState();
			}
			else
			{
				clearScreen();
				cout << "No such directory" << endl;
				cout << sl.getState();
			}
		}
		else if (!str.compare("cat"))
		{
			//Uso: cat <filename.txt>
			cin >> str;
			sl.cat(str);

			cout << sl.getState();
		}
	}

	
	return 0;
}