#include "BTreeNode.h"
#include <iostream>

using namespace std;

typedef char* id;


BTreeNode::BTreeNode(int grau, bool folha, int tamanho){
    this->grau = grau;
    this->folha = folha;
    this->n = 0;
    this->tamanho = tamanho;
    this->valores = new id[tamanho];
    this->chaves = new BTreeNode*[tamanho];
}

BTreeNode::~BTreeNode() {
}

int BTreeNode::getGrau() {
    return this->grau;
}

void BTreeNode::setGrau(int grau) {
    this->grau = grau;
}

BTreeNode** BTreeNode::getChaves() {
    return this->chaves;
}

void BTreeNode::setChaves(BTreeNode **chaves) {
    *this->chaves = *chaves;
}

int BTreeNode::getN() {
    return this->n;
}

void BTreeNode::setN(int n) {
    this->n = n;
}

bool BTreeNode::isFolha() {
    return this->folha;
}

void BTreeNode::setFolha(bool folha) {
    this->folha = folha;
}

int BTreeNode::getTamanho(){
    return this->tamanho;
}

void BTreeNode::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

bool BTreeNode::compararId(char* id1, char* id2){
    int i = 0;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
    return id1[i] > id2[i];
}

bool BTreeNode::idIgual(char* id1, char* id2){
    int i = 0;
    for(i = 0; id1[i] != '\0' && id1[i] == id2[i]; i++);
    return id1[i] == id2[i];
}


// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::buscar(char* id)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && compararId(id, valores[i]))
        i++;

    // If the found key is equal to k, return this node
    if (idIgual(id, valores[i]))
        return this;

    // If key is not found here and this is a leaf node
    if (folha)
        return nullptr;

    // Go to the appropriate child
    return chaves[i]->buscar(id);
}

void BTreeNode::inserirNaoCompleto(char* id)
{
    // inicializa como no index mais a direita
    int i = n-1;

    // se eh folha ou esta dentro do tamanho possivel
    if (folha)
    {
        //encontra a posicao para o novo id e rarranja os ids "maiores"
        cout << "while!" << endl;
        while (i >= 0 && compararId(valores[i], id))
        {
            valores[i+1] = valores[i];
            i--;
        }
        cout << "fim while!" << endl;

        //insere o valor na nova localizacao
        valores[i+1] = id;
        n++;
    }
    else // se nao e folha
    {
        // encontrando a chave para o valor
        cout << "while nao folha!" << endl;
        while (i >= 0 && compararId(valores[i], id)){
            i--;
        }

        // verificando se o filho encontrado esta completo
        if (chaves[i+1]->getN() == tamanho)
        {
            // se estiver completo, utilizar o split
            cout << "split!" << endl;
            splitFilho(i+1, chaves[i+1]);

            // depois do split, uma das chaves de chaves[i] sobe para o no pai
            // chaves[i] eh separado em 2.
            // busca quais dos 2 recebera o valor
            if (compararId(id, valores[i+1])){
                i++;
            }
        }
        cout << "nao completo reprise" << endl;
        chaves[i+1]->inserirNaoCompleto(id);
    }
}

//funcao para splitar filho
void BTreeNode::splitFilho(int i, BTreeNode *y)
{
    // criando no novo
    BTreeNode *z = new BTreeNode(y->grau, y->folha, y->tamanho);
    z->n = grau - 1;

    // passando as chaves depois do grau
    for (int j = 0; j < grau-1 && j+grau < tamanho; j++)
        z->valores[j] = y->valores[j+grau];

    // copiar o ultimo de grau filho de y para z
    if (!y->folha)
    {
        for (int j = 0; j < grau; j++)
            z->chaves[j] = y->chaves[j+grau];
    }

    // reduzir o numero de chaves
    y->n = grau - 1;

    // criando uma chave e espaco para uma nova chave
    for (int j = n; j >= i+1; j--)
        chaves[j+1] = chaves[j];

    //linkando o novo no
    chaves[i+1] = z;

    //buscando um novo no e movendo as chaves para abrir espaco
    for (int j = n-1; j >= i; j--)
        valores[j+1] = valores[j];

    //copiando a espaco de y para
    valores[i] = y->valores[grau-1];

    // incrementando n
    n = n + 1;
}

// navegar entre os nos
void BTreeNode::navegar()
{
    //navegando pelos nos de i
    int i;
    for (i = 0; i < n; i++)
    {
        // se nao e uma folha, percorrer as chaves antes de imprimir,
        if (!folha)
            chaves[i]->navegar();
        cout << " " << valores[i];
    }

    //  imprimindo os valores do ultimo no
    if (!folha)
        chaves[i]->navegar();
}