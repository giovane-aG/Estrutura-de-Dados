// Tabela Hash com tratamento de colisão por endereçamento aberto
#include <iostream>
#include <stdexcept>

typedef int TValor; // tipo do valor armazenado

class InfoHash {
    friend class Hash; // essa classe só deve ser usada na classe Hash
    InfoHash();
    InfoHash(const std::string& chave, const TValor& valor);
    std::string mChave;
    TValor mValor;
};

class Hash {
    public:
        Hash(int capacidade = 50);
        ~Hash();
        // Mostra todos as posições de armazenamento da hash.
        void EscreverEstrutura(std::ostream& saida) const;
        // Insere uma cópia do valor. Não permite inserção de chave repetida.
        void Inserir(const std::string& chave, const TValor& valor);
        // Remove um item da hash associado com a chave dada.
        void Remover(const std::string& chave);
        // Retorna o valor associado a uma chave.
        TValor Valor(const std::string& chave) const;
    protected:
        // Retorna a posicao em que uma chave está armazenada na estrutura.
        unsigned Buscar(const std::string& chave) const;
        // Retorna a posicao em que uma chave deveria ficar na estrutura.
        unsigned Posicao(const std::string& chave) const;

        InfoHash** mVetPtDados;
        InfoHash* REMOVIDO; // ponteiro especial a ser usado para marcar posições de elemento removido
        int mCapacidade;
        int mTamanho;
};

using namespace std;

InfoHash::InfoHash()
    : mChave(), mValor() {
}

InfoHash::InfoHash(const std::string& chave, const TValor& valor)
    : mChave(chave), mValor(valor) {
}

Hash::Hash(int capacidade) // capacidade tem valor default
    : mVetPtDados(new InfoHash*[capacidade]), REMOVIDO(new InfoHash()), mCapacidade(capacidade), mTamanho(0) {
    // FALTA FAZER:
    // inicializar todas as posições de armazenamento com NULL indicando posição VAZIA
    for(int i = 0; i < capacidade; i++) {
    	mVetPtDados[i] = NULL;
	}
}

Hash::~Hash() {
    // desalocar memória de cada item (InfoHash) armazenado
    // desalocar o ponteiro especial REMOVIDO
    // desalocar o vetor de ponteiro
    for(int i = 0; i < mCapacidade; i++) {
    	mVetPtDados[i] = NULL;
	}
	delete REMOVIDO;
	delete [] mVetPtDados;
}

unsigned Hash::Buscar(const std::string& chave) const {
    // Retorna a posicao em que uma chave está armazenada na estrutura. Protegido.
    int pos = Posicao(chave);
    int ultimo = (mCapacidade +pos-1)%mCapacidade;
    while(mVetPtDados[pos]!=NULL and mVetPtDados[pos]->mChave!= chave and pos!=ultimo){
		pos = (pos+1) % mCapacidade;
	}
	if (mVetPtDados[pos]!=NULL and mVetPtDados[pos]->mChave == chave) {
		return pos;
	}
	else throw runtime_error("Chave não existe na estrutura");
}

void Hash::EscreverEstrutura(std::ostream& saida) const {
    // Mostra todos as posições de armazenamento da hash. Ajuda a debugar.
    for (int i = 0; i < mCapacidade; ++i) {
        saida << '[' << i;
        if (mVetPtDados[i] != NULL) {
            if (mVetPtDados[i] == REMOVIDO)
                saida << "/removido";
            else
                saida << '/' << mVetPtDados[i]->mChave << '/' << mVetPtDados[i]->mValor;
        }
        saida << "] ";
    }
}

void Hash::Inserir(const string& chave, const TValor& valor) {
    // Insere uma cópia do valor. Não permite inserção de chave repetida.
	if(mTamanho < mCapacidade) {
    	InfoHash* novo = new InfoHash(chave,valor);
    	unsigned pos = Posicao(chave);
    	int cont = 0;
		while(mVetPtDados[pos] != NULL and mVetPtDados[pos] != REMOVIDO and mVetPtDados[pos]->mChave != chave  and cont < mCapacidade) {
			pos = (pos+1)%mCapacidade;
			cont++;
		}
		 if(mVetPtDados[pos] == NULL or mVetPtDados[pos] == REMOVIDO){
    		mVetPtDados[pos] = novo;
    		mTamanho++;
		} else {
			throw runtime_error("Chave ja inserida");
		}
	} else {
		throw runtime_error("Tabela cheia");
	}
}

unsigned Hash::Posicao(const string& chave) const {
    // Retorna a posição de armazenamento de uma chave, 0 <= posicao < mCapacidade. Protegido.
    unsigned pos = 1;
    unsigned tamanho = unsigned(chave.length());
    for (unsigned i = 0; i < tamanho; ++i)
        pos = 7 * pos + chave[i];
    return pos % mCapacidade;
}

void Hash::Remover(const std::string& chave) {
    // Remove um item da hash associado com a chave dada.
    unsigned pos = Buscar(chave);
	delete mVetPtDados[pos];
	mVetPtDados[pos] = REMOVIDO;
	mTamanho--;
}

TValor Hash::Valor(const std::string& chave) const {
    // Retorna o valor associado a uma chave.
	unsigned pos = Buscar(chave);
	return mVetPtDados[pos]->mValor;
}

int main() {
    int capacidade;
    cin >> capacidade;
    Hash tabela(capacidade);
    char operacao;
    string chave;
    TValor valor;
    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // inserir
                    cin >> chave >> valor;
                    tabela.Inserir(chave, valor);
                    break;
                case 'r': // remover
                    cin >> chave;
                    tabela.Remover(chave);
                    break;
                case 'c': // consultar
                    cin >> chave;
                    valor = tabela.Valor(chave);
                    cout << valor << endl;
                    break;
                case 'd': // debug (mostrar estrutura)
                    tabela.EscreverEstrutura(cout);
                    cout << endl;
                    break;
                case 'f': // finalizar
                    // vai testar depois
                    break;
                default:
                    cerr << "operação inválida\n";
            }
        }
        catch (exception& e) {
            // ignorar a mensagem que explica o erro e só escrever ERRO.
            cout << "ERRO" << endl;
        }
    } while (operacao != 'f');
    return 0;
}

