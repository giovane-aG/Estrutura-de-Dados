
// Árvore 2-3-4  
// (Árvore B em memória, com nós com capacidade para 2, 3 ou 4 filhos)
// Estruturas de Dados - 2018/2
// Código by Joukim

#include <iostream>
using namespace std;

// constantes para verificação
const int MAXITENS = 3;
const int MINITENS = 1;
const int MAXFILHOS = 4;

// posição do elemento do meio (o que sobe para página pai em caso de estouro
const int MEIO = 1; 

typedef float Dado;

class Noh {
friend class Arvore234;
private:
    bool eFolha;
    int num; // número de itens armazenadas no nó
    Dado itens[MAXITENS];
    Noh* filhos[MAXFILHOS];
    Noh* pai;
public:
    Noh();
    ~Noh();
};

Noh::Noh() {
    num = 0;
    eFolha = false;
    for (int pos = 0; pos < MAXFILHOS; pos++) {
        filhos[pos] = NULL;
    }
}

Noh::~Noh() {
    for (int pos = 0; pos < num+1; pos++) {
        delete filhos[pos];
    }
}

class Arvore234 {
private:
    Noh* raiz;
    void percorreEmOrdemAux(Noh* atual, int nivel);
    Noh* Divide(Noh* umNoh, Dado &itemPromovido);
public:
    Arvore234() { raiz = NULL; }
    ~Arvore234() { delete raiz; }
    void insere(Dado umItem);
    //metodo que auxilia a insercao
    Noh* InsiraRecursivamente(Noh* umNoh, Dado umItem, Dado &itemPromovido);
    void insereIntermediarionaoCheio(Noh* umNoh,Noh* nohAuxiliar,Dado &itemPromovido);
    void inserirNoFolhaNaoCheio(Noh* umNoh, Dado umItem);
    // percorrimento (impressão)
    void percorreEmOrdem();
};

Noh* Arvore234::Divide(Noh* umNoh, Dado &itemPromovido){
    itemPromovido = umNoh->itens[MEIO];
    Noh* novo = new Noh();
    novo->eFolha = umNoh->eFolha;0000000
    novo->itens[0] = umNoh->itens[MEIO+1];
    novo->num = MEIO;
    umNoh->num = MEIO;
    
    if(not(umNoh->eFolha)){
        for (int pos = 0; pos < MEIO+1; pos++){
            novo->filhos[pos] = umNoh->filhos[MEIO+1+pos];
        }
    }
    return novo;
}

/* So acontece quando um noh filho eh dividido e o noh atual esta cheio */
void Arvore234::insereIntermediarionaoCheio(Noh* umNoh,Noh* nohAuxiliar,Dado &itemPromovido) {
    int pos = umNoh->num-1;
    while(pos >= 0 and umNoh->itens[pos] > itemPromovido) {
        // move item uma posicao a direita
        umNoh->itens[pos+1] = umNoh->itens[pos];
        umNoh->filhos[pos+2] = umNoh->filhos[pos+1];
        pos--;
    }
    // insere novo item no local encontrado
    umNoh->itens[pos+1] = itemPromovido;
    umNoh->filhos[pos+2] = nohAuxiliar;
    umNoh->num++;
}

void Arvore234::inserirNoFolhaNaoCheio(Noh* umNoh,Dado umItem) {
    int pos = umNoh->num-1;
    /* Tenta encontrar a posicao adequada para insercao */
    while(pos >= 0 and umNoh->itens[pos] > umItem) {
        // move item uma posicao a direita
        umNoh->itens[pos+1] = umNoh->itens[pos];
        pos--;
    }
    // insere novo item no local encontrado
    umNoh->itens[pos+1] = umItem;
    umNoh->num++;
}

Noh* Arvore234::InsiraRecursivamente(Noh* umNoh,Dado umItem, Dado &itemPromovido) {
    if (umNoh->eFolha) { //caso o noh seja folha encontre o lugar para inserir
        if (umNoh->num < MAXITENS) { /*Noh folha nao cheio*/
            inserirNoFolhaNaoCheio(umNoh,umItem);
            itemPromovido = 0;
            return NULL;
        }
        else { /* noh folha esta cheio, precisa dividir */

            Noh* novo = Divide(umNoh, itemPromovido);
           
            if (umItem <= umNoh->itens[MEIO]) 
                inserirNoFolhaNaoCheio(umNoh,umItem);
            else
                inserirNoFolhaNaoCheio(novo,umItem);
            
            return novo;
        }
    }
    else { // noh nao e folha
        int pos = umNoh->num-1;
        while(pos >= 0 and umNoh->itens[pos] > umItem) { // procura o filho certo para chamar a função InsiraRecursivamente
            pos--;
        }
        Noh* nohAuxiliar = InsiraRecursivamente(umNoh->filhos[pos+1],umItem,itemPromovido); // chamou a função no filho do noh atual
       
        if (nohAuxiliar) { /* Isso acontece quando ha retorno da funcao chamada no filho, o quer dizer que houve divisao do noh filho e e preciso inserir em umNoh*/

            if (umNoh->num < MAXITENS) { //noh não esta cheio
                insereIntermediarionaoCheio(umNoh,nohAuxiliar,itemPromovido);
                return NULL;
            }
            else { /* noh esta cheio */
                Dado itemPromovidoFilho = itemPromovido;
                Noh* novo = Divide(umNoh,itemPromovido);
                
                if(umItem <= umNoh->itens[MEIO])
                    insereIntermediarionaoCheio(umNoh,nohAuxiliar,itemPromovidoFilho);
                else
                    insereIntermediarionaoCheio(umNoh,nohAuxiliar,itemPromovidoFilho);
                return novo;
            }
        }
        return NULL;
    }
}

void Arvore234::insere(Dado umItem) {
    if (raiz == NULL) {
        raiz = new Noh();
        raiz->eFolha = true;
        raiz->itens[0] = umItem;
        raiz->num++;
    } else { // ja tem algo na raiz
        Dado itemPromovido = 0;
        Noh* novo = InsiraRecursivamente(raiz,umItem,itemPromovido);
        if (novo) {
            Noh* antigaraiz = raiz;
            raiz = new Noh();
            raiz->itens[0] = itemPromovido;
            raiz->num++;
            raiz->filhos[0] = antigaraiz;
            raiz->filhos[1] = novo;
        }

    }
}

void Arvore234::percorreEmOrdem() {
    percorreEmOrdemAux(raiz,0);        
    cout<< endl;
}

void Arvore234::percorreEmOrdemAux(Noh* umNoh, int nivel) {
    int pos;
    for (pos = 0; pos < umNoh->num; pos++) {
        // se nó não é folha, imprima os dados do filho pos
        // antes de imprimir o item pos
        if (not umNoh->eFolha) {
            percorreEmOrdemAux(umNoh->filhos[pos], nivel+1); 
        }
        cout << umNoh->itens[pos] << '/' << nivel << ' ';
    }
 
    // Imprima os dados do último filho
    if (not umNoh->eFolha) {
        percorreEmOrdemAux(umNoh->filhos[pos], nivel+1);   
    }
}

/* =========================== Programa ================================*/
int main() {
    Arvore234* B = new Arvore234;
    
    char opcao;
    float valor;
    
    do {
        cin >> opcao;
        if (opcao == 'i') {
            cin >> valor;
            B->insere(valor);
        } else if(opcao == 'e') {
            B->percorreEmOrdem();
        }
    } while(opcao != 'q');
    
    
    delete B;    
    
    return 0;
}