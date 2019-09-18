// Este programa é uma implementação mínima de Lista.
// Sem atributos tamanho e último, sem remoção, sem alteração, etc...
// Os métodos estão "na lista".

#include <iostream>

typedef int Dado;

// === Declaração do Noh ========
class Noh {
    friend class Lista;
    protected:
        Noh(Dado d, Noh* prox);
        Dado mDado;
        Noh* mPtProximo;
};

// === Declaração da Lista ======
class Lista {
    public:
        // Cria Lista vazia.
        Lista();
        // Desaloca memória.
        ~Lista();
        // Insere um dado no fim da lista.
        void InserirNoFim(Dado dado);
        // Retorna um item da lista.
        Dado Item(unsigned pos);
        // Escreve todos os itens da lista.
        void Escrever(std::ostream& saida);
    protected:
        Noh* mPtPrimeiro;
        Noh* mPtUltimo;
};

using namespace std;

// === Implementação do Noh =====
Noh::Noh(Dado d, Noh* prox)
    : mDado(d), mPtProximo(prox) {
}

// === Implementação da Lista ===
Lista::Lista()
    : mPtPrimeiro(NULL), mPtUltimo(NULL) {
// constrói uma Lista inicialmente vazia
}

Lista::~Lista() {
    Noh* iter = mPtPrimeiro;
    Noh* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->mPtProximo;
        delete iter;
        iter = proximo;
    }
}

void Lista::Escrever(ostream& saida) {
// método básico que *percorre* a Lista, imprimindo seus elementos
    saida << '[';
    Noh* ptNoh = mPtPrimeiro;
    if (ptNoh != NULL) {
        saida << ptNoh->mDado;
        ptNoh = ptNoh->mPtProximo;
    }
    while (ptNoh != NULL) {
        saida << ',' << ptNoh->mDado;
        ptNoh = ptNoh->mPtProximo;
    }
    saida << "]\n";
}

void Lista::InserirNoFim(Dado dado) {
// insere um dado no final da lista
	Noh* novo = new Noh(dado,NULL);
	
	if(mPtPrimeiro == NULL){
		mPtPrimeiro = novo;
		mPtUltimo = novo;
	} else{
		
		mPtUltimo -> mPtProximo = novo;
		mPtUltimo = novo;
	}

}

Dado Lista::Item(unsigned pos) {
// Retorna um dos itens da lista. Caso a posição seja inválida, escreve mensagem de erro
// na saída padrão e retorna um dado default.
	Dado retorno = 0; 
	int PosAux = 0;

	Noh* iter = mPtPrimeiro;

	while(PosAux != pos){
		iter = iter -> mPtProximo;
		PosAux++;
	}

	if(PosAux == pos){
		return iter -> mDado;
	}

	else{
		cout << "Erro: posicao invalida!\n";
		return Dado();
	}
}

int main() {
    Lista lista;
    Dado valor;
    char opcao;
    int pos;
    cin >> opcao;
    while (opcao != 'f') {
        switch(opcao) {
            case 'i': // Inserir
                cin >> valor;
                lista.InserirNoFim(valor);
                lista.Escrever(cout);
                break;
            case 'p': // item na Posicao
                cin >> pos;
                cout << lista.Item(pos) << endl;
                break;
            default:
                cerr << "Erro: opcao invalida!\n";
        }
        cin >> opcao;
    }
    return 0;
}
