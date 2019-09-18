#include <iostream>
#include <string>

typedef std::string TDado; // tipo do dado que será armazenado na pilha

class Noh {
    friend class Fila;
    public:
        Noh(const TDado& d, Noh* p = NULL) : dado(d), prox(p) {}
    private:
        TDado dado;
        Noh* prox;
};

class Fila {
    public:
        Fila();
        ~Fila();
        void Inserir(TDado d); // insere no final da fila
        TDado Remover(); // remove e retorna o primeiro elemento da fila
        bool Vazia();
    private:
        int tamanho;
        Noh* primeiro;
        Noh* ultimo;
};

using namespace std;

Fila::Fila() : tamanho(0), primeiro(NULL), ultimo(NULL) {
}

Fila::~Fila() {
    while (primeiro != NULL)
        Remover();
}

void Fila::Inserir(TDado d) {
    Noh* temp = new Noh(d);
    if (ultimo != NULL)
        ultimo->prox = temp;
    ultimo = temp;
    if (Vazia())
        primeiro = temp;
    ++tamanho;
}

TDado Fila::Remover() {
    TDado removido;
    Noh* temp;
    removido = primeiro->dado;
    temp = primeiro;
    primeiro = primeiro->prox;
    if (Vazia())
        ultimo = NULL;
    delete temp;
    --tamanho;
    return removido;
}

bool Fila::Vazia() {
    return primeiro == NULL;
}

int main() {
	
	Fila filaP, filaN;
	int cont = 1;
	string id, nome;

	cin >> id;
	
	while(id != "fim"){
		if(id == "prioridade"){
			cin >> nome;
			filaP.Inserir(nome);
		}
		if(id == "normal"){
			cin >> nome;
			filaN.Inserir(nome);
		}
		if(id == "atender"){
			if(filaP.Vazia() and filaN.Vazia()){
				cout << "AGUARDE" << endl;
			}
			else if(not filaP.Vazia() and (not filaN.Vazia())){
				if(cont < 4){
					cout << filaP.Remover() << endl;
					cont++;
				}else if(cont == 4){
					cout << filaN.Remover() << endl;
					cont = 1;
				}
			}
			else if(filaP.Vazia() and (not filaN.Vazia())){
				cout << filaN.Remover() << endl;
				cont = 1;
			}
			else if(not filaP.Vazia() and filaN.Vazia()){
				cout << filaP.Remover() << endl;
				cont++;
			}
		}
		cin >> id;
	}
	
	
	
    return 0;
}




