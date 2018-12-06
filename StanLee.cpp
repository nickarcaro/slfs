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
	Inode *parent; //Puntero hacia el padre
	bool active; //Variable para saber si está utilizado
	char type; // 'f' para file, 'd' para directory

	//Elementos del file
	File *file; //puntero al archivo, la estructura de este está más arriba.
	int fileSize; //tamaño del archivo
	int creationDate; //fecha de creación

	//Elementos directory
	string *dirName; //Nombre del directorio
	vector<Inode*> subInodes; //Punteros a los otros archivos o directorios
};

/*Esta es la clase para el árbol, falta
 implementar las funciones para desplazarse
 por este, o buscar inodes específicos.*/
class InodeTree
{
private:
	Inode root;

public:
	InodeTree()
	{
		//Aquí se inicializa el primer inode (root)
		root.active = true;
		root.type = 'd';
		string name = "/";
		root.dirName = &name;
	}

	//Esta funcion devuelve el root
	Inode* getRoot()
	{
		return &root;
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

	/*TODO:
		implementar:
			mkdir()
			cd()
			createFile()*/

	
	
};

int main()
{
	StanLeeFS sl;
	

	//cout << *i.dirName << endl;
	return 0;
}