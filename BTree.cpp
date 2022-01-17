#include "BTree.h"
#include <iostream>
#include <fstream>


using namespace std;

BTree::BTree(int grau_var, int tamanho_var){
    this->raiz = nullptr;
    this->grau = grau_var;
    this->tamanho = tamanho_var;
}

BTree::~BTree(){
    if(raiz != nullptr){
        libera(raiz);
        delete raiz;
    }
}

// navegar na arvore e apaga
void BTree::libera(BTreeNode* node)
{
    // navegando pelos nos de i
    int i;
    if(node != nullptr){
        if (!node->folha) {
            for (i = 0; i < node->n; i++) {
                // se nao e uma folha, percorrer as chaves antes de liberar,
                libera(node->chaves[i]);
                delete node->chaves[i];
            }
        }
    }
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

BTreeNode* BTree::buscar(char* id, double* comparacoes){
    return (raiz == nullptr) ? nullptr : raiz->buscar(id, comparacoes);
}

void BTree::inserir(char *id, double endereco, double* comparacoes) {

    // caso a raiz seja nula
    if (raiz == nullptr)
    {
        // um novo no sera criado e o valor do id colocado nele
        //esse no sera a raiz e seu tamanho atual (n) sera atualizado
        raiz = new BTreeNode(grau, true, tamanho);
        raiz->valores[0].idText = id;
        raiz->valores[0].endereco = endereco;
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
            if (BTreeNode::compararId(id, s->valores[0].idText, comparacoes)){
                i++;
            }
            s->chaves[i]->inserirNaoCompleto(id, endereco, comparacoes);

            // mudando a raiz
            raiz = s;
        }
        else {
            raiz->inserirNaoCompleto(id, endereco, comparacoes);
        }  // caso a raiz nao esteja completa basta inserir utilizando a funcao 'inserirNaocompleto'
    }
}