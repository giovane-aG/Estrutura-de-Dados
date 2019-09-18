#include <iostream>
using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilhav implementada em arranjo 
class pilhav{
private:
	int capacidade;
	Dado* dados;
	int tamanho;
	int posTopo;
public:
	pilhav(int cap = 100);
    ~pilhav();
	void empilha(Dado valor);
	Dado desempilha();
	Dado espia(); // acessa elemento do topo, mas não retira
	void depura(); // imprime os dados do vetor da pilhav sem removê-los (desempilhar)
	void info();  // imprime informações da pilhav (tamanho e  posição do topo)
};

pilhav::pilhav(int cap){
	capacidade = cap;
	dados = new Dado[capacidade];
	tamanho = 0;
	posTopo = 0;
}

pilhav::~pilhav(){
	delete [] dados;
}

void pilhav::empilha(Dado valor){
	
	int i = tamanho;
	dados[i] = valor;
	posTopo = tamanho;
	tamanho++;
	
}

Dado pilhav::desempilha(){
	Dado retorno = dados[posTopo];
	posTopo--;
	tamanho--;
	return retorno;
}

Dado pilhav::espia(){
	return dados[posTopo];
}

void pilhav::depura(){
	for(int i = 0; i <= posTopo; i++){
		cout << dados[i] << " ";
	}
}

void pilhav::info(){
	cout << tamanho << " " << posTopo << endl;
}

int main(){
	Dado cap = 20;
	pilhav* p1 = new pilhav(20);
	int valor;
	
	for(int i = 0; i < 5; i++){
		cin >> valor;
		p1->empilha(valor);
	}
	
	for(int i = 0; i < 3; i++){
		cout << p1->desempilha() << " ";
	}
	cout << endl;
	
	for(int i = 0; i < 4; i++){
		cin >> valor;
		p1->empilha(valor);
	}
	
	for(int i = 0; i < 3; i++){
		cout << p1->desempilha() << " ";
	}
	cout << endl;
	
	cout << p1->espia() << endl;
	
	p1->depura();
	cout << endl;

	p1->info();
	
	
	
return 0;
}









