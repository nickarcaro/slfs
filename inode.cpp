#include <iostream>

using namespace std;
class nodo{
	private:
	string archivo;
	int id;
	
	public:
	 nodo *izq;
	 nodo *der;
	 
	 nodo (string archivo){
		 this->archivo=archivo;
		 *izq=NULL;
		 *der=NULL;
	 }
	 
	 string getarchivo(){
		 return archivo;
	 }
	
	
};

class slfs {
	
};
	

int main(){
return 0;}
