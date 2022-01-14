#include "BTree.h"
#include <iostream>
#include <fstream>


using namespace std;

BTree::BTree(int grau, int tamanho){
    raiz = nullptr;
    grau = grau;
    tamanho = tamanho;
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

        *raiz->valores[0] = *id;
        raiz->n = 1;
    }
    else // caso a arvore nao esteja vazia
    {
        // se a raiz estiver cheia a arvore deve crescer em altura
        if (raiz->n == tamanho)
        {
            // criando a nova raiz
            BTreeNode *s = new BTreeNode(grau, false, tamanho);

            ofstream file;
            file.open("csv'/BTree.bin", ios::out | ios::app | ios::binary);
            file.write((char*)&s, sizeof(s));
            file.close();

            ifstream file2;
            BTreeNode *teste;
            file2.open("csv'/BTree.bin", ios::in | ios::binary);
            file2.read((char*)&teste, sizeof(teste));

            cout << "testando leitura: " << teste->getTamanho() << endl;


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