#include "BTree.h"
#include <iostream>
#include <fstream>


using namespace std;

BTree::BTree(int grau, int tamanho){
    raiz = nullptr;
    grau = grau;
    tamanho = tamanho;
}

BTree::~BTree(){
    libera(raiz);
    raiz = nullptr;
}

// navegar entre os nos
void BTree::libera(BTreeNode* node)
{
    // navegando pelos nos de i
    int i;
    for (i = 0; i < node->n; i++)
    {
        // se nao e uma folha, percorrer as chaves antes de liberar,
        if (!node->folha) {
            libera(node->chaves[i]);
        }
    }
    cout << "core dump aki?" << endl;
    delete node;
}

BTreeNode *BTree::getRaiz() {
    return raiz;
}

void BTree::setRaiz(BTreeNode *raiz) {
    BTree::raiz = raiz;
}

int BTree::getGrau(){
    return grau;
}

void BTree::setGrau(int grau) {
    BTree::grau = grau;
}

int BTree::getTamanho(){
    return tamanho;
}

void BTree::setTamanho(int tamanho) {
    BTree::tamanho = tamanho;
}

void BTree::navegar(){
    if (raiz != nullptr){
        raiz->navegar();
    }
}

BTreeNode* BTree::buscar(char* id){
    return (raiz == nullptr) ? nullptr : raiz->buscar(id);
}

void BTree::inserir(char *id) {

    // caso a raiz seja nula
    if (raiz == nullptr)
    {
        // um novo no sera criado e o valor do id colocado nele
        //esse no sera a raiz e seu tamanho atual (n) sera atualizado
        raiz = new BTreeNode(grau, true, tamanho);
        raiz->valores[0] = id;
        raiz->n = 1;
    }
    else // caso a arvore nao esteja vazia
    {
        // se a raiz estiver cheia a arvore deve crescer em altura
        if (raiz->n == tamanho)
        {
            // criando a nova raiz
            BTreeNode *s = new BTreeNode(grau, false, tamanho);

            // raiz antiga se torna filha da raiz velha
            s->chaves[0] = raiz;

            // aplicando split na raiz antiga para reorganizar a arvore b
            s->splitFilho(0, raiz);

            //a nova raiz possui 2 filhos, splitados da raiz velha
            // two children is going to have new key
            int i = 0;
            if (BTreeNode::compararId(id, s->valores[0])){
                i++;
            }
            s->chaves[i]->inserirNaoCompleto(id);

            // mudando a raiz
            raiz = s;
        }
        else {
            raiz->inserirNaoCompleto(id);
        }  // caso a raiz nao esteja completa basta inserir utilizando a funcao 'inserirNaocompleto"
    }
}