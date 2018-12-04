#include <iostream>
#include <vector>
using namespace std;

//Compilar con: g++ -o itree InodeTree.cpp
//Ejecutar: ./itree

class Inode{
private:
	/*Creo que el id depende de la cantidad de 
	  nodos que hayan, por lo tanto el root 
	  debería ser id=0. Pero para sacar el 
	  valor de los otros nodos, quizás debamos 
	  implementar una función que cuente la cantidad 
	  de nodos totales en el árbol.*/
	int id;

	//Este bool marca la diferencia entre los archivos y los directorios.
	bool isDirectory;

	//Vector de Inodes, ya que el árbol no es binario.
	vector<Inode*> subInodes;

	/*TODO:
		Hay que implementar alguna variable
		que apunte hacia algun archivo, ya que
		el inode no contiene el archivo en si.*/
public:
	Inode(int id, bool isDirectory){
		this->id = id;
		this->isDirectory = isDirectory;
	}
	int getId(){
		return id;
	}
	int getSubInodeCount(){
		return subInodes.size();
	}

	void addInode(Inode *newInode){
		subInodes.push_back(newInode);
	}
};

class InodeTree
{
	/*TODO:
		Luego de implementar la clase Inode, 
		hay que armar el árbol, comenzando
		del root y haciendo las funciones 
		recursivas para recorrerlo
		ej:
			findInode(int id, Inode n){
				if n.id = id
					return el nodo
				else
					for cada nodohijo en n
						return findInode(id, nodohijo[i]);
						*/
};


int main(int argc, char const *argv[])
{
	//Probando la clase Inode
	Inode root(0, true);
	Inode test(2, false);

	root.addInode(&test);

	cout << root.getId() << endl;
	cout << root.getSubInodeCount() << endl;
	return 0;
}


