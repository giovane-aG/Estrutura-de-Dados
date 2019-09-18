#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class lista;
    private:
        const Dado dado;
        noh* proximo;
    public:
        noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d) {
    proximo = NULL;
}

class lista {
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        lista();
        ~lista();
        void insere(Dado dado);
        void insere(Dado dado, int pos);
        void remove(int posicao);
        int procura(Dado valor);
        void imprime();
        inline bool vazia();
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    noh* iter = primeiro;
    noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    noh* aux = primeiro;
    while (aux != NULL) {
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

// insere por padrão no final da lista
void lista::insere(Dado dado) {
    // Implemente aqui
	if(vazia()){
		noh* novo = new noh(dado);
    	primeiro = novo;
    	ultimo = novo;
    	tamanho++;
	} else {
		noh* novo = new noh(dado);
		ultimo -> proximo = novo;
		ultimo = novo;
		tamanho++;
	}
}

// insere um dado em uma determinada posição da lista
void lista::insere(Dado dado, int posicao) {
    // Implemente aqui
    if(posicao >= 0 and posicao <= tamanho){
    	if(vazia()){
    		noh* novo = new noh(dado);
    		primeiro = novo;
    		ultimo = novo;
    		tamanho++;
		}
		else if(posicao == 0){
			noh* novo = new noh(dado);
			novo->proximo = primeiro;
			primeiro = novo;
			tamanho++;
		}
		else if(posicao == tamanho and tamanho != 0){
			noh* novo = new noh(dado);
			ultimo->proximo = novo;
			ultimo = novo;
			novo->proximo = NULL;
			tamanho++;
		}
   		else {
   			noh* novo = new noh(dado);	
   			noh* iter = primeiro;	
			int Pos = 0;
			while(Pos != (posicao-1)){
				iter = iter -> proximo;
				Pos++;
				tamanho++;
			}
			novo = new noh(dado);
			novo -> proximo = iter -> proximo;
			iter -> proximo = novo;
			tamanho++;
		}
	}
	
}

// remove o item da posição passada por parâmetro
// Atenção - o código deve tratar de posição inválidas
void lista::remove(int posicao) {
    // Implemente aqui    
    if(posicao < 0 or posicao >= tamanho){
    	cout << "Posicao Invalida" << endl;
	}
	else {
		if(tamanho == 1){
	    	noh* iter = primeiro;
	    	primeiro = NULL;
	    	ultimo = NULL;
	    	delete iter;
	    	tamanho--;
		}
	    else if(posicao == 0 and tamanho > 1){
	    	noh* iter = primeiro;
	    	primeiro = primeiro -> proximo;
	    	delete iter;
	    	tamanho--;
		} 
		else if(posicao == (tamanho-1)){
			noh* iter = primeiro;
			noh* aux = NULL;
			int Pos = 0;
			
			while(Pos != posicao){
				aux = iter;
				iter = iter -> proximo;
				Pos++;
			}
			ultimo = aux;
			aux->proximo = NULL;
			delete iter;
			tamanho--;
		}
		else {
			noh* iter = primeiro;
			noh* aux = NULL;
			int Pos = 0;
			
			while(Pos != posicao){
				aux = iter;
				iter = iter -> proximo;
				Pos++;
			}
			aux->proximo = iter -> proximo;
			delete iter;
			tamanho--;
		}
	}
}

// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Dado valor) {
    // Implemente aqui
    int Pos = 0;
	noh* iter = primeiro;

	while(iter != NULL){
		if(iter -> dado == valor){
			return Pos;
		}
		iter = iter -> proximo;
		Pos++;
	}
	return -1;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    // Implemente aqui
    return primeiro == NULL;
}

int main() { // NÃO MODIFIQUE!
    lista minhaLista;
    char opcao;
    int valor, pos;
    cin >> opcao;
    while (opcao != 'Q') {
        switch(opcao) {
            case 'I':
                cin >> valor;
                minhaLista.insere(valor);
                break;
            case 'W':
                cin >> valor;
                cin >> pos;
                minhaLista.insere(valor, pos);
                break;
            case 'P':
                cin >> valor;
                cout << minhaLista.procura(valor) << endl;
                break;
            case 'R':
                cin >> pos;
                minhaLista.remove(pos);
                break;
            case 'V':
                cout << minhaLista.vazia() << endl;
                break;
        }
        cin >> opcao;
    }
    minhaLista.imprime();
    return 0;
}
