#include <iostream>
#include <string>

using namespace std;

int funcaoHash(string s) {
    int h = s.size() % 23;
    return h;
}

class noh {
    friend class tabelaHash;
    private:
        string chave;
        string significado;
        noh* proximo = NULL;
    public:
        noh(string c, string v) {
            chave = c;
            significado = v;
        }
};

class tabelaHash {
    private:
        // vetor de ponteiros de nós
        noh** vetor;
        int capacidade;
    public:
        // construtor padrão
        tabelaHash(int cap = 23);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(string c, string v);
        // recupera um valor associado a uma dada chave
        string recupera(string c);
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    vetor = new noh*[cap];
    capacidade = cap;
    for (int i = 0; i < cap; i++)
        vetor[i] = NULL;
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = vetor[i];
        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] vetor;
}

// Insere um valor v com chave c.
void tabelaHash::insere(string c, string v) {
    int hash = funcaoHash(c);
    if(vetor[hash] == NULL){
  	  noh* novo = new noh(c,v);
  	  vetor[hash] = novo;   	
	} else {
		if(recupera(c) == "NAO ENCONTRADO!"){
			noh* novo = new noh(c,v);
			noh* iter = vetor[hash];
			while(iter->proximo != NULL){
				iter = iter->proximo;
			}
			iter->proximo = novo;
		}
	}
}

// recupera um valor associado a uma dada chave
string tabelaHash::recupera(string c) {
    int h;
    h = funcaoHash(c);
    if((vetor[h] != NULL) and (vetor[h]->chave == c)) {
        return vetor[h]->significado;
    } else {
        noh* atual = vetor[h];

        while ((atual != NULL) and (atual->chave != c)) {
            atual = atual->proximo;
        }

        if ((atual != NULL) and (atual->chave == c)) {
            return atual->significado;
        } else {
            return "NULL";
        }
    }
}

int main( ) {
    tabelaHash th(23);
    int qtdade;
    string chave;
    string significado;

    // insercao na tabela
    cin >> qtdade;
    for (int i=0; i < qtdade; i++) {
        cin >> chave;
        getline(cin,significado);
        th.insere(chave,significado);
    }
    // recupera valores
    cin >> chave;
    while(chave != "-1"){
	    cout<<"["<<chave<<"]"<<" => "<<th.recupera(chave)<<endl;
	    cin>>chave;
	}
    
    return 0;
}
